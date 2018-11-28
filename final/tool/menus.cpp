#include "stdafx.h"
#include <ostream>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>
#include "block.h"
#include <algorithm>
#include "menus.h"
#include <iterator>

void press_enter_to_go_back()
{
  std::cout << "\nPress ENTER to go back...\n";
  std::cin.ignore();
  system("cls");
}

unsigned int get_number_from_console(std::string caption)
{
  unsigned int user_number = 0;
  std::string input = "";
  while (true) {
    std::cout << caption;
    getline(std::cin, input);
    // This code converts from string to number safely.
    std::stringstream input_ss(input);
    if (input_ss >> user_number)
      break;
    std::cout << "Invalid number, please try again..." << std::endl;
  }
  return user_number;
}

double get_input_from_console(std::string caption)
{
  double input_value = 0.;
  std::string input;
  while (true) {
    std::cout << caption;
    getline(std::cin, input);
    // This code converts from string to number safely.
    std::stringstream input_ss(input);
    if (input_ss >> input_value)
      break;
    std::cout << "Invalid input value, please try again..." << std::endl;
  }
  return input_value;
}

std::string get_text_from_console(std::string caption)
{
  std::string text_input;
  std::cout << caption << "\n";
  getline(std::cin, text_input);
  return text_input;
}

void show_available_block_types()
{
  //show available block types
  system("cls");
  std::string block_list_menu = "Available block types:\n";
  std::vector<std::string> block_list = block_factory::GetBlockTypes();
  for (std::vector<std::string>::iterator it = block_list.begin(); it != block_list.end(); ++it)
    block_list_menu += *it;
  std::cout << block_list_menu << std::endl;
}

void show_block_sequence(block_processor &bp)
{
  //show block sequence
  system("cls");
  std::cout << "Block sequence:\n" << std::endl;
  int index = 0;
  std::vector<std::string> temp_v = bp.get_sequence();
  std::for_each(temp_v.begin(), temp_v.end(), [&](std::string const &c)
  {
    index++;
    std::cout << index << ":\t" << c << std::endl;
  });
}

bool add_new_block(block_processor &bp)
{
  //add new block
  system("cls");
  std::string block_command;
  std::string input = "";
  while (true) {
    std::cout << "Enter new block (or just ENTER to go back):\ ";
    getline(std::cin, input);
    if (input == "")
      return false;
    try
    {
      std::pair<std::string, std::vector<double>> p = block_processor::get_block_command_from_text(input);
      std::unique_ptr<block> bl = block_factory::Create(p.first, p.second);
      if (bl == nullptr) return false;
      bp.add_block(bl);
      return true;
    }
    catch (...)
    {
      std::cout << "Invalid entry, please try again..." << std::endl;
      return false;
    }
  }
}
void remove_block_from_sequence(block_processor &bp)
{
  system("cls");
  const unsigned int block_index = get_number_from_console("Enter index of block to be removed:");
  if (bp.remove_block(block_index))
    std::cout << "Block on index" << block_index << " is removed." << std::endl;
  else
    std::cout << "ERROR: Block on index" << block_index << " is NOT removed." << std::endl;
}
//
void calc_sequence(const block_processor &bp)
{
  system("cls");
  const double input_value = get_input_from_console("Please enter a valid number: ");
  const double result = bp.calc_all(input_value);
  std::cout << "Result: " << result << std::endl;
}

void load_from_file(block_processor &bp, std::string &file_name)
{
  system("cls");
  block_processor::sequence_list stored_blocks;

  std::ifstream parameters_stream(file_name, std::ios::in);
  std::string block_line;

  if (!parameters_stream.is_open())
  {
    std::cout << "ERROR: Block sequence cannot be loaded from '" << file_name << "' file.\n" << std::endl;
    return;
  }
  try
  {
    bp.load_from_stream(parameters_stream);
    std::cout << "Block sequence is loaded from '" << file_name << "' file.\n" << std::endl;
  }
  catch (const std::exception&)
  {
    std::cout << "ERROR: Block sequence cannot be loaded from '" << file_name << "' file.\n" << std::endl;
  }
  parameters_stream.close();
}

void load_and_calc_inputs_from_file(block_processor &bp)
{
  system("cls");

  //Load inputs from file
  double input_value;
  std::vector<double> inputs_for_calc;
  const std::string file_with_inputs = get_text_from_console("Please enter file name with input values (each value in new row): ");
  std::ifstream inputs_is(file_with_inputs);
  std::string input_line;
  if (!inputs_is.is_open()) { std::cout << "\nERROR: Cannot open input file: " << file_with_inputs; return; }

  //Prepare result stream
  const std::size_t lastindex = file_with_inputs.find_last_of(".");
  const std::string raw_file_name = file_with_inputs.substr(0, lastindex);
  const std::string result_file_name = raw_file_name + "_results.txt";
  std::ofstream results_os(result_file_name, std::ios::out);
  if (!results_os.is_open()) { std::cout << "\nERROR: Cannot open output file:: " << result_file_name; return; }

  // Calculate and save results
  if (!bp.bulk_calc(inputs_is, results_os))
    std::cout << "\nERROR: Input file: '" << file_with_inputs << "' has one or more invalid values.";
  else
    std::cout << "\nResults are saved to file: " << result_file_name;

  //close streams
  inputs_is.close();
  results_os.close();
}

void save_sequence_to_file(block_processor &bp, std::string file_name)
{
  system("cls");

  std::ofstream parameters_stream(file_name, std::ios::out);
  if (!parameters_stream.is_open()) { std::cout << "\nERROR: Block sequence is NOT saved to file: " << file_name; }

  auto command_sequence = bp.get_sequence();
  for (std::vector<std::string>::iterator it = command_sequence.begin(); it != command_sequence.end(); ++it)
    parameters_stream << *it << std::endl;
  parameters_stream.close();
  std::cout << "\nBlock sequence is saved to file: " << file_name;
}