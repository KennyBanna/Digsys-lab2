/*
 * lab2_3.c
 *
 * Created: 2026-02-09 18:23:58
 * Author : Oskar
 */ 

#include <avr/io.h>

#define TOP			ICR3
#define COUNTER		TCNT3



void initialize_counter(){
	

}

// Home Assignment 3.1
// How do you configure Timer 3 to generate a Fast PWM signal with ICR3 as top? Look at
// TCCR3A and TCCR3B register in the data sheet
void set_wave_form_mode_to_PWM_top_OCR3(){

	// WGM3n = 1010 from data sheet page 189
	
	// WGM33 = TCCR3B & (1 << 4)
	// WGM32 = TCCR3B & (1 << 3)
	// WGM31 = TCCR3A & (1 << 1)
	// WGM30 = TCCR3A & (1 << 0)
	TCCR3B |= (1 << 4);
	TCCR3B &= ~(1 << 3);
	TCCR3A |= (1 << 1);
	TCCR3A &= ~(1 << 0);  
	
}

void set_counter(uint8_t value){
	
}


int main(void)
{
    /* Replace with your application code */
    while (1)
    {
		
    }
}

