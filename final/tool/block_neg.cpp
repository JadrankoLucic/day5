#include "stdafx.h"
#include "block_neg.h"
#include "block.h"
//#include <vector>
#include "self_registered_in_factory.h"

neg::neg(const std::vector<double>& parameters) : block(GetFactoryName(), 0, parameters)
{
}

double neg::calc(double input)
{
  is_blocktype_registered_;
  return -1 * input;
}

std::string self_registered_in_factory<neg>::description_ = "Negation of input value. Example: neg";
