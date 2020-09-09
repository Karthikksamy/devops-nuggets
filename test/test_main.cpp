#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <clockp.h>

uint8_t ip[4u]= {0x54, 0x86, 0xA1, 0xD5};
struct time_res_t unpack_result={0};


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

