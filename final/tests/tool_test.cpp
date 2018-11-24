#include "CppUnitTest.h"
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
    std::vector<double> p;
    p.push_back(5);
    std::unique_ptr<block> block_add = block_factory::Create("add", p);
    bp.add_block(block_add);
    double res = bp.calc_all(5.);
    Assert::AreEqual(10., res);
  }
};
