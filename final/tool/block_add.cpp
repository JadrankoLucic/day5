#include "stdafx.h"
#include "block_add.h"
#include "block.h"
#include "self_registered_in_factory.h"

#pragma region add
add::add(const std::vector<double>& parameters) : block(GetFactoryName(), 1, parameters)
{
  initial_value_ = parameters[0];
}

double add::calc(double input)
{
  is_blocktype_registered_;
  return initial_value_ + input;
};

std::string self_registered_in_factory<add>::description_ = "Summarize input with parameter value. Example: add 5";
#pragma endregion add