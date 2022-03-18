/*
 * pp_bku.c
 *
 * Created: 16.03.2022 8:44:17
 * Author : m.gasratov
 */ 

#include "pp_bku.h"

void ports_init();


int main(void)
{
	ports_init();
	adc_init_8bit();
    hd44780_init();
	
    while (1) {
		
		if (~PINB & 1<<4) {		// œœ1
			// TODO _delay_us
			
			uint8_t adcArray[10] = {0};
			for (uint8_t i=0; (~PINB & 1<<4)) {
				
			}
			while (~PINB & 1<<4) {
				arrayMooveToRight(adcArray, 10);
				adcArray[0] = adc_work_8bit(0);
			}
			uint8_t adcAverageValue = arrayAverageValue(adcArray, 10);
			
			if (adcAverageValue > ??) status.pp1 = 0x«;
			else if (adcAverageValue > ??) status.pp1 = 0xœ;
			else status.pp1 = 0xŒ;
			
			flag.pp1Worked = 1;
		}
		
		if (~PIND & 1<<0) {		// œœ2
			// TODO _delay_us
			
			uint8_t adcArr[11] = {0};
			while (~PIND & 1<<0) {
				for (uint8_t k=9; k>=0; k--) adcArr[k+1] = adcArr[k];
				adcArr[0] = adc_work_8bit(0);
			}
			
			uint8_t adcAverage = 0;
			for (uint8_t i=1; i<11; adcAverage += adcArr[i++]);
			adcAverage /= 10;
			
			if (adcAverage > ??) status.pp2 = 0x«;
			else if (adcAverage > ??) status.pp2 = 0xœ;
			else status.pp2 = 0xŒ;
			
			flag.pp2Worked = 1;
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
    }
}





if (adcAverage > ??) hd44780_setAddress(0x18); hd44780_print(0x«);
else if (adcAverage > ??) hd44780_setAddress(0x18); hd44780_print(0xœ);
else {hd44780_setAddress(0x18); hd44780_print(0xŒ);}