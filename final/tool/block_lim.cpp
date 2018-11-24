#include "stdafx.h"
#include "block_lim.h"
#include "block.h"
#include "self_registered_in_factory.h"

lim::lim(const std::vector<double>& parameters) : block(GetFactoryName(), 2, parameters)
{
  initial_value_1_ = parameters[0];
  initial_value_2_ = parameters[1];
}

double lim::calc(double input)
{
  is_blocktype_registered_;
  double ret = input;
  if (input < initial_value_1_)
    ret = initial_value_1_;

  if (input > initial_value_2_)
    ret = initial_value_2_;
  return ret;
}

std::string self_registered_in_factory<lim>::description_ = "Limit between numbers. Example: lim 0 100";
