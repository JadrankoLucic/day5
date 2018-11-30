#include "stdafx.h"
#include "block_mult.h"
#include "block.h"
#include "self_registered_in_factory.h"

#pragma region mult
mult::mult(const std::vector<double>& parameters) : block(GetBlockTypeName(), 1, parameters)
{
  initial_value_ = parameters[0];
}
double mult::calc(double input)
{
  is_blocktype_registered_;
  return initial_value_ * input;
}
#pragma endregion mult
