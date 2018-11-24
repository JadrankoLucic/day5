#pragma once
#include "stdafx.h"
#include "block.h"
#include <string>

class add :
  //derived from base block class
  public block,
  //derived from base block class
  public self_registered_in_factory<add>
{
private:
  double initial_value_;
public:
  add(const std::vector<double>& parameters);
  double calc(double input) override;

  static std::unique_ptr<block> CreateMethod(const std::vector<double>& parameters) {
    return std::make_unique<add>(parameters);
  }
  static std::string GetFactoryName() { return "add"; }
};
