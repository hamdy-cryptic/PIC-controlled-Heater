

#include <xc.h>
#include "ssd.h"
#include <pic16f877a.h>

//Function Build

void segment_display (unsigned short int x){
    unsigned int a1,a2=1;
    unsigned char binary_pattern[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
   a1 = ((x/10)%10);  
   a2 = (x%10);
   s2=0; s1=1;
   PORTD = binary_pattern[a2];
    __delay_ms(10);
    s2=1; s1=0;
   PORTD = binary_pattern[a1];
   __delay_ms(10);
   s1=1;
  }

void segment_display_off(void){
    s2=0; s1=1;
   PORTD = 0;
    __delay_ms(10);
    s2=1; s1=0;
   PORTD = 0;
   __delay_ms(10);
   s1=1;
}

void segment_display_blink (unsigned short int x){
    if(blink){
        segment_display(x);
  }
    else {
        segment_display_off();
    }
}

void set_blink(){
    blink=1;
}

void alternate(){
    if(blink==1)
        blink=0;
    else if(blink==0)
        blink=1;
}