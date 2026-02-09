/*
 * lab2_USART.c
 *
 * Created: 2026-02-08 16:16:16
 * Author : Oskar
 */ 

#include <avr/io.h>
const uint8_t* USCR0A_ptr = 0xc0;
const uint8_t* USCR0B_ptr = 0xc1;
const uint8_t* USCR0C_ptr = 0xc2;
const uint8_t* UBRR0L_ptr = 0xC4;
const uint8_t* UBRR0H_ptr = 0xC4 + 0x01;

#define USCR0A *USCR0A_ptr
#define USCR0B *USCR0B_ptr
#define USCR0C *USCR0C_ptr
#define USBRR0L *UBRR0L_ptr
#define USBRR0H *UBRR0H_ptr


void enable_transmitter() {
	USCR0B |= (1 << 4);
}

void enable_receiver() {
	USCR0B |= (1 << 3);
}

uint8_t is_data_register_empty() {
	return USCR0A & (1 << 5);
}

void set_data_len_to_8_bits() {
	//USCZ1[2:0] = 011
	USCR0C &= ~(1 << 1);	// USCZ1[0] = 0
	USCR0C |= (1 << 2);		// USCZ1[1] = 1
	USCR0B |= (1 << 2);		// USCZ1[2] = 1
}

uint8_t is_receive_complete() {
	return USCR0A & (1 << 7);
}

// Sets the USBS flag (USCR0C[3]) 
void set_num_stop_bits(uint8_t num){
	if(num == 2){
		USCR0C |= (1 << 3); // 1 = 2 stop bits
	} else if (num == 1) {
		USCR0C &= ~(1 << 3); // 0 = 1 stop bits
	}
}

// Home assignment 2.3
void set_baud_rate_to_2400(){
	// chosing 2400 for arbitrary number
	UBRR0L = 416;
	UBRR0H = (416 >> 8);
}


// Home assignment 2.3
void usart0_init(){
	
	enable_receiver(); 
	set_num_stop_bits(1);
	set_data_len_to_8_bits();
	set_baud_rate_to_2400();
	
}

int main(void)
{
    /* Replace with your application code*/

	//uint8_t* USART_reset = 0x20;
	//
	//*USART_reset = 0;
	
}
