#pragma once
#include <string>

inline const std::string MAIN_MENU =
"MAIN MENU:\n\n"
"Chose command (enter number):\n"
"1:\tShow available block types.\n"
"2:\tShow block sequence.\n"
"3:\tAdd new block.\n"
"4:\tRun block sequence.\n"
"5:\tRemove block from sequence.\n"
"6:\tSave block sequence to file.\n"
"7:\tLoad block sequence from file.\n"
"8:\tLoad and calculate inputs from file.\n"
"0:\tExit.\n";

inline const std::string BLOCK_SEQUENCE_FILE = "block_sequence.txt";

void press_enter_to_go_back();
void show_available_block_types();
unsigned int get_number_from_console(std::string caption);
double get_input_from_console(std::string caption);
std::string get_text_from_console(std::string caption);
void show_block_sequence(block_processor &bp);
bool add_new_block(block_processor &bp);
void calc_sequence(const block_processor &bp);
void remove_block_from_sequence(block_processor &bp);
void load_from_file(block_processor &bp, std::string &file_name);
void save_sequence_to_file(block_processor &bp, std::string file_name);
void load_and_calc_inputs_from_file(block_processor &bp);