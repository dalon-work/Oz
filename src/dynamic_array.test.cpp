
#include "oz/dynamic_array.h"
#include "catch2/catch.hpp"

using namespace oz;

TEST_CASE("Dynamic Array")
{

   dynamic_array<int> a;

   REQUIRE(a.size() == 0);
   REQUIRE(a.empty());

}
