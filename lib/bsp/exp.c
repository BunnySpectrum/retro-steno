#include "exp.h"

// I2C reserves some addresses for special purposes. We exclude these from the scan.
// These are any addresses of the form 000 0xxx or 111 1xxx
static inline uint8_t reserved_addr(uint8_t addr) {
    return (addr & 0x78) == 0 || (addr & 0x78) == 0x78;
}

// void exp_search(uint8_t id){
//     // printf("\nExp search\n");
//     // printf("   0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\n");

//     for (int addr = 0; addr < (1 << 7); ++addr) {
//         if (addr % 16 == 0) {
//             ;
//             // printf("%02x ", addr);
//         }

//         // Perform a 1-byte dummy read from the probe address. If a slave
//         // acknowledges this address, the function returns the number of bytes
//         // transferred. If the address byte is ignored, the function returns
//         // -1.

//         // Skip over any reserved addresses.
//         int ret;
//         uint8_t rxdata;
//         if (reserved_addr(addr))
//             ret = -2;
//         else
//             ret = rs_i2c_read(id, addr, &rxdata, 1, 0);

//         // printf(ret < 0 ? "." : "@");
//         // printf(addr % 16 == 15 ? "\n" : "  ");
//     }
//     // printf("Done.\n");

// }

uint8_t exp_check(uint8_t id, uint8_t addr){
    i2cResponse_t scratch;
    scratch.length = 1;
    uint8_t data;
    scratch.data = &data;
    return rs_i2c_read(id, addr, &scratch, 0);
}