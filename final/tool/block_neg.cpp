#include "stdafx.h"
#include "block_neg.h"
#include "block.h"
#include "self_registered_in_factory.h"

neg::neg(const std::vector<double>& parameters) : block(GetBlockTypeName(), 0, parameters)
{
}

double neg::calc(double input)
{
  is_blocktype_registered_;
  return -1 * input;
}
