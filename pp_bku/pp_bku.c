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
	hd44780_printString2("GB7-? ÓÏÑ-? ÌÐÄÒÒ-? ÏÏ1-? ÏÏ2-?");
	
	Module gb1 = {0, 0, 1, 163, 2};	// 3.2V, 0.04V
	Module gb2 = {0, 0, 1, 163, 2};	// 3.2V, 0.04V
	Module gb3 = {0, 0, 1, 163, 2};	// 3.2V, 0.04V
	Module gb4 = {0, 0, 1, 163, 2};	// 3.2V, 0.04V
	Module gb5 = {0, 0, 1, 163, 2};	// 3.2V, 0.04V
	Module gb6 = {0, 0, 1, 163, 2};	// 3.2V, 0.04V
	Module gb7 = {0, 0, 1, 163, 2};	// 3.2V, 0.04V
	Module ups = {0, 0, 2, 112, 1};	// 2.2V, 0.02V
	Module mrdtt = {0, 0, 2, 112, 1};	// 2.2V, 0.02V
	Module pp1 = {0, 0, 0, 51, 2};	// 1V, 0.04V
	Module pp2 = {0, 0, 0, 51, 2};	// 1V, 0.04V
	
	while (1) {
		
		if (~PINB & 1<<4) {		// ÏÏ1
			pp1.status = checkModuleStatus(&pp1);
			pp1.worked = 1;
			while (~PINB & 1<<4);
			_delay_us(10);
		}
		if (~PIND & 1<<0) {		// ÏÏ2
			pp2.status = checkModuleStatus(&pp2);
			pp2.worked = 1;
			while (~PIND & 1<<0);
			_delay_us(10);
		}
		if (~PIND & 1<<1) {		// GB5
			gb5.status = checkModuleStatus(&gb5);
			gb5.worked = 1;
			while (~PIND & 1<<1);
			_delay_us(10);
		}
		if (~PIND & 1<<2) {		// GB6
			gb6.status = checkModuleStatus(&gb6);
			gb6.worked = 1;
			while (~PIND & 1<<2);
			_delay_us(10);
		}
		if (~PIND & 1<<3) {		// GB7
			gb7.status = checkModuleStatus(&gb7);
			gb7.worked = 1;
			while (~PIND & 1<<3);
			_delay_us(10);
		}
		if (~PIND & 1<<4) {		// GB1
			gb1.status = checkModuleStatus(&gb1);
			gb1.worked = 1;
			while (~PIND & 1<<4);
			_delay_us(10);
		}
		if (~PIND & 1<<5) {		// GB2
			gb2.status = checkModuleStatus(&gb2);
			gb2.worked = 1;
			while (~PIND & 1<<5);
			_delay_us(10);
		}
		if (~PIND & 1<<6) {		// GB3
			gb3.status = checkModuleStatus(&gb3);
			gb3.worked = 1;
			while (~PIND & 1<<6);
			_delay_us(10);
		}
		if (~PIND & 1<<7) {		// GB4
			gb4.status = checkModuleStatus(&gb4);
			gb4.worked = 1;
			while (~PIND & 1<<7);
			_delay_us(10);
		}
		if (~PINC & 1<<0) {		// ÌÐÄÒÒ
			mrdtt.status = checkModuleStatus(&mrdtt);
			mrdtt.worked = 1;
			while (~PINC & 1<<0);
			_delay_us(10);
		}
		if (~PINC & 1<<1) {		// ÓÏÑ
			ups.status = checkModuleStatus(&ups);
			ups.worked = 1;
			while (~PINC & 1<<1);
			_delay_us(10);
		}
		
		
		if (pp1.worked) {
			pp1.worked = 0;
			hd44780_setAddress(0x18);
			hd44780_print(pp1.status);
		}
		if (pp2.worked) {
			pp2.worked = 0;
			hd44780_setAddress(0x20);
			hd44780_print(pp2.status);
		}
		if (gb5.worked) {
			gb5.worked = 0;
			hd44780_setAddress(0x1E);
			hd44780_print(gb5.status);
		}
		if (gb6.worked) {
			gb6.worked = 0;
			hd44780_setAddress(0x24);
			hd44780_print(gb6.status);
		}
		if (gb7.worked) {
			gb7.status = 0;
			hd44780_setAddress(0x40);
			hd44780_print(gb7.status);
		}
		if (gb1.worked) {
			gb1.worked = 0;
			hd44780_setAddress(0x04);
			hd44780_print(gb1.status);
		}
		if (gb2.worked) {
			gb2.worked = 0;
			hd44780_setAddress(0x0A);
			hd44780_print(gb2.status);
		}
		if (gb3.worked) {
			gb3.worked = 0;
			hd44780_setAddress(0x12);
			hd44780_print(gb3.status);
		}
		if (gb4.worked) {
			gb4.worked = 0;
			hd44780_setAddress(0x16);
			hd44780_print(gb4.status);
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


uint8_t checkModuleStatus(Module* module) {
	uint16_t adcValue = 0;
	for (uint8_t i=0; i<10; i++)
		adcValue += (uint16_t)(adc_work_8bit(module->adcChannel));
	uint8_t adcAverage = (uint8_t)(adcValue /= 10);
	
	if (adcAverage > module->minToLaunch) return 0xA4;				// "Ç" - Çàïóñê
	else if (adcAverage > module->minToPreparation) return 0xA8;	// "Ï" - Ïðîâåðêà
	else return 0x4F;												// "Î" - Îáðûâ
}