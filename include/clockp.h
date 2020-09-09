#ifndef CLOCKP_H
#define CLOCKP_H

#ifdef __cplusplus
    extern "C"
    {
#endif

#include <stdint.h>
#include <stdbool.h>



struct time_res_t
{
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
};


void time_res_pack(
    const struct time_res_t *const input,
    uint8_t *const output
);

void time_res_unpack(
    const uint8_t *const input,
    struct time_res_t *const output
);

#ifdef __cplusplus
    }
#endif


#endif /* CLOCKP_H */