/*
 * adc.h
 *
 * Created: 16.03.2022 14:05:10
 *  Author: m.gasratov
 */ 


#ifndef ADC_H_
#define ADC_H_


#include <avr/io.h>

void adc_init_8bit();
uint8_t adc_work_8bit(uint8_t number);


#endif /* ADC_H_ */