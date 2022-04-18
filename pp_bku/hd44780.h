/*
 * hd44780.h
 * Модуль для для работы с дисплеем типа hd44780 (ЖК-модуль WH4002 ф. Winstar)
 * Created: 16.03.2022 09:34:54
 * Author: gasra
 *
 * ИСПОЛЬЗУЕТСЯ ПОДКЛЮЧЕНИЕ ПО 4-РАЗРЯДНОЙ ШИНЕ ДАННЫХ
 * Индикатор постоянно настроен на работу в режиме записи (ВЫВОД RW = 0)
 * !!! ВАЖНО: Перед началом использования необходимо определисть выводы (см. ниже)
 */ 


#ifndef HD44780_H_
#define HD44780_H_

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
		
//////////	!! ОПРЕДЕЛЕНИЕ ВЫВОДОВ !!	//////////
#define	PORT_HD44780	PORTB		// ПОРТ ДЛЯ HD44780-ИНДИКАТОРА
#define	DDR_HD44780		DDRB		// ПОРТ DDR ДЛЯ HD44780-ИНДИКАТОРА
#define	RS				5			// вывод индикатора  RS  (Команда(0)/Данные(1))
#define	E				6			// вывод индикатора  E   (Строб записи. Активное изменение с 1 на 0)
#define	HD44780_D4		0			// вывод индикатора  D4
#define	HD44780_D5		1			// вывод индикатора  D5
#define	HD44780_D6		2			// вывод индикатора  D6
#define	HD44780_D7		3			// вывод индикатора  D7
// ВАЖНОЕ ЗАМЕЧАНИЕ: НА ВЫВОДЕ ИНДИКАТОРА RW (ЧТЕНИЕ/ЗАПИСЬ) ДОЛЖЕН БЫТЬ НИЗКИЙ УРОВЕНЬ (ЗАПИСЬ)


void hd44780_init();												// Инициализация
void hd44780_init_proteus();										// Инициализация для Proteus
void hd44780_com(const uint8_t command);							// Выдача команды в дисплей
void hd44780_setAddress(uint8_t adress);							// Установка адреса DDRAM. После команды должна следовать ф-ция HD44780_print()
void hd44780_print(const uint8_t data);								// Запись символа в дисплей
void hd44780_printArray(const uint8_t *array, const uint8_t size);	// Вывод на дисплей массива
void hd44780_printArray1(const uint8_t *array, const uint8_t size);
void hd44780_printArray2(const uint8_t *array, const uint8_t size);
void hd44780_printString(char *string);								// Вывод на дисплей строки
void hd44780_printString1(char *string);
void hd44780_printString2(char *string);


#endif