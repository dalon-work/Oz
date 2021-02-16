
#include "oz/dynamic_array.h"
#include "catch2/catch.hpp"

using namespace oz;

SCENARIO("dynamic array")
{
   GIVEN("An empty dynamic array") 
   {
      dynamic_array<int> a;
      REQUIRE(a.size() == 0);
      REQUIRE(a.empty());
      REQUIRE(a.data() == nullptr);
      REQUIRE(sizeof(a) == sizeof(int*) + sizeof(size_t)); // This needs to be a bit smarter?
      //REQUIRE(a.allocator().bytes == 0); Save this one for later
   }
}
