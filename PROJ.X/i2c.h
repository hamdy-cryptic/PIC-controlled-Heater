

#ifndef I2C_H
#define	I2C_H

#include "Typdefs.h"
#define I2C_BAUDRATE 9600
void i2c_master_init(void);
void i2c_start(void);
void i2c_stop(void);
void i2c_restart(void);
void i2c_wait(void);
void i2c_ack(void);
void i2c_nack(void);
uint8 i2c_write_slave_address_with_write_req(uint8 address);
uint8 i2c_write_slave_address_with_read_req(uint8  address);
uint8 i2c_master_write(uint8 data);
uint8 i2c_master_read(void);









#endif

