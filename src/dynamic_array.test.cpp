
#include "oz/dynamic_array.h"
#include "catch2/catch.hpp"

using namespace oz;

struct ThrowExceptionDuring10thConstruction
{
   static int count;

   int id;

   ThrowExceptionDuring10thConstruction()
   {
      id = count;
      if (count == 10) {
         throw std::runtime_error("Cannot construct");
      }
      count++;
   }

   ~ThrowExceptionDuring10thConstruction()
   {
      count--;
   }
};

int ThrowExceptionDuring10thConstruction::count = 0;

TEST_CASE("dynamic array")
{
   SECTION("An empty dynamic array") 
   {
      dynamic_array<int> a;
      REQUIRE(a.size() == 0);
      REQUIRE(a.empty());
      REQUIRE(a.data() == nullptr);
      REQUIRE(sizeof(a) == sizeof(int*) + sizeof(size_t)); // This needs to be a bit smarter?
      //REQUIRE(a.allocator().bytes == 0); Save this one for later
   }

   SECTION("Construction Fails")
   {
      REQUIRE_THROWS_AS(dynamic_array<ThrowExceptionDuring10thConstruction>(20), std::runtime_error);
      // REQUIRE(a.size() == 0);
      // REQUIRE(a.empty());
      // REQUIRE(a.data() == nullptr);
      REQUIRE(ThrowExceptionDuring10thConstruction::count == 0);
   }
}
