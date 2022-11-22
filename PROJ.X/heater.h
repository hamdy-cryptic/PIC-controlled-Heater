#ifndef	_heater_h
#define  _heater_h

#define heater RC5
#define cooler RC2
#define LED RB1
#define UP RB4
#define DOWN RB5
#define POWER RB0

//Global Variables

unsigned char temp_set=60;  //set temp in setting mode
unsigned char past_temps[10]={0}; // store previous sensor readings to determine average
unsigned char index=0;  // used to navigate past temps
unsigned char temp_setting_mode=0;  // 0 for sensor mode // 1 for setting mode
unsigned char ON_OFF_FLAG= 0; //to power up heater when 1

//Declaration

void check_temp(void);
void save_temp(short temp);
void temp_setting_up(void);
void temp_setting_down(void);
void set_temp_off(void);
void check_active_button(void);
void off();
void alternate_on_off();

//Function Build


#endif 

 
