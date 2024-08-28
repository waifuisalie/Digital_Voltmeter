#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "my_lib.h"
#define F_CPU	16000000


volatile uint16_t adc_value = 0;		// initiate the variable

const uint8_t num_table[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

void display();

int main(void) {
	// config
	DDRD = 0xFF;
	DDRB = 0x0F;
	ADMUX = 0x40;
	ADCSRA = 0xCF;		// start converting
	sei();
	
	int digit[4];
	
	while (1)
	{
		float voltage = ((adc_value / 1024.0) * 5.0) * 1000.0;
		
		digit[0] = voltage / 1000;
		digit[1] = (voltage / 100) % 10;
		digit[2] = (voltage / 10) % 10;
		digit[3] = voltage % 10;
		
		for (int i = 0; i < 4; i++) {
			display(digit[i], i);
			_delay_ms(1);
		}
	}
	return 0;
}

void display(int num, int digit_pos) {

	// resetting the displays
	for (int i=0; i < 4; i++) {
		clr_bit(PORTB, i);
	}

	// passing the number to PORTD
	PORTD = num_table[num];

	// displaying it
	if (digit_pos == 0) {
		set_bit(PORTD, digit_pos);
		set_bit(PORTD, 7);
		
		}	else {
		set_bit(PORTD, digit_pos);
	}
}

ISR(ADC_vect){
	adc_value = ADC;			// saving adc`s value
	set_bit(ADCSRA, 6);			// turning it on again so I can start converting.
}