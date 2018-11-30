#pragma 
#include "stdafx.h"
#include "block.h"
#include <string>

class queq : public block, public self_registered_in_factory<queq>
{
private:
 double initial_value_a_;
 double initial_value_b_;
 double initial_value_c_;
public:
  queq(const std::vector<double>& parameters);
  double calc(double input) override;

  static std::unique_ptr<block> CreateMethod(const std::vector<double>& parameters) {
    return std::make_unique<queq>(parameters);
  }

  inline static const char* name = "queq";
  inline static const char* description = "Quadratic equation (ax^2 + bx + c). Example: queq 1 2 3";
};
