/*
 * pp_bku.h
 *
 * Created: 17.03.2022 15:01:54
 *  Author: m.gasratov
 */ 


#ifndef PP_BKU_H_
#define PP_BKU_H_


#define F_CPU 16000000UL

#include <util/delay.h>
#include "pp_bku.h"
#include "hd44780.h"
#include "adc.h"

struct {
	uint8_t gb1Worked	:1;
	uint8_t gb2Worked	:1;
	uint8_t gb3Worked	:1;
	uint8_t gb4Worked	:1;
	uint8_t gb5Worked	:1;
	uint8_t gb6Worked	:1;
	uint8_t gb7Worked	:1;
	uint8_t upsWorked	:1;
	uint8_t mrdttWorked	:1;
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

void ports_init();
uint8_t adcMeasureAverageOfTen(uint8_t channel);
uint8_t checkAdcResult(uint8_t adcResult, uint8_t minToLaunch, uint8_t minToPreparation);


#endif /* PP_BKU_H_ */