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
    std::unique_ptr<block> block_add = block_factory::create("add", { 5 });
    bp.add_block(std::move(block_add));
    double res = bp.calc_all(5.);
    Assert::AreEqual(10., res);
  }

  TEST_METHOD(test_lim_lower)
  {
    block_processor bp;
    std::unique_ptr<block> block_lim = block_factory::create("lim", { 5, 10 });
    bp.add_block(std::move(block_lim));
    double res = bp.calc_all(4.);
    Assert::AreEqual(5., res);
  }

  TEST_METHOD(test_lim_between)
  {
    block_processor bp;
    std::unique_ptr<block> block_lim = block_factory::create("lim", { 5, 10 });
    bp.add_block(std::move(block_lim));
    double res = bp.calc_all(7.);
    Assert::AreEqual(7., res);
  }

  TEST_METHOD(test_lim_upper)
  {
    block_processor bp;
    std::unique_ptr<block> block_lim = block_factory::create("lim", { 5, 10 });
    bp.add_block(std::move(block_lim));
    double res = bp.calc_all(17.);
    Assert::AreEqual(10., res);
  }
  TEST_METHOD(test_calc_all)
  {
    block_processor bp;
    std::unique_ptr<block> block_add = block_factory::create("add", { 2 });
    std::unique_ptr<block> block_mult = block_factory::create("mult", { 2 });
    bp.add_block(std::move(block_add));
    bp.add_block(std::move(block_mult));
    double res = bp.calc_all(1.);
    Assert::AreEqual(6., res);
  }

  TEST_METHOD(test_get_block_infos)
  {
    std::vector<std::string> abl = block_factory::get_block_infos();
    Assert::IsTrue(std::any_of(abl.begin(), abl.end(),
      [](std::string const& s)
    {
      return  s.compare(0, 3, "add") == 0;
    }));
  }

  TEST_METHOD(test_bulk_calc_with_add_block)
  {
    //create block processor with 'add' block
    const double add_parameter = 5.;
    block_processor bp;
    std::unique_ptr<block> bl = block_factory::create("add", { add_parameter });
    bp.add_block(std::move(bl));

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
