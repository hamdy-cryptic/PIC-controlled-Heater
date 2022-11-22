

#include <xc.h>
#include "heater.h"
#include "ssd.h"
#include "timer.h"
#include "eeprom.h"



void check_temp(void){
    unsigned short int sum=0; //to add all 10 temperatures to get avg
    unsigned short int avg=0;
    for (char i=0;i<10;i++)
        sum=sum+past_temps[i];  //adding temps
    avg=sum/10;                  //calculate average
    if (avg<(temp_set-5))       // temperature logic for heater, cooler
    { 
    heater=1;
    cooler=0;
    if (blink==1)       // blink led when heater is on
        LED=1;
    else if(blink==0)
        LED=0;
    }
    else if(avg>(temp_set+5))
    { 
    cooler=1;
    heater=0;
    LED=1;
    }
    else            //default is off for all
    {heater=0;
    cooler=0;
    LED=0;
    }  
}

//.....................................................................

void save_temp(short temp){    //save temp sensor reading in net index of array
    past_temps[index]=temp;
                index++;
                if (index==10)
                    index=0;
}

//.....................................................................

void temp_setting_up(void){ 
   if(temp_setting_mode==0) temp_setting_mode=1; //first (up or down)button hit enters the setting mode 
   else if (temp_setting_mode==1){
       if(temp_set<75) temp_set+=5;
       else if (temp_set>=75) temp_set=75;
   }
}

//.....................................................................

void temp_setting_down(void){        //decrease set temp if in setting mode
    if(temp_setting_mode==0) temp_setting_mode=1;
    else if (temp_setting_mode==1){
       if(temp_set>35) temp_set-=5; }
}

//......................................................................

void set_temp_off(void){       // get out of temp setting mode into sensor mode
    temp_setting_mode=0;
    eeprom_write(0x00,temp_set);
}

//....................................................................

void check_active_button(void){
    if(UP==0) {
        __delay_ms(100);    // delay to reduce switch bouncing
        set_blink();        // ensure ssd is on
       stop_timer(1);       // stop timer 1 if already on 
       restart_timer(1);    // restart timer to get 5seconds again 
       start_timer(1,5000);   //start timer ticking
        temp_setting_up();}
       else if(DOWN==0) {
       __delay_ms(100);
       set_blink();
       stop_timer(1);
       restart_timer(1);
       start_timer(1,5000);
        temp_setting_down();}
      
}

//.......................................................................

void off(){
    if(ON_OFF_FLAG==0){
      cooler=0;
      heater=0;
      segment_display_off();
      }
 }

//..........................................................................
    
void alternate_on_off(){
    
    if(ON_OFF_FLAG==0)
     { 
        //temp_set=eeprom_read(0x00); (Problems in eeprom read function>> transforms written value at address to 0xA1)>> commented out because it affects the correct written value at eeprom... code is depedent on that temp_set variable is never reset...
        ON_OFF_FLAG=1;}
    else if (ON_OFF_FLAG==1)
    {   
        ON_OFF_FLAG=0;}
    else{
        
    }
}