/* Title: Assignment 3
 * 
 * Author: Nicholas LaJeunesse
 *
 */

#include "drvreg.h"

// Write value to register
void WriteReg(int RegAddr, int value){
	*((volatile unsigned char *)RegAddr) = value;
}

// Read value from register
unsigned char ReadReg(int RegAddr){
	return(*((volatile unsigned char *)RegAddr));
}

// Delay loops
void delay_loop(unsigned int delay_count){
	volatile unsigned int i, j;

	for(i = 0; i < delay_count; i++){
		for(j = 0; j < delay_count; j++);
	}
}

// Blink LED
void blink_LED(unsigned char LED){
	// Turn ON one LED at a time
	WriteReg(PORTB, ~LED); 

	// Delay
	delay_loop(300);

	// Turn OFF all LEDs
	WriteReg(PORTB, 0xff);
}

int main(void)
{
	for(;;){
	
		unsigned char i, j = 0x1;
	
		// Set PORTB DATA Direction (DDRB) as output
    	WriteReg(DDRB, 0xff);

		// Turn OFF all LEDS by writing 1's to PORTB
	    WriteReg(PORTB, 0xff);

		// Set PORTA DATA Direction (DDRA) as input
		WriteReg(DDRA, 0x0);

		// Enable internal pull-ups for all PORTA
		WriteReg(PORTA, 0xff);
	
		for(i = 0; i < 8; i++){
			if(ReadReg(PINA) != 0xff){
				if((~ReadReg(PINA) & j) == j){
					blink_LED(j);
				} else{
					delay_loop(300);
				}
			} else{
				blink_LED(j);
			}
			
			j <<= 1;
		}
	}
}
