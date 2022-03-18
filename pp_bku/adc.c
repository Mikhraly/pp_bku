#include "adc.h"

void adc_init_8bit() {
	ADCSRA |= (1<<ADEN);				// Разрешить работу АЦП
	ADCSRA |= (1<<ADPS0) | (1<<ADPS2);	// Коэффициент деления - Fмк/32
	ADCSRA &= ~(1<<ADPS1);
	ADCSRA &= ~(1<<ADATE);				// Выбран одиночный режим преобразования
	ADMUX &= ~(1<<REFS1) & ~(1<<REFS0);	// AREF, внутреннее опорное напряжение отключено
	ADMUX |= (1<<ADLAR);				// Левосторонее выравнивание результата преобразования в регистре данных ADC (ADCH, ADCL)
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
	// Запускаем процесс аналого-цифрового преобразования
	ADCSRA |= (1<<ADSC);			// Активируем преобразование (ADSC = 1)
	while (!(ADCSRA & 1<<ADIF));	// Ожидаем завершения преобразования (ADIF == 1)
	ADCSRA |= (1<<ADIF);			// Обнуляем ADIF, указывая на завершение преобразования (это осуществляется принудительно записью единицы!)
	return ADCH;					// Возвращаем значение старшего регистра данных АЦП
}