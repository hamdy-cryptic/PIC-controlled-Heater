
#ifndef	_ssd_h
#define  _ssd_h

#define _XTAL_FREQ 4000000
#define s1 RA5
#define s2 RA4

//Global Variables

unsigned char blink=1;

//Declaration

void segment_display (unsigned short int x);
void segment_display_off(void);
void segment_display_blink (unsigned short int x);
void set_blink();
void alternate();




#endif 

 
