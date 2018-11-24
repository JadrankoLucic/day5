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

double get_input_from_console()
{
  double input_value = 0.;
  std::string input;
  while (true) {
    std::cout << "Please enter a valid input number: ";
    getline(std::cin, input);
    // This code converts from string to number safely.
    std::stringstream input_ss(input);
    if (input_ss >> input_value)
      break;
    std::cout << "Invalid input value, please try again..." << std::endl;
  }
  return input_value;
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
std::pair<std::string, std::vector<double>> get_block_command_from_text(std::string command_text)
{
  bool block_name_taken = false;
  std::string block_name;
  std::vector<double> parameters;
  std::istringstream line_ss(command_text);
  do
  {
    std::string value;
    line_ss >> value;
    if (value == "") break;
    if (!block_name_taken)
    {
      block_name = value;
      block_name_taken = true;
    }
    else
      parameters.push_back(atof(value.c_str()));
  } while (!line_ss.eof());
  return std::pair<std::string, std::vector<double>>(block_name, parameters);
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
      std::pair<std::string, std::vector<double>> p = get_block_command_from_text(input);
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
  const double input_value = get_input_from_console();
  const double result = bp.calc_all(input_value);
  std::cout << "Result: " << result << std::endl;
}

void load_from_file(block_processor &bp, std::string &file_name)
{
  system("cls");
  block_processor::sequence_list stored_blocks;
  if (get_blocks_from_file(file_name, stored_blocks))
  {
    try
    {
      bp.load(stored_blocks);
      std::cout << "Block sequence is loaded from '" << file_name << "' file.\n" << std::endl;
    }
    catch (const std::exception&)
    {
      std::cout << "ERROR: Block sequence cannot be loaded from '" << file_name << "' file.\n" << std::endl;
    }
  }
  else
  {
    std::cout << "File '" << file_name << "' is missing.\n" << std::endl;
  }
}

bool get_blocks_from_file(std::string &file_name, block_processor::sequence_list &stored_blocks)
{
  std::ifstream parameters_stream(file_name, std::ios::in);
  std::string block_line;

  if (!parameters_stream.is_open()) { return false; }

  std::istringstream line_stream;
  while (getline(parameters_stream, block_line)) {
    std::pair<std::string, std::vector<double>> block_command = get_block_command_from_text(block_line);
    stored_blocks.push_back(block_command);
  }
  parameters_stream.close();
  return true;
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