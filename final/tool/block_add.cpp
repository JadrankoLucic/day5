#include "stdafx.h"
#include "block_add.h"
#include "block.h"
#include "self_registered_in_factory.h"

#pragma region add
add::add(const std::vector<double>& parameters) : block(GetBlockTypeName(), 1, parameters)
{
  initial_value_ = parameters[0];
}

double add::calc(double input)
{
  //we have to have line below in order to trigger registration during class instantiation (before main)
  is_blocktype_registered_;
  return initial_value_ + input;
};

#pragma endregion add