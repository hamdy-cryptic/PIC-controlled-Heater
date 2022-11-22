


#ifndef	_adc_h
#define  _adc_h
#define _XTAL_FREQ 8000000

//=================================
//-----[ Globals ]-----
unsigned short AN0RES=0;
float  Voltage;
//=================================
//-----[ Functions Prototypes ]----
void ADC_Init();
unsigned short ADC_Read(unsigned char);
unsigned short int temperature_read(unsigned char);
//=================================
 

#endif 

 
