
#include <xc.h>
#include "timer.h"

//Function Build

unsigned long multiply(unsigned short x,unsigned short y){
    unsigned long sum=0;
    if (x>=y){
    for (unsigned short i=0;i<y;i++)
        sum=sum+x;
    }
    else if (x<y){
        for (unsigned short i=0;i<x;i++)
        sum=sum+y;
    }
    return sum;
}

//.....................................................................

void set_timer1(unsigned short time){  //time is in ms
     //Setting Timer Register Values
    unsigned long Time=multiply(time,1000); //convert to microseconds
    unsigned static int tmr1=0; //variables to be pointed at
    unsigned static char cntr1=0;
    TMR1CS=0; //Internal Clock Enabled (Fosc/4)
    T1OSCEN=0;
    T1CKPS0=0; //Setting Pre-scaler to 1
    T1CKPS1=0;
    TMR1_REG=&tmr1; //Default starting address point of tick counting
    //Resolution of 1 timer overflow is used in identifying pre-loaded TMR value
    unsigned int resolution= 65535;//(4*1000*(65535-tmr1))/freq; //in microseconds

     if (Time % resolution !=0){
        for (unsigned int i=50000;i>0;i--){ //keep reducing resolution time till a value fits for optimum accuracy
            if (Time%i==0){
                resolution=i;
                tmr1=-(resolution-65535);//note this is for 4MHz only (use (freq*resolution/4000)-65535) for others
                break;
            }
        }
    }
    else{
        tmr1=0;
        resolution= 65535;//for other frequencies, use (4*1000*(65535-tmr1))/freq
    }

      cntr1= Time/resolution;
      counter1=&cntr1;
      
//      if(*TMR1_REG==15535) //debugging
//          RB0=1;
//      if(*counter1==100)
//          RB2=1;
}

////...........................................................................

void set_timer2(unsigned short time){  //time is in ms
     //Setting Timer Register Values
    unsigned long Time=multiply(time,1000); //convert to microseconds
    unsigned static char tmr2=0; //variables to be pointed at
    unsigned static char cntr2=0;
    T2CKPS0=1; //Setting Pre-scaler to 1:4
    T2CKPS1=0;
    TOUTPS0=1; //Setting Post_scaler to 1:16
    TOUTPS1=1;
    TOUTPS2=1;
    TOUTPS3=1;
    TMR2_REG=&tmr2; //Default starting point of tick counting
    PR2=255; //Default final TMR2 value to raise flag
    //Resolution of 1 timer overflow is used in identifying pre-loaded TMR value
    unsigned short resolution= 16320; //for other freqs, (4*16*4*1000*(PR2-tmr2))/freq; //in microseconds

      if (Time % resolution !=0){
        for (unsigned short i=15650;i>0;i--){ //keep reducing resolution time till a value fits for optimum accuracy
            if (Time%i==0){
                resolution=i;
                tmr2=-(resolution/64-PR2);//(use (-(freq*resolution/(64*8000))-255) for others freqs
                break;
            }
        }
    }
    else{
        tmr2=0;
        resolution=510;
    }
     cntr2= Time/resolution;  
     counter2=&cntr2;

//      if(*TMR2_REG==11) //debugging
//          RB1=1;
//      if(*counter2==64)
//          RB0=1;
}

//..................................................................

void set_timer0(unsigned short time){  //time is in ms
     //Setting Timer Register Values
    unsigned long Time=multiply(time,1000); //convert to microseconds
    unsigned static char tmr0=0; //variables to be pointed at
    unsigned static char cntr0=0;
    PSA=0; //Prescaler to timer0 (not watchdog)
    PS0=0; //Setting Pre-scaler to 1:8
    PS1=1;
    PS2=0;
    T0CS=0; //Internal Clock Enabled (Fosc/4)
    T0SE=0;
    TMR0_REG=&tmr0; //Default starting point of tick counting
    //Resolution of 1 timer overflow is used in identifying pre-loaded TMR value
    unsigned short resolution= 2040; //for other freqs, (4*8*1000*(255-tmr0))/freq; //in microseconds
     if (Time % resolution !=0){
        for (unsigned short i=2039;i>0;i--){ //keep reducing resolution time till a value fits for optimum accuracy
            if ((Time)%i==0){
                resolution=i;
                tmr0=-((resolution/8)-255); //(use (-(freq*resolution/(8*4000))-255) for others
                break;
            }
        }
    }
    else{
        tmr0=0;
        resolution=2040;
    }
      cntr0= Time/resolution;
      counter0=&cntr0;
      
//      if(*TMR0_REG==5) //debugging
//          RB1=1;
//      if(*counter0==50)
//          RB2=1;
      
}

//...........................................................................

void stop_timer(unsigned char timer){
    if (timer==1){
        TMR1ON=0; //disable timer 1 
    }
    else if (timer==2){
        TMR2ON=0; //disable timer 2 
    }
    else if (timer==0){
        PSA=1;
    }
    else{
        
    }
}

//.......................................................................

void restart_timer(unsigned char timer){
    if (timer==1){
        T1=0; //restart timer 1 
    }
    else if (timer==2){
        T2=0; //restart timer 2 
    }
    else if (timer==0){
        T0=0;
    }
    else{
        
    }
}

//........................................................................

void start_timer(unsigned char timer , unsigned short time){ //time in ms
    if (timer==1){
        set_timer1(time);
        TMR1=*TMR1_REG; //Initial counting point
        TMR1IE=1; //Enable timer 1 interrupt
        TMR1ON=1; //Power up timer 1
    
    }
    else if (timer==2){     
        set_timer2(time);
        TMR2=*TMR2_REG; //Initial counting point
        TMR2IE=1; //Enable timer 2 interrupt
        TMR2ON=1; //Power up timer 2 
        
    }
    else if (timer==0){
        set_timer0(time);
        TMR0=*TMR0_REG; //Initial counting point
        TMR0IE=1;//Enable timer 0 interrupt
    }
    else{
        
    }
}

//..........................................................................

 unsigned char timer_ISR(){
      //timer interrupt procedure
    if (TMR1IF){
        T1++;  //increase timer ticks
        TMR1=*TMR1_REG;
        TMR1IF=0;  //pull timer flag down
        if (T1==(char)(*counter1)){
            T1=0;
            return '1';
        }
    }
    else if (TMR2IF){
        T2++;  //increase timer ticks
        TMR2=*TMR2_REG;
        TMR2IF=0;  //pull timer flag down
        if (T2==*counter2){
            T2=0;
            return '2';
        }
    }
    else if (TMR0IF){
         T0++;  //increase timer ticks
        TMR0=*TMR0_REG;
        TMR0IF=0;  //pull timer flag down
        if (T0==(char)(*counter0)){
            T0=0;
//            RB0=~RB0; //debugging
            return '0';
        }
    }
    
        return 'b';
    
}
