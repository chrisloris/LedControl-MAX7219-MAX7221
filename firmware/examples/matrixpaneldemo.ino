// This #include statement was automatically added by the Spark IDE.
#include "LedControl-MAX7219-MAX7221.h"

LedControl *led;
int phase = 0;
char message[64];
int messageLength = 0;
int myUptime = 0;

uint8_t data = A5;
uint8_t load = A4;
uint8_t myclock = A3;

void setup() {
    led = new LedControl(data,myclock,load,1); //DIN,CLK,CS,HowManyDisplays
    led-> shutdown(0,false); //Turn it on
    led-> setIntensity(0,1);
}

void loop() {

    if(phase==0){ //Message-loop starts
        myUptime = (int)(millis()/1000);
        sprintf(message,"Uptime %d:%02d", myUptime / 3600, (myUptime % 3600)/60); //update message
        messageLength = strlen(message); // ...and length
        led->tweenLetters(0,' ',message[phase]); //scroll from empty to 1 letter
    }

    if(phase<messageLength-1){ //next characters except last one
        led->tweenLetters(0,message[phase],message[phase+1]);
        phase++;
    }else if(phase==messageLength-1){//last character scrolls to empty
        led->tweenLetters(0,message[phase],' ');
        phase = 0; //restart message-loop
    }
}
