#pragma 
#include "stdafx.h"
#include "block.h"
#include <string>

class lim : public block, public self_registered_in_factory<lim>
{
private:
  double initial_value_1_;
  double initial_value_2_;
public:
  lim(const std::vector<double>& parameters);
  double calc(double input) override;

  static std::unique_ptr<block> CreateMethod(const std::vector<double>& parameters) {
    return std::make_unique<lim>(parameters);
  }
  static std::string GetFactoryName() { return "lim"; }
};
