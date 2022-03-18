/*
 * pp_bku.c
 *
 * Created: 17.03.2022 15:01:20
 *  Author: m.gasratov
 */ 

void ports_init() {
	DDRA |= (1<<3) | (1<<4) | (1<<5) | (1<<6) | (1<<7);
	PORTA &= ~(1<<3) & ~(1<<4) & ~(1<<5) & ~(1<<6) & ~(1<<7);
	DDRB &= ~(1<<4);
	PORTB |= 1<<4;
	DDRC &= ~(1<<0) & ~(1<<1);
	PORTC |= (1<<0) | (1<<1);
	DDRC |= 1<<7;
	PORTC &= ~(1<<7);
	DDRD = 0;
	PORTD = 0xFF;
}


void arrayMooveToRight (uint8_t *array, uint8_t size) {
	for (uint8_t i = size-2; i >= 0; i--)
		array[i+1] = array[i];
}

uint8_t arrayAverageValue (uint8_t *array, uint8_t size) {
	uint16_t averageValue = 0;
	for (uint8_t i=0; i<size; averageValue += averageValue[i++]);
	return (uint8_t(averageValue /= size));
}