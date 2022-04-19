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
#include <avr/interrupt.h>
#include <util/delay.h>
#include "hd44780.h"
#include "adc.h"
#include "timers.h"

typedef struct {
	uint8_t checked :1;
	uint8_t status;
	uint8_t adcChannel;
	uint8_t lcdAddress;
	uint8_t minToLaunch;
	uint8_t minToPreparation;
} Module;

enum modules {GB1, GB2, GB3, GB4, GB5, GB6, GB7, UPS, MRD, PP1, PP2};

enum moduleStatusCodeForHD44780 {
	LAUNCH = 0xA4,			// "З" - Запуск
	PREPARATION = 0xA8,		// "П" - Проверка
	BREAKAGE = 0x4F,		// "О" - Обрыв
};

/************************************************************************/
/*        Импульс для запуска батарей через прерывание таймера1         */
/************************************************************************/
enum launchSteps {START = 1, WORK, STOP};

struct {
	uint8_t BABS	:2;
	uint8_t BABP	:2;
} volatile launch = {0};
	
ISR (TIMER1_COMPA_vect) {
	if (launch.BABS == START) {
		PORTA |= 1<<4;
		launch.BABS = WORK;
	} else if (launch.BABS == WORK) {
		PORTA &= ~(1<<4);
		launch.BABS = STOP;
	}
	
	if (launch.BABP == START) {
		PORTA |= 1<<3;
		launch.BABP = WORK;
	} else if (launch.BABP == WORK) {
		PORTA &= ~(1<<3);
		launch.BABP = STOP;
	}
	
	if (launch.BABS == STOP && launch.BABP == STOP)
		TCCR1B = 0;			// Stop timer1
	
	TCNT1 = 0;
}
//////////////////////////////////////////////////////////////////////////

void ports_init();
uint8_t checkModuleStatus(Module* module);


#endif /* PP_BKU_H_ */