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
  static std::string GetFactoryName() { return "queq"; }
};
