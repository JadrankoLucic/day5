#pragma once
#include "stdafx.h"
#include "block.h"
#include <string>

class mult : public block, public self_registered_in_factory<mult>
{
private:
  double initial_value_{};
public:
  mult(const std::vector<double>& parameters);
  double calc(double input) override;

  static std::unique_ptr<block> CreateMethod(const std::vector<double>& parameters) {
    return std::make_unique<mult>(parameters);
  }

  inline static const char* name = "mult";
  inline static const char* description = "Multiply input value with parameter value. Example: mult 5";
};