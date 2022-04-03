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
#include "pp_bku.h"
#include "hd44780.h"
#include "adc.h"

typedef struct {
	uint8_t worked :1;
	uint8_t status :1;
	uint8_t adcChannel;
	uint8_t lcdAddress;
	uint8_t minToLaunch;
	uint8_t minToPreparation;
} Module;

enum modules {GB1, GB2, GB3, GB4, GB5, GB6, GB7, UPS, MRDTT, PP1, PP2};


void ports_init();
uint8_t checkModuleStatus(Module* module);


#endif /* PP_BKU_H_ */