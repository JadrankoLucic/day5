// tool.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <ostream>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>
#include "block.h"
#include "menus.h"

//bool get_blocks_from_file(std::string &file_name, block_processor::sequence_list &stored_blocks);
//void load_from_file(block_processor &bp, std::string &file_name, block_processor::sequence_list &stored_blocks);
//bool save_sequence_to_file(block_processor &bp, std::string file_name);

int main(int argc, char *argv[]) {

  block_processor bp;
  //block_processor::sequence_list stored_blocks_;
  std::string block_sequence_file_name = BLOCK_SEQUENCE_FILE;

  //check passed file
  if (argc > 1) {
    // This will print the first argument passed to your program
    block_sequence_file_name = argv[1];
    std::cout << "Passed file is used: '" << block_sequence_file_name << "'.\n" << std::endl;
  }
  else
  {
    std::cout << "Default file is used: '" << block_sequence_file_name << "'.\n" << std::endl;
  }

  //load_from_file(bp, block_sequence_file_name, stored_blocks_);
  load_from_file(bp, block_sequence_file_name);
  int user_input = 0;
  //std::cout << MAIN_MENU << std::endl;
  //user_input = get_number_from_console("Please enter a valid number: ");

  do {
    std::cout << MAIN_MENU << std::endl;
    user_input = get_number_from_console("Please enter a valid number: ");

    switch (user_input)
    {
    case 1:
    {
      //show available block types
      show_available_block_types();
      press_enter_to_go_back();
      break;
    }
    case 2:
    {
      //show block sequence
      show_block_sequence(bp);
      press_enter_to_go_back();
      break;
    }
    case 3://add new block
    {
      if (add_new_block(bp))
        std::cout << "\nNew block added.\ ";
      else
        std::cout << "\nERROR: New block is NOT added.\ ";
      press_enter_to_go_back();
      break;
    }
    case 4://calc seuence
    {
      calc_sequence(bp);
      press_enter_to_go_back();
      break;
    }
    case 5://Remove block from sequence
    {
      remove_block_from_sequence(bp);
      press_enter_to_go_back();
      break;
    }
    case 6://Save block sequence to file
    {
      save_sequence_to_file(bp, block_sequence_file_name);
      press_enter_to_go_back();
      break;
    }
    case 7://Load block sequence from file
    {
      //load_from_file(bp, block_sequence_file_name, stored_blocks_);
      load_from_file(bp, block_sequence_file_name);
      press_enter_to_go_back();
      break;
    }
    default:
      system("cls");
      std::cout << "\nNumber is NOT valid.\ ";
      press_enter_to_go_back();
      break;
    }
    //std::cout << MAIN_MENU << std::endl;
    //user_input = get_number_from_console("Please enter a valid number: ");
  } while (user_input != 0);

  return 0;
}

//void load_from_file(block_processor &bp, std::string &file_name, block_processor::sequence_list &stored_blocks)
//{
//  system("cls");
//  if (get_blocks_from_file(file_name, stored_blocks))
//  {
//    try
//    {
//      bp.load(stored_blocks);
//      std::cout << "Block sequence is loaded from '" << file_name << "' file.\n" << std::endl;
//    }
//    catch (const std::exception&)
//    {
//      std::cout << "Error: Block sequence cannot be loaded '" << file_name << "' file.\n" << std::endl;
//    }
//  }
//  else
//  {
//    std::cout << "File '" << file_name << "' is missing.\n" << std::endl;
//  }
//}
//
//bool get_blocks_from_file(std::string &file_name, block_processor::sequence_list &stored_blocks)
//{
//  std::ifstream parameters_stream(file_name, std::ios::in);
//  std::string block_line;
//
//  if (!parameters_stream.is_open()) { return false; }
//
//  std::istringstream line_stream;
//  while (getline(parameters_stream, block_line)) {
//    //std::cout << block_line << std::endl;
//    std::pair<std::string, std::vector<double>> block_command = get_block_command_from_text(block_line);
//    stored_blocks.push_back(block_command);
//  }
//  parameters_stream.close();
//  return true;
//}
//
//void save_sequence_to_file(block_processor &bp, std::string file_name)
//{
//  system("cls");
//
//  std::ofstream parameters_stream(file_name, std::ios::trunc);
//  if (!parameters_stream.is_open()) { std::cout << "\nBlock sequence is NOT saved to file: " << file_name; }
//
//  auto command_sequence = bp.get_sequence();
//  for (std::vector<std::string>::iterator it = command_sequence.begin(); it != command_sequence.end(); ++it)
//    parameters_stream << *it << std::endl;
//  parameters_stream.close();
//  std::cout << "\nBlock sequence is saved to file: " << file_name;
//}