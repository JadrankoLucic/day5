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
  double initial_value_{};
public:
  add(const std::vector<double>& parameters);
  double calc(double input) override;

  static std::unique_ptr<block> CreateMethod(const std::vector<double>& parameters) {
    return std::make_unique<add>(parameters);
  }

  inline static const char* name = "add";
  inline static const char* description = "Summarize input with parameter value. Example: add 5";
};
