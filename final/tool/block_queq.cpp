#include "stdafx.h"
#include "block_queq.h"
#include "block.h"
#include "self_registered_in_factory.h"

queq::queq(const std::vector<double>& parameters) : block(GetBlockTypeName(), 3, parameters)
{
  initial_value_a_ = parameters[0];
  initial_value_b_ = parameters[1];
  initial_value_c_ = parameters[2];
}

double queq::calc(double input)
{
  is_blocktype_registered_; 
  return initial_value_a_ * input * input + initial_value_b_ * input + initial_value_c_;
}

//std::string self_registered_in_factory<queq>::description_ = "Quadratic equation (ax^2 + bx + c). Example: queq 1 2 3";
