#include "stdafx.h"
#include "block_lim.h"
#include "block.h"
#include "self_registered_in_factory.h"
#include <algorithm>

lim::lim(const std::vector<double>& parameters) : block(GetBlockTypeName(), 2, parameters)
{
  initial_value_1_ = parameters[0];
  initial_value_2_ = parameters[1];
}

double lim::calc(double input)
{
  is_blocktype_registered_;
  double ret = std::clamp(input, initial_value_1_, initial_value_2_);
  //if (input < initial_value_1_)
  //  ret = initial_value_1_;

  //if (input > initial_value_2_)
  //  ret = initial_value_2_;
  return ret;
}
