/*
 * pp_bku.h
 *
 * Created: 17.03.2022 15:01:54
 *  Author: m.gasratov
 */ 


#ifndef PP_BKU_H_
#define PP_BKU_H_


#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "hd44780.h"

struct {
	uint8_t pp1Worked	:1;
	uint8_t pp2Worked	:1;
} flag = {0};

struct {
	uint8_t gb1;
	uint8_t gb2;
	uint8_t gb3;
	uint8_t gb4;
	uint8_t gb5;
	uint8_t gb6;
	uint8_t gb7;
	uint8_t ups;
	uint8_t mrdtt;
	uint8_t pp1;
	uint8_t pp2;
} status = {0};

void arrayMooveToRight (uint8_t *array, uint8_t size);
uint8_t arrayAverageValue (uint8_t *array, uint8_t size);


#endif /* PP_BKU_H_ */