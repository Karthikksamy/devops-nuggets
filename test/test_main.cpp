#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <clockp.h>

uint8_t unpack_ip[8u]= {0x54, 0x86, 0xA1, 0xD5,0,0,0,0};
struct time_res_t unpack_result={0};


TEST_CASE("4Byte unpacking ","[time_res_unpack]")
{
	time_res_unpack(unpack_ip,&unpack_result);
	REQUIRE(unpack_result.year==2020);
	REQUIRE(unpack_result.month==9);
	REQUIRE(unpack_result.day==1);
	REQUIRE(unpack_result.hour==3);
	REQUIRE(unpack_result.minute==26);
	REQUIRE(unpack_result.second==53);
}


TEST_CASE("4Byte packing ","[time_res_pack]")
{
	struct time_res_t pack_ip = {2020,9,1,3,26,53};	
	uint8_t packed_op[4]={0,0,0,0};	

	time_res_pack(&pack_ip,packed_op);

	REQUIRE(*(uint32_t*)packed_op==0xd5a18654);
}

