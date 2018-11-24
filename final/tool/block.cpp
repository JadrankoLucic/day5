#include "stdafx.h"
#include "block.h"
#include <vector>
#include <iostream>
#include <algorithm>

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
  std::string arguments;

  std::for_each(parameters_.begin(), parameters_.end(), [&](double const &par) {
    arguments += std::to_string(par) + " ";
  });

  return block_type_name_ + " " + arguments;
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

bool block_processor::remove_block(unsigned int index)
{
  if (index > blocks_.size())
    return false;
  blocks_.erase(blocks_.begin() + index - 1);
  return true;
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
