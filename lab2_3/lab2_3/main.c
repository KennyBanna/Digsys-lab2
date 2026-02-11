/*
 * lab2_3.c
 *
 * Created: 2026-02-09 18:23:58
 * Author : Oskar
 */ 

#include <avr/io.h>


// Home Assignment 3.1
// How do you configure Timer 3 to generate a Fast PWM signal with ICR3 as top? Look at
// TCCR3A and TCCR3B register in the data sheet
void set_compare_outputmode_to_PWM(){
	TCCR3A |= (1 << 7); // COM3A1 to 1
	TCCR3A &= ~(1 << 6);// COM3A0 to 0
	TCCR3A |= (1 << 5); // COM3B1 to 1
	TCCR3A &= ~(1 << 4);// COM3B0 to 0	
}
 
void set_wave_form_mode_to_PWM_top_ICR3(){

	// WGM3n = 1110 from data sheet page 189
	
	// WGM33 = TCCR3B & (1 << 4)
	// WGM32 = TCCR3B & (1 << 3)
	// WGM31 = TCCR3A & (1 << 1)
	// WGM30 = TCCR3A & (1 << 0)
	TCCR3B |= (1 << 4);
	TCCR3B |= (1 << 3);
	TCCR3A |= (1 << 1);
	TCCR3A &= ~(1 << 0);
	
}

// Home assignment 3.2
void configure_timer3_prescaler_value_1024(){
	//CS32 CS31 CS30
	//Sit on TCCR3B [2:0] 1024 is 101
	TCCR3B |= (1 << 2);
	TCCR3B &= ~(1 << 1);
	TCCR3B |= (1 << 0);
}

// Home assignment 3.3
void configure_Pin_PB6_to_output(){
	DDRB |= (1 << PORTB6);
}

void timer3_init(){
	set_compare_outputmode_to_PWM();
	set_wave_form_mode_to_PWM_top_ICR3();
	configure_timer3_prescaler_value_1024();
	configure_Pin_PB6_to_output();
}

void set_pulse(uint16_t pulse_value){
	OCR3AL = pulse_value;
	OCR3AH = (pulse_value >> 8);
}

void set_period(uint16_t period){
	// sets input capture register ICR3
	ICR3L = period;		 // Sets ICR3[7:0]
	ICR3H = (period >> 8); // Sets ICR3[15:8]
}

int main(void)
{
	timer3_init();
	set_pulse(0x0FFF);
	set_period(0xFFFF);
	
	while(1);
}

