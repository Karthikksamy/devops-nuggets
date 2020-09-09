#include <stdio.h>
#include <assert.h>
#include <string.h> //for memcpy


#include <clockp.h>
#include <clockp_helper.h>

#define YEAR_OFFSET (2000)
#define MAX_YEAR (63)
#define MAX_MONTH (12)
#define MAX_DAY (31)
#define MAX_HR (23)
#define MAX_MIN (59)
#define MAX_SEC (59)

#define BYTE_SZ_BITS (8)
#define BUFFER_SZ_BYTES (4)

/*!
  Serialize the given input structure to Byte stream
*/
void time_res_pack( const struct time_res_t *const input,
    				uint8_t *const output ) {
	uint64_t temp=0;
	/* Input validation */ 
	assert(input != NULL);
	assert(output != NULL);
	assert(input->year <= MAX_YEAR+YEAR_OFFSET ); 
	assert(input->month <= MAX_MONTH );
	assert(input->day <= MAX_DAY );
	assert(input->hour <= MAX_HR );
	assert(input->minute <= MAX_MIN);
	assert(input->second <= MAX_SEC);

	//clear the output variable
	temp = encode_bitmask(0,0,BUFFER_SZ_BYTES*BYTE_SZ_BITS,0);

	temp |= encode_bitmask(input->year, 0,6,2000);
	temp |= encode_bitmask(input->month, 6,4,0);
	temp |= encode_bitmask(input->day, 10,5,0);
	temp |= encode_bitmask(input->hour, 15,5,0);
	temp |= encode_bitmask(input->minute, 20,6,0);		
	temp |= encode_bitmask(input->second, 26,6,0);	

	//*output1 = output;
	memcpy(output, &temp, BUFFER_SZ_BYTES);
	//printf("Output %x \n", *(uint32_t *const)output);

	return;
}

/*!
  Deserialize the stream of Bytes into a 'c' structure

  ASSUMPTION: 
   Input pointer is of length 4B for simple C based implementation
   In the auto-generated version, the byte stream 

*/
void time_res_unpack( const uint8_t *const ip, struct time_res_t *const output){

	uint8_t input[8];
	assert(ip != NULL);
	assert(output != NULL);

	//TODO 1: To memcopy based on RAW stream size
	memcpy(input, ip, BUFFER_SZ_BYTES);

	// uint64_t extract_field(uint64_t buffer, uint8_t start, uint8_t len, uint32_t offset)
	output->year = extract_field(input, 0, 6, 2000);
	output->month = extract_field(input, 6, 4, 0);
	output->day = extract_field(input, 10, 5, 0);
	output->hour = extract_field(input, 15, 5, 0);
	output->minute  = extract_field(input, 20, 6, 0);
	output->second = extract_field(input, 26, 6, 0);

	return;
}

#ifdef INCLUDE_MAIN
int main(int argc, char *argv[] ){
	uint8_t packed_time_res[4u] = {0x54, 0x86, 0xA1, 0xD5}; 
	struct time_res_t time_res = {0};
	struct time_res_t ip = {2020,9,1,3,26,53};
	uint8_t packed_op[4]={0,0,0,0};

	time_res_pack(&ip, packed_op);

	printf("packed_op %x \n", *(uint32_t*)packed_op);

	time_res_unpack(packed_time_res, &time_res);
	printf("unpacked output :\n");
	printf("year : %d \n", time_res.year );
	printf("month : %d \n", time_res.month );
	printf("day : %d \n", time_res.day );
	printf("hour : %d \n", time_res.hour );
	printf("minutes : %d \n", time_res.minute );
	printf("sec : %d \n", time_res.second );

	assert(time_res.year == 2020); 
	assert(time_res.month == 9); 
	assert(time_res.day == 1); 
	assert(time_res.hour == 3); 
	assert(time_res.minute == 26); 
	assert(time_res.second == 53);


	return 0;	
}
#endif