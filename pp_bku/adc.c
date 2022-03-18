#include "adc.h"

void adc_init_8bit() {
	ADCSRA |= (1<<ADEN);				// ��������� ������ ���
	ADCSRA |= (1<<ADPS0) | (1<<ADPS2);	// ����������� ������� - F��/32
	ADCSRA &= ~(1<<ADPS1);
	ADCSRA &= ~(1<<ADATE);				// ������ ��������� ����� ��������������
	ADMUX &= ~(1<<REFS1) & ~(1<<REFS0);	// AREF, ���������� ������� ���������� ���������
	ADMUX |= (1<<ADLAR);				// ������������ ������������ ���������� �������������� � �������� ������ ADC (ADCH, ADCL)
}


uint8_t adc_work_8bit(uint8_t number) {
	switch (number) {
	case 0:
		ADMUX &= ~(1<<MUX4) & ~(1<<MUX3) & ~(1<<MUX2) & ~(1<<MUX1) & ~(1<<MUX0);
		break;
	case 1:
		ADMUX &= ~(1<<MUX4) & ~(1<<MUX3) & ~(1<<MUX2) & ~(1<<MUX1);
		ADMUX |= (1<<MUX0);
		break;
	case 2:
		ADMUX &= ~(1<<MUX4) & ~(1<<MUX3) & ~(1<<MUX2) & ~(1<<MUX0);
		ADMUX |= (1<<MUX1);
		break;
	case 3:
		ADMUX &= ~(1<<MUX4) & ~(1<<MUX3) & ~(1<<MUX2);
		ADMUX |= (1<<MUX1) | (1<<MUX0);
		break;
	case 4:
		ADMUX &= ~(1<<MUX4) & ~(1<<MUX3) & ~(1<<MUX1) & ~(1<<MUX0);
		ADMUX |= (1<<MUX2);
		break;
	case 5:
		ADMUX &= ~(1<<MUX4) & ~(1<<MUX3) & ~(1<<MUX1);
		ADMUX |= (1<<MUX2) | (1<<MUX0);
		break;
	case 6:
		ADMUX &= ~(1<<MUX4) & ~(1<<MUX3) & ~(1<<MUX0);
		ADMUX |= (1<<MUX2) | (1<<MUX1);
		break;
	case 7:
		ADMUX &= ~(1<<MUX4) & ~(1<<MUX3);
		ADMUX |= (1<<MUX2) | (1<<MUX1) | (1<<MUX0);
		break;
	default:
		ADMUX &= ~(1<<MUX4) & ~(1<<MUX3) & ~(1<<MUX2) & ~(1<<MUX1) & ~(1<<MUX0);
		break;
	}
	// ��������� ������� �������-��������� ��������������
	ADCSRA |= (1<<ADSC);			// ���������� �������������� (ADSC = 1)
	while (!(ADCSRA & 1<<ADIF));	// ������� ���������� �������������� (ADIF == 1)
	ADCSRA |= (1<<ADIF);			// �������� ADIF, �������� �� ���������� �������������� (��� �������������� ������������� ������� �������!)
	return ADCH;					// ���������� �������� �������� �������� ������ ���
}