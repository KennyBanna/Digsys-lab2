/*
 * lab2_1_2.c
 *
 * Created: 2026-02-06 15:25:06
 * Author : Oskar
 */ 

#include <avr/io.h>
#define F_CPU 160000
#include <util/delay.h>

// #define PINB 0x24
void uppg_1_();
void uppg_1_2_2();

int main(void)
{
	
	/*
	addr reg
	
	0x20 PINA
	0x21 DDRA
	0x22 PORTA
	0x23 PINB
	0x24 DDRB
	0x25 PORTB
	0x26 PINC
	0x27 DDRC
	0x28 PORTC
	0x29 PIND
	0x2A DDRD
	0x2B PORTD
	*/
	
    /* Replace with your application code */
    while (1) 
    {
		uppg_1_2_3();
						
	}

}
	
void uppg_1_(){
	*(volatile uint16_t*)0x0024 = 0x08; // DDRB (1<<3) 0x08DDRB =	0000 1000
	*(volatile uint16_t*)0x0025 |= 0x08;	// PORTB |=	0000 
}


void uppg_1_2_2(){
	DDRB = 0x08;
	PORTB |= 0x08;
}

// duoble debounced read of button 7 (B Btn)
uint8_t pind_bit7_button_read() {
	static uint8_t stable_state = 0;
	
	static uint8_t counter_up = 0;
	static uint8_t counter_down = 0;
	
	if (PIND & (1 << 7)) {
		counter_down++;
		
		if (counter_down > 10) {
			stable_state = 1;

			counter_up = 0;
		}
		
	} else {
		counter_up++;
		
		if (counter_up > 10) {
			stable_state = 0;
			
			counter_down = 0;
		}
	}
	
	return stable_state;
}
	


void uppg_1_2_3(){
	DDRD &= ~(1 << 7);	// set 7th bit of Port D to input (0)
	DDRB |= (1 << 4);	// set 4th bit of Port B to output (1)


	uint8_t last_button_state = 0;
	
	while(1){
		uint8_t new_button_state = pind_bit7_button_read();

		if (last_button_state == 0 && new_button_state == 1) {
			PORTB ^= (1 << 4); // toggle 4th bit of Port B (toggle LED)
		}
		
		last_button_state = new_button_state;
	}
	
	//  &= ~(1 << 4); // 1111 0111
}