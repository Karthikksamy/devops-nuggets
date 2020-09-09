#ifndef CLOCKP_HELPER_H
#define CLOCKP_HELPER_H

#include <stdint.h>

/*!
  is_little_endian - Helper function to check the endianness of the system

*/
static inline bool is_little_endian(){
    volatile uint32_t num = 1;
    uint8_t *lsb = (uint8_t*)&num;
    return (*lsb) == 1;
}

/*!
Set the given field  

1. create a template of 1's for given length
2. Set the field on the mask, so that it is only of given length
3. move the field to given start position

*/

static inline uint64_t encode_bitmask(uint64_t field, uint8_t start, uint8_t len, uint32_t offset){
    
    return ( ( (((uint64_t)(0x1) << len)-1) \
        & (field-offset) ) \
        << start );           
}

/*! extract_field - 

    1. create a template of 1's for given length of field - (((uint64_t)(0x1) << len)-1)
    2. move the field to given start position             - << start
    3. Extract the field using mask,                      - & *(uint64_t*)buffer
    4. move back the extracted field to start             - >> start
    5. add the offset to extracted data     

*/

static inline uint64_t extract_field(uint8_t *buffer, uint8_t start, uint8_t len, uint32_t offset){
    
    return ( ( ( ( (((uint64_t)(0x1) << len)-1) \
        << start) \
        & *(uint32_t*)buffer ) \
        >> start ) \
        + offset);           
}

/*! extract_field with 8Byte buffer as input- 

    1. create a template of 1's for given length of field - (((uint64_t)(0x1) << len)-1)
    2. move the field to given start position             - << start
    3. Extract the field using mask,                      - & *(uint64_t*)buffer
    4. move back the extracted field to start             - >> start
    5. add the offset to extracted data     

*/
static inline uint64_t extract_field_8b(uint8_t *buffer, uint8_t start, uint8_t len, uint32_t offset){
    
    return ( ( ( ( (((uint64_t)(0x1) << len)-1) \
        << start) \
        & *(uint64_t*)buffer ) \
        >> start ) \
        + offset);           
}

#endif /* CLOCKP_HELPER_H */