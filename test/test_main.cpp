#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <clockp.h>

uint8_t ip[4u]= {0x54, 0x86, 0xA1, 0xD5};
struct time_res_t unpack_result;

#if 0
void time_res_pack(
    const struct time_res_t *const input,
    uint8_t *const output
);

void time_res_unpack(
    const uint8_t *const input,
    struct time_res_t *const output
);
#endif

TEST_CASE("4Byte unpacking ","[time_res_unpack]")
{
	time_res_unpack(ip,&unpack_result);
	REQUIRE(unpack_result.year==2020);
	REQUIRE(unpack_result.month==6);
	REQUIRE(unpack_result.day==10);
	REQUIRE(unpack_result.hour==15);
	REQUIRE(unpack_result.minute==20);
	REQUIRE(unpack_result.minute==26);
}


#if 0
SCENARIO("4Byte unpacking ","[time_res_unpack]"){

	GIVEN("clock protocol unpacked "){
		struct time_res_t unpack_result;

		WHEN("4Byte value given"){
			time_res_unpack({0x54, 0x86, 0xA1, 0xD5},&unpack_result);

			THEN("Result is "){
				REQUIRE(unpack_result.year==2020);
			}

		}
	}
}

Karthik@MacBook-Pro-3 part_1 % g++ -c test.cpp  -std=c++17 -I.
Karthik@MacBook-Pro-3 part_1 % g++ -o runme test.o clockp.o
Karthik@MacBook-Pro-3 part_1 % g++ -c clockp.c -std=c++17 -I.

#endif