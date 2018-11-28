#include "stdafx.h"
#include "block.h"
#include <vector>
//#include <iostream>
#include <algorithm>
#include <numeric>
#include <sstream>
#include "menus.h"

#pragma region block
block::block(std::string block_type_name, int number_of_parameters, const std::vector<double>& parameters)
{
  if (parameters.size() != number_of_parameters)
    throw std::invalid_argument("Wrong number of arguments");
  parameters_ = parameters;
  block_type_name_ = block_type_name;
}

std::string block::get_command()
{
  std::string arguments = std::accumulate(parameters_.begin(), parameters_.end(), std::string(),
  [](std::string &args, double &par)
  {
    return args.empty() ? std::to_string(par) : args + " " + std::to_string(par);
  });

  return block_type_name_ + (arguments.empty() ? "" : " " + arguments);
}

//block::~block() {};
#pragma endregion block

#pragma region block_processor
block_processor::block_processor()
{

}

void block_processor::add_block(std::unique_ptr<block> &b)
{
  blocks_.push_back(std::move(b));
}

double block_processor::calc_all(double input) const
{
  double calculated_value = input;
  for (auto const& b : blocks_)
  {
    calculated_value = (*b).calc(calculated_value);
  }
  return calculated_value;
}

std::vector<std::string> block_processor::get_sequence()
{
  std::vector<std::string> temp_vector;
  temp_vector.reserve(blocks_.size());
  std::transform(blocks_.begin(), blocks_.end(), std::back_inserter(temp_vector), [](std::unique_ptr<block> const &b)
  {
    return (*b).get_command();
  });
  return temp_vector;
}

void block_processor::load(sequence_list sl)
{
  blocks_.clear();
  for (sequence_list::iterator it = sl.begin(); it != sl.end(); ++it) {
    const std::string block_name = (*it).first;
    const std::vector<double> parameter_values = it->second;
    std::unique_ptr<block> bl = block_factory::Create(block_name, parameter_values);
    blocks_.push_back(std::move(bl));
  }
}

bool block_processor::load_from_stream(std::istream &is)
{
  //check streams
  if (!is.good()) { return false; }

  sequence_list stored_blocks;
  std::string block_line;
  std::istringstream line_stream;
  while (std::getline(is, block_line)) {
    const std::pair<std::string, std::vector<double>> block_command = get_block_command_from_text(block_line);
    stored_blocks.push_back(block_command);
  }
  load(stored_blocks);
  return true;
}

bool block_processor::remove_block(unsigned int index)
{
  if (index > blocks_.size())
    return false;
  blocks_.erase(blocks_.begin() + index - 1);
  return true;
}

bool block_processor::bulk_calc(std::istream &is, std::ostream &os) const
{
  //check streams
  if (!os.good() || !is.good()) { return false; }

  //load inputs from input stream
  double input_value;
  std::vector<double> inputs_for_calc;
  std::string input_line;

  std::istringstream line_stream;
  while (getline(is, input_line)) {
    std::stringstream input_ss(input_line);
    if (input_ss >> input_value)
      inputs_for_calc.push_back(input_value);
    else
      return false;
  }

  //calculate each input value and send to output stream
  for (std::vector<double>::iterator it = inputs_for_calc.begin(); it != inputs_for_calc.end(); ++it)
    os << calc_all(*it) << std::endl;

  return true;
}

std::pair<std::string, std::vector<double>> block_processor::get_block_command_from_text(std::string command_text)
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
#pragma endregion block_processor

#pragma region block_factory
using TBlockCreateMethod = std::unique_ptr<block>(*)(const std::vector<double>& parameter);

std::map<std::string, block_meta> block_factory::create_methods_;

bool block_factory::Register(const std::string block_name, const std::string block_description, TBlockCreateMethod funcCreateBlock)
{
  if (auto it = create_methods_.find(block_name); it == create_methods_.end())
  { 
    create_methods_[block_name] = block_meta(block_description, funcCreateBlock);
    //std::cout << "LOG: block_factory::Register for block: " + block_name << std::endl;
    return true;
  }
  return false;
}

std::unique_ptr<block> block_factory::Create(const std::string& block_name, const std::vector<double>& parameters)
{
  if (auto it = create_methods_.find(block_name); it != create_methods_.end())
  {
    //std::cout << "LOG: block_factory::Create for block: " + block_name << std::endl;
    return it->second.GetCreateMethod()(parameters); // call the createFunc
  }
  return nullptr;
}

std::vector<std::string> block_factory::GetBlockTypes()
{
  //Vector of int to store values
  std::vector<std::string> temp_vector;
  temp_vector.reserve(create_methods_.size());

  //First solution: Copy all value fields from map to a vector using transform() & Lambda function
  //std::transform(create_methods_.begin(), create_methods_.end(), std::back_inserter(temp_vector), [](std::pair<std::string, block_meta> const &m)
  //{
  //  return m.first + " : " + m.second.Getdescription() + "\n";
  //});

  //Second solution: Copy all value fields from map to a vector using Lambda function
  std::for_each(create_methods_.begin(), create_methods_.end(), [&](std::pair<std::string, block_meta> const &m) {
    temp_vector.push_back(m.first + "\t" + m.second.Getdescription() + "\n");
  });

  return temp_vector;
}

#pragma endregion block_factory
