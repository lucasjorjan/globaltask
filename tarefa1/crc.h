#ifndef CRC_H
#define CRC_H

#include <stdint.h>

// cálculo de CRC
uint16_t CRC_CalculateCRC16(const uint8_t *Buffer, uint16_t Length);

#endif // CRC_H
