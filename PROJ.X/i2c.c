 
#include <xc.h>
#include <pic16f877a.h>
#include "i2c.h"
#define _XTAL_FREQ 8000000


void i2c_master_init(void) {

    TRISC3= 1;
    TRISC4= 1;
    SSPCON2 = 0x00;
    SSPSTAT = 0x00;
    SSPEN  = 1;
    SSPM3 = 1;
    SSPM2 = 0;
    SSPM1 = 0;
    SSPM0 = 0;
    SSPADD = ((_XTAL_FREQ / 4) / I2C_BAUDRATE) - 1;
}

void i2c_start(void) {
    i2c_wait();
    SEN = 1;
}

void i2c_stop(void) {
    i2c_wait();
    PEN = 1;
}

void i2c_restart(void) {
    i2c_wait();
    RSEN = 1;
}

void i2c_wait(void) {
    while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
}

void i2c_ack(void) {
    ACKDT = 0;
    i2c_wait();
    ACKEN = 1;
}

void i2c_nack(void) {
    ACKDT = 1;
    i2c_wait();
    ACKEN = 1;
}

uint8 i2c_write_slave_address_with_write_req(uint8 address) {
    i2c_wait();
    SSPBUF = (address << 1);
    while(!SSPIF);
    SSPIF = 0;
    return ACKSTAT;
}

uint8 i2c_write_slave_address_with_read_req(uint8 address) {
    i2c_wait();
    SSPBUF = ( (address << 1) | 1);
    while(!SSPIF);
    SSPIF = 0;
    return ACKSTAT;
}

uint8 i2c_master_write(uint8 data) {
    i2c_wait();
    SSPBUF = data;
    while(!SSPIF);
    SSPIF = 0;
    return ACKSTAT;
}

uint8 i2c_master_read(void) {
    i2c_wait();
    RCEN = 1;
    while(!SSPIF);
    SSPIF = 0;
    i2c_wait();
    return SSPBUF;
}