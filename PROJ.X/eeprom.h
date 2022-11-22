
#ifndef _EEPROM_H
#define _EEPROM_H

#include "Typdefs.h"
#include "i2c.h"
#define EEPROM_ADDRESS 0x50

void eeprom_write(uint8 address, uint8 data);
uint8 eeprom_read(uint8 address);


#endif