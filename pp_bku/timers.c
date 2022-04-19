/*
 * timers.c
 */ 

#include "timers.h"
/*
void timer0_init() {
	TCNT0 = 0;
	TIMSK |= 1<<OCIE0;		// Разрешено прерывание по совпадению
	TCCR0 = 0;				// Mode Normal
	TCCR0B = 0b001;			// Fclk:8, при Fclk=4МГц один отсчет: 2 мкс
}
*/

void timer1_init() {
	TCNT1 = 0;
	TCCR1A = 0;				// Mode Normal
	TCCR1B = 0b101;			// Fclk:1024, при Fclk=16МГц один отсчет: 64 мкс
	TIMSK |= 1<<OCIE1A;		// Разрешено прерывание по совпадению TIMER1_COMPA_vect
	OCR1A = 15625;			// Прерывание каждую секунду
	//TIMSK |= 1<<OCIE1B;		// Разрешено прерывание по совпадению TIMER1_COMPB_vect
	//OCR1B = 7812;			// Прерывание каждые полсекунды
}
