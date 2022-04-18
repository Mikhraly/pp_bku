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
	hd44780_printString2("GB7-? ÓÏÑ-? ÌÐÄ-? ÏÏ1-? ÏÏ2-?");
	
	Module gb1 = {0, 0, 1, 0x04, 50, 5};	// 1.0V, 0.1V
	Module gb2 = {0, 0, 1, 0x0A, 50, 5};	// 1.0V, 0.1V
	Module gb3 = {0, 0, 1, 0x10, 50, 5};	// 1.0V, 0.1V
	Module gb4 = {0, 0, 1, 0x16, 50, 5};	// 1.0V, 0.1V
	Module gb5 = {0, 0, 1, 0x1C, 50, 5};	// 1.0V, 0.1V
	Module gb6 = {0, 0, 1, 0x22, 50, 5};	// 1.0V, 0.1V
	Module gb7 = {0, 0, 1, 0x44, 50, 5};	// 1.0V, 0.1V
	Module ups = {0, 0, 2, 0x4A, 50, 4};	// 1.0V, 0.08V
	Module mrd = {0, 0, 2, 0x50, 50, 4};	// 1.0V, 0.08V
	Module pp1 = {0, 0, 0, 0x56, 40, 3};	// 0.8V, 0.06V
	Module pp2 = {0, 0, 0, 0x5C, 40, 3};	// 0.8V, 0.06V
	
	Module *module[] = {&gb1, &gb2, &gb3, &gb4, &gb5, &gb6, &gb7, &ups, &mrd, &pp1, &pp2};
	
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
			mrd.status = checkModuleStatus(&mrd);
			mrd.worked = 1;
			while (~PINC & 1<<0);
			_delay_us(10);
		}
		if (~PINC & 1<<1) {		// ÓÏÑ
			ups.status = checkModuleStatus(&ups);
			ups.worked = 1;
			while (~PINC & 1<<1);
			_delay_us(10);
		}
		
		
		for (uint8_t i=0; i<11; i++) {
			if (module[i]->worked) {
				module[i]->worked = 0;
				hd44780_setAddress(module[i]->lcdAddress);
				hd44780_print(module[i]->status);
			}
		}

	}
}


void ports_init() {
	DDRA |= (1<<3) | (1<<4) | (1<<5) | (1<<6) | (1<<7);
	PORTA &= ~(1<<3) & ~(1<<4) & ~(1<<5) & ~(1<<6) & ~(1<<7);
	
	DDRB &= ~(1<<4);
	PORTB |= 1<<4;
	
	DDRC &= ~(1<<0) & ~(1<<1) &~(1<<6);
	PORTC |= (1<<0) | (1<<1) | (1<<6);
	DDRC |= 1<<7;
	PORTC &= ~(1<<7);
	
	DDRD = 0x00;
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