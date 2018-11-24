#pragma 
#include "stdafx.h"
#include "block.h"
#include <string>

class neg : public block, public self_registered_in_factory<neg>
{
private:
  //double initial_value_;
public:
  neg(const std::vector<double>& parameters);
  double calc(double input) override;

  static std::unique_ptr<block> CreateMethod(const std::vector<double>& parameters) {
    return std::make_unique<neg>(parameters);
  }
  static std::string GetFactoryName() { return "neg"; }
};
