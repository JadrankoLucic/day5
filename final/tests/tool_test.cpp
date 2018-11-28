#include "CppUnitTest.h"
#include <numeric>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "tests.h"
#include <sstream>
#include <algorithm>
#include "..\tool\block.h"

TEST_CLASS(test_tool)
{
public:
  TEST_METHOD(test_add)
  {
    block_processor bp;
    //std::vector<double> p;
    //p.push_back(5);
    std::unique_ptr<block> block_add = block_factory::Create("add", { 5 });
    bp.add_block(block_add);
    double res = bp.calc_all(5.);
    Assert::AreEqual(10., res);
  }

  TEST_METHOD(test_bulk_calc_with_add_block)
  {
    //create block processor with 'add' block
    const double add_parameter = 5.;
    block_processor bp;
    bp.add_block(block_factory::Create("add", { add_parameter }));

    //prepare input values
    std::vector<double> inputs{1,2,3};
    std::stringstream input_ss;
    for (auto it = inputs.begin(); it != inputs.end(); ++it)
      input_ss << *it << std::endl;

    //validate return value from bulk_calc
    std::stringstream output_ss;
    Assert::AreEqual(bp.bulk_calc(input_ss, output_ss), true);

    //validate output values
    double output_value;
    std::vector<double> outputs;
    std::string output_line;

    //check that all output values are doubles
    std::istringstream line_stream;
    while (std::getline(output_ss, output_line)) {
      std::stringstream output_value_ss(output_line);
      if (output_value_ss >> output_value)
        outputs.push_back(output_value);
      else
        Assert::Fail(L"output is wrong");
    }

    //check input and output sizes
    Assert::AreEqual(outputs.size() == 3, true);

    //compare and validate each value
    const bool is_equal = std::equal(outputs.begin(), outputs.end(), inputs.begin(),
      [add_parameter](double &vo, double &vi)
    {
      return add_parameter + vi == vo;
    });

    Assert::AreEqual(is_equal, true);
  }

  TEST_METHOD(test_load_sequence)
  {
    const double add_parameter = 5.;
    block_processor bp;

    std::stringstream input_ss("add 5\nmult 2");
    Assert::AreEqual(bp.load_from_stream(input_ss), true);

    //check bp size
    auto seq = bp.get_sequence();
    Assert::AreEqual(seq.size() == 2, true);
  }
};
