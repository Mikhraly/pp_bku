/*
 * pp_bku.c
 *
 * Created: 17.03.2022 15:01:20
 *  Author: m.gasratov
 */ 


#include "pp_bku.h"


int main(void)
{
	ports_init();
	hd44780_init();
	adc_init_8bit();
	
	hd44780_printString1("GB1-? GB2-? GB3-? GB4-? GB5-? GB6-?");
	hd44780_printString2("GB7-? ÓÏÑ-? ÌĞÄÒÒ-? ÏÏ1-? ÏÏ2-?");
	
	while (1) {
		
		if (~PINB & 1<<4) {		// ÏÏ1
			status.pp1 = checkAdcResult(adcMeasureAverageOfTen(0), 51, 2);	// 1V, 0.04V
			flag.pp1Worked = 1;
			while (~PINB & 1<<4);
			_delay_us(10);
		}
		if (~PIND & 1<<0) {		// ÏÏ2
			status.pp2 = checkAdcResult(adcMeasureAverageOfTen(0), 51, 2);	// 1V, 0.04V
			flag.pp2Worked = 1;
			while (~PIND & 1<<0);
			_delay_us(10);
		}
		if (~PIND & 1<<1) {		// GB5
			status.gb5 = checkAdcResult(adcMeasureAverageOfTen(1), 163, 2);	// 3.2V, 0.04V
			flag.gb5Worked = 1;
			while (~PIND & 1<<1);
			_delay_us(10);
		}
		if (~PIND & 1<<2) {		// GB6
			status.gb6 = checkAdcResult(adcMeasureAverageOfTen(1), 163, 2);	// 3.2V, 0.04V
			flag.gb6Worked = 1;
			while (~PIND & 1<<2);
			_delay_us(10);
		}
		if (~PIND & 1<<3) {		// GB7
			status.gb7 = checkAdcResult(adcMeasureAverageOfTen(1), 163, 2);	// 3.2V, 0.04V
			flag.gb7Worked = 1;
			while (~PIND & 1<<3);
			_delay_us(10);
		}
		if (~PIND & 1<<4) {		// GB1
			status.gb1 = checkAdcResult(adcMeasureAverageOfTen(1), 163, 2);	// 3.2V, 0.04V
			flag.gb1Worked = 1;
			while (~PIND & 1<<4);
			_delay_us(10);
		}
		if (~PIND & 1<<5) {		// GB2
			status.gb2 = checkAdcResult(adcMeasureAverageOfTen(1), 163, 2);	// 3.2V, 0.04V
			flag.gb2Worked = 1;
			while (~PIND & 1<<5);
			_delay_us(10);
		}
		if (~PIND & 1<<6) {		// GB3
			status.gb3 = checkAdcResult(adcMeasureAverageOfTen(1), 163, 2);	// 3.2V, 0.04V
			flag.gb3Worked = 1;
			while (~PIND & 1<<6);
			_delay_us(10);
		}
		if (~PIND & 1<<7) {		// GB4
			status.gb4 = checkAdcResult(adcMeasureAverageOfTen(1), 163, 2);	// 3.2V, 0.04V
			flag.gb4Worked = 1;
			while (~PIND & 1<<7);
			_delay_us(10);
		}
		if (~PINC & 1<<0) {		// ÌĞÄÒÒ
			status.mrdtt = checkAdcResult(adcMeasureAverageOfTen(2), 112, 1);	// 2.2V, 0.02V
			flag.mrdttWorked = 1;
			while (~PINC & 1<<0);
			_delay_us(10);
		}
		if (~PINC & 1<<1) {		// ÓÏÑ
			status.ups = checkAdcResult(adcMeasureAverageOfTen(2), 112, 1);	// 2.2V, 0.02V
			flag.upsWorked = 1;
			while (~PINC & 1<<1);
			_delay_us(10);
		}
		
		
		if (flag.pp1Worked) {
			flag.pp1Worked = 0;
			hd44780_setAddress(0x18);
			hd44780_print(status.pp1);
		}
		if (flag.pp2Worked) {
			flag.pp2Worked = 0;
			hd44780_setAddress(0x20);
			hd44780_print(status.pp2);
		}
		if (flag.gb5Worked) {
			flag.gb5Worked = 0;
			hd44780_setAddress(0x1E);
			hd44780_print(status.gb5);
		}
		if (flag.gb6Worked) {
			flag.gb6Worked = 0;
			hd44780_setAddress(0x24);
			hd44780_print(status.gb6);
		}
		if (flag.gb7Worked) {
			flag.gb7Worked = 0;
			hd44780_setAddress(0x40);
			hd44780_print(status.gb7);
		}
		if (flag.gb1Worked) {
			flag.gb1Worked = 0;
			hd44780_setAddress(0x04);
			hd44780_print(status.gb1);
		}
		if (flag.gb2Worked) {
			flag.gb2Worked = 0;
			hd44780_setAddress(0x0A);
			hd44780_print(status.gb2);
		}
		if (flag.gb3Worked) {
			flag.gb3Worked = 0;
			hd44780_setAddress(0x12);
			hd44780_print(status.gb3);
		}
		if (flag.gb4Worked) {
			flag.gb4Worked = 0;
			hd44780_setAddress(0x16);
			hd44780_print(status.gb4);
		}
		
	}
}


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

uint8_t adcMeasureAverageOfTen(uint8_t channel) {
	uint16_t adcValue = 0;
	for (uint8_t i=0; i<10; i++)
		adcValue += (uint16_t)(adc_work_8bit(channel));
	return (uint8_t)(adcValue /= 10);
}

uint8_t checkAdcResult(uint8_t adcResult, uint8_t minToLaunch, uint8_t minToPreparation) {
	if (adcResult > minToLaunch) return 0xA4;				// "Ç" - Çàïóñê
	else if (adcResult > minToPreparation) return 0xA8;		// "Ï" - Ïğîâåğêà
	else return 0x4F;										// "Î" - Îáğûâ
}