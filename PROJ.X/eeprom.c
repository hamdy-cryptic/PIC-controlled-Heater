

#include <xc.h>
#include "eeprom.h"   


void eeprom_write(uint8 address, uint8 data) {
    i2c_master_init();
    i2c_start();
    while(i2c_write_slave_address_with_write_req(EEPROM_ADDRESS))
    i2c_restart();
    i2c_master_write(address >> 8);
    i2c_master_write((uint8) address);
    i2c_master_write(data);
    i2c_stop();
}
uint8 eeprom_read(uint8 address) {
    i2c_master_init();
    uint8 data;
    i2c_start();
    while(i2c_write_slave_address_with_write_req(EEPROM_ADDRESS))
    i2c_restart();
    i2c_master_write(address >> 8);
    i2c_master_write((uint8) address);
    i2c_restart();
    i2c_write_slave_address_with_read_req(EEPROM_ADDRESS);
    data = i2c_master_read();
    i2c_nack();
    i2c_stop();
    return data;
}