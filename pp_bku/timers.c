/*
 * timers.c
 */ 

#include "timers.h"
/*
void timer0_init() {
	TCNT0 = 0;
	TIMSK |= 1<<OCIE0;		// ��������� ���������� �� ����������
	TCCR0 = 0;				// Mode Normal
	TCCR0B = 0b001;			// Fclk:8, ��� Fclk=4��� ���� ������: 2 ���
}
*/

void timer1_init() {
	TCNT1 = 0;
	TCCR1A = 0;				// Mode Normal
	TCCR1B = 0b101;			// Fclk:1024, ��� Fclk=16��� ���� ������: 64 ���
	TIMSK |= 1<<OCIE1A;		// ��������� ���������� �� ���������� TIMER1_COMPA_vect
	OCR1A = 15625;			// ���������� ������ �������
	//TIMSK |= 1<<OCIE1B;		// ��������� ���������� �� ���������� TIMER1_COMPB_vect
	//OCR1B = 7812;			// ���������� ������ ����������
}
