
#ifndef	_timer_h
#define  _timer_h


//unsigned int freq=4000; // _XTAL_FREQ in KHz to be used in formulas
unsigned char T1=0; //increase by one each timer overflow
unsigned char *counter1=0; //number of overflows needed to pass required time
unsigned int *TMR1_REG=0; //value from which timer starts counting
unsigned char T2=0;
unsigned char *counter2=0;
unsigned char *TMR2_REG=0;
unsigned char T0=0;
unsigned char *counter0=0;
unsigned char *TMR0_REG=0;

//Declaration
unsigned long multiply(unsigned short x,unsigned short y);
void set_timer1(unsigned short time);
void set_timer2(unsigned short time);
void set_timer0(unsigned short time);
void stop_timer(unsigned char timer);
void restart_timer(unsigned char timer);
void start_timer(unsigned char timer , unsigned short time);
unsigned char timer_ISR();





#endif 

 
