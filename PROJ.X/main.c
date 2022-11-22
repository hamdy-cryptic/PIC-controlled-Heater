


#include <xc.h>
#include "config.h"
#include <pic16f877a.h>
#include "ssd.h"
#include "timer.h"
#include "adc.h"
#include "eeprom.h"
#include "heater.h"

#define _XTAL_FREQ 8000000
#define ON 1
#define OFF 0

unsigned short int temperature=0;




void __interrupt() isr ()
{
   switch (timer_ISR()){
           case '0': 
          temperature=temperature_read(2);
          save_temp(temperature);
                break;
          case '1':
              set_temp_off();
              stop_timer(1);
                  break;
          case '2':
              alternate();
                  break;   
        default:
            if(INTF){
        alternate_on_off();
        INTF=0;
    }
            
   }             
  }
  
  
  

void main(void) {

//    TRISB0=0;TRISB1=0;TRISB2=0; //debugging
//    RB0=0;RB1=0;RB2=0;
    TRISB=0;
    TRISB |=0b00110001; //POWER/UP/DOWN buttons
    TRISB1=0; //heater led
    LED=0;
    PORTB=0;
    TRISC &=0b11011011; //Heater/Cooler pins
    heater=0;
    cooler=0;
    TRISD=0;           //7 Segment pins
    PORTD=0;
    TRISA |= 0b00000100; //Temp Sensor Pin
    TRISA &= 0b11001111; //7 Segment Control
    PORTA=0;
    ADC_Init();          //initiate ADC
    INTE=1;
    INTEDG=0;
    GIE=1;               //Enabling Interrupts
    PEIE=1;
    start_timer(0,100);  //Starting temp timer
    start_timer(2,1000); //Starting blink timer


    while(1)
     { 
     while (ON_OFF_FLAG){
        while(temp_setting_mode){
            heater=0;
            cooler=0;
            LED=0;
            segment_display_blink(temp_set);
            check_active_button();  
        }
        segment_display(temperature);
        check_temp();  
        check_active_button();
        
    
     }
      off();    
     }
    return;
}
