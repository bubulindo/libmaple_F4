// Sample main.cpp file. Blinks the built-in LED, sends a message out
// USART2, and turns on PWM on pin 2.

#include "wirish.h"
#include "rng.h"
#include "rcc.h"



void setup() {
	uint32 test; 
    /* Set up the LED to blink  */

    pinMode(BOARD_GREEN_LED_PIN, OUTPUT);
    pinMode(BOARD_ORANGE_LED_PIN, OUTPUT);
    pinMode(BOARD_BLUE_LED_PIN, OUTPUT);
    pinMode(BOARD_RED_LED_PIN, OUTPUT);

    /* Turn on PWM on pin PWM_PIN */
//    pinMode(PWM_PIN, PWM);
//    pwmWrite(PWM_PIN, 0x8000);

 /* Send a message out USART2  */
//    Serial2.begin(9600);
//    Serial2.println("Hello world!");

    /* Send a message out the usb virtual serial port  */
    //SerialUSB.println("Hello!");
    
    rng_init(); 
	
    rng_enable();
//    togglePin(BOARD_BLUE_LED_PIN);
    
    
    while ( (test = rng_get_number()) < 3) {
		
//		if ()
			togglePin(BOARD_BLUE_LED_PIN);		
		/*
		if (check_PLL() >2)
			togglePin(BOARD_RED_LED_PIN);			
    	if (check_PLL() < 15)
			togglePin(BOARD_ORANGE_LED_PIN);*/
	}
}

void loop() {

//4,294,967,295
    togglePin(BOARD_GREEN_LED_PIN);
    delay(100);
    
    if (rng_get_number() < 2147483647UL) {
    	togglePin(BOARD_RED_LED_PIN);
    	delay(100);
    	}
    if (rng_get_number()  > 2147483647UL) {
    	togglePin(BOARD_BLUE_LED_PIN);
    	delay(100);
    	}
    //togglePin(BOARD_ORANGE_LED_PIN);
    //delay(100);


}

// Force init to be called *first*, i.e. before static object allocation.
// Otherwise, statically allocated objects that need libmaple may fail.
__attribute__((constructor)) void premain() {
    init();
}

int main(void) {
    setup();

    while (true) {
        loop();
    }

    return 0;
}
