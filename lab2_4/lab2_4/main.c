/*
 * lab2_4.c
 *
 * Created: 2026-02-11 19:51:12
 * Author : Hoskrik
 */ 

#include <avr/io.h>

void ADC_enable(){
	ADCSRA |= (1 << ADEN); // aden = 7
}


void set_frequency_to_125khz(){
	ADCSRA |= (1 << 2);
	ADCSRA |= (1 << 1);
	ADCSRA |= (1 << 0);
}

void set_ADC_to_use_channel0(){
	ADMUX &= ~(1 << 4);
	ADMUX &= ~(1 << 3);
	ADMUX &= ~(1 << 2);
	ADMUX &= ~(1 << 1);
	ADMUX &= ~(1 << 0);
}

void set_adlar_to_right(){
	ADMUX &= ~(1 << 5);
}


// TODO: Avcc is tp supply voltage from a seperate pin
void set_ADC_to_use_AVcc(){
	ADMUX &= ~(1 << 7);
	ADMUX |= (1 << 6);
}

void adc_init(){
	ADC_enable();
	set_frequency_to_125khz();
	set_ADC_to_use_channel0();
	set_ADC_to_use_AVcc();
	set_adlar_to_right();
}

uint16_t read_adc(){
	ADCSRA |= (1 << ADSC);	// set start conversion bit to 1
	while ((ADCSRA & (1 << ADSC)) != 0) {} // wait until conversation is done
	
	uint16_t data = ADCH;
	data = data << 8;
	data |= ADCL;
	
	uint8_t low = ADCL; // DEBUG purposes only
	uint8_t high = ADCH; // Debug purposes only
	
	return data;
}

int main(void)
{
	DDRB = 0b11111111;
	PORTB |= (1 << 0);
	adc_init();
	
	
    /* Replace with your application code */
    while (1)
    {
		
 		if(read_adc() > 500){
 			PORTB = 0x00;
 		} else {
 			PORTB = 0xff;
 		}
	}
}

