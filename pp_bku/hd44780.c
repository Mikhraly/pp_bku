/*
 * hd44780.c
 * ��-������ WH4002 �. Winstar
 * Created: 16.03.2022 09:55:35
 *  Author: gasra
 */ 

#include "hd44780.h"

void hd44780_work(const uint8_t mode, const uint8_t byte);
void hd44780_convertStringRus(char string[]);
char hd44780_convertSymbolRus(char symbol);

void hd44780_init() {
	// ��������� ������� �� �����
	DDR_HD44780 |= 1<<E | 1<<RS | 1<<HD44780_D4 | 1<<HD44780_D5 | 1<<HD44780_D6 | 1<<HD44780_D7;
	_delay_ms(20);
	/*
	// ������������� �������� ������������ �� ��-16S2D (�. ����)
	hd44780_com(0b00111010);	// ���������� ����������� ����������
	hd44780_com(0b00111010);	// ���������� ����������� ����������
	hd44780_com(0b00111010);	// ���������� ����������� ����������
	hd44780_com(0b00101010);	// ���������� ����������� ����������
	hd44780_com(0b00101010);	// ��������� ����������
	hd44780_com(0b00001000);	// ���������� �������
	hd44780_com(0b00000001);	// ������� �������
	hd44780_com(0b00000110);	// ��������� ������ ����� ������
	hd44780_com(0b00001100);	// ��������� �������
	*/
	// ���� �������������
	_delay_ms(40);
	hd44780_work(0, 0b00000011); _delay_ms(6);
	hd44780_work(0, 0b00000011); _delay_ms(6);
	hd44780_work(0, 0b00000011); _delay_ms(6);
	hd44780_work(0, 0b00101010); _delay_ms(6); // ����������� 4 ����, �������� 1
	hd44780_work(0, 0b00101010); _delay_ms(6); // ����������� 4 ����, �������� 1
	hd44780_work(0, 0b00001000); _delay_ms(6);
	hd44780_work(0, 0b00000001); _delay_ms(6);
	hd44780_work(0, 0b00010000); _delay_ms(6);
	hd44780_work(0, 0b00000110); _delay_ms(6);
	hd44780_work(0, 0b00000010); _delay_ms(6);
	hd44780_work(0, 0b00101010); _delay_ms(6); // ����������� 4 ����, �������� 1
	hd44780_work(0, 0b00001100); _delay_ms(6);
}

void hd44780_init_proteus() {
	// ��������� ������� �� �����
	DDR_HD44780 |= 1<<E | 1<<RS | 1<<HD44780_D4 | 1<<HD44780_D5 | 1<<HD44780_D6 | 1<<HD44780_D7;
	hd44780_com(0b00000010);	// ��������� ������� � ��������� ���������. ������� �������
	hd44780_com(0b00101000);	// ��������� ����������: ����������� 4 ����. 2 ������. ������ ������ 5�7
	hd44780_com(0b00001100);	// ��������� �������. ������ ��������� �������. ������ �������� �������
}

void hd44780_work(const uint8_t mode, const uint8_t byte) {
	// ���������� ����� �������(0)/������(1)
	mode ? (PORT_HD44780 |= (1<<RS))	:	(PORT_HD44780 &= ~(1<<RS));
	// ����� � ���� ������� �������
	byte&(1<<7) ? (PORT_HD44780 |= (1<<HD44780_D7)) : (PORT_HD44780 &= ~(1<<HD44780_D7));
	byte&(1<<6) ? (PORT_HD44780 |= (1<<HD44780_D6)) : (PORT_HD44780 &= ~(1<<HD44780_D6));
	byte&(1<<5) ? (PORT_HD44780 |= (1<<HD44780_D5)) : (PORT_HD44780 &= ~(1<<HD44780_D5));
	byte&(1<<4) ? (PORT_HD44780 |= (1<<HD44780_D4)) : (PORT_HD44780 &= ~(1<<HD44780_D4));
	// ������ ��������� �������
	PORT_HD44780 |= (1<<E);
	asm("nop");
	PORT_HD44780 &= ~(1<<E);
	// ����� � ���� ������� �������
	byte&(1<<3) ? (PORT_HD44780 |= (1<<HD44780_D7)) : (PORT_HD44780 &= ~(1<<HD44780_D7));
	byte&(1<<2) ? (PORT_HD44780 |= (1<<HD44780_D6)) : (PORT_HD44780 &= ~(1<<HD44780_D6));
	byte&(1<<1) ? (PORT_HD44780 |= (1<<HD44780_D5)) : (PORT_HD44780 &= ~(1<<HD44780_D5));
	byte&(1<<0) ? (PORT_HD44780 |= (1<<HD44780_D4)) : (PORT_HD44780 &= ~(1<<HD44780_D4));
	// ������ ��������� �������
	PORT_HD44780 |= (1<<E);
	asm("nop");
	PORT_HD44780 &= ~(1<<E);
	_delay_ms(10);
}

void hd44780_com(const uint8_t command) {
	hd44780_work(0, command);
	_delay_us(40);
}

void hd44780_setAddress(uint8_t adress) {
	adress |= 1<<7;
	hd44780_work(0, adress);
	_delay_us(40);
}


void hd44780_print(const uint8_t data) {
	hd44780_work(1, data);
	_delay_us(40);
}


void hd44780_printArray(const uint8_t *array, const uint8_t size) {
	for (uint8_t i=0; i<size; i++)	hd44780_print(*(array+i));
}

void hd44780_printArray1(const uint8_t *array, const uint8_t size) {
	hd44780_setAddress(0x00);
	for (uint8_t i=0; i<size; i++)	hd44780_print(*(array+i));
}

void hd44780_printArray2(const uint8_t *array, const uint8_t size) {
	hd44780_setAddress(0x40);
	for (uint8_t i=0; i<size; i++)	hd44780_print(*(array+i));
}


/* �������� ����������� �� ��������� 0. ������ ������ �������� �������. ��� ��������� ������ ��� �� ������ ��������� �������
 * ������������� �� �������� 1. �������� ���� ������ �������, �� ��� ��������� ����� ������ �������� ������ ������� ���������:
 * setAddress(0x00); print(0x20); print(0x20); print(0x4F); � �.�.
 */
void hd44780_printString(char *string) {
	//hd44780_convertStringRus(string);			// ���������������� ��� ������������� "�������� 0" ������� ��-16S2D
	for (uint8_t i=0; string[i] != '\0'; i++)
		hd44780_print(string[i]);
}

void hd44780_printString1(char *string) {
	hd44780_setAddress(0x00);
	hd44780_printString(string);
}

void hd44780_printString2(char *string) {
	hd44780_setAddress(0x40);
	hd44780_printString(string);
}


void hd44780_convertStringRus(char string[]) {
	for(uint8_t i=0; string[i] != '\0'; i++)
		string[i] = hd44780_convertSymbolRus(string[i]);
}

char hd44780_convertSymbolRus(char symbol) {
	switch(symbol) {
	case '�':	return 0x41;
	case '�':	return 0xA0;
	case '�':	return 0x42;
	case '�':	return 0xA1;
	case '�':	return 0xE0;
	case '�':	return 0x45;
	case '�':	return 0xA2;
	case '�':	return 0xA3;
	case '�':	return 0xA4;
	case '�':	return 0xA5;
	case '�':	return 0xA6;
	case '�':	return 0x4B;
	case '�':	return 0xA7;
	case '�':	return 0x4D;
	case '�':	return 0x48;
	case '�':	return 0x4F;
	case '�':	return 0xA8;
	case '�':	return 0x50;
	case '�':	return 0x43;
	case '�':	return 0x54;
	case '�':	return 0xA9;
	case '�':	return 0xAA;
	case '�':	return 0x58;
	case '�':	return 0xE1;
	case '�':	return 0xAB;
	case '�':	return 0xAC;
	case '�':	return 0xE2;
	case '�':	return 0xAD;
	case '�':	return 0xAE;
	case '�':	return 0x62;
	case '�':	return 0xAF;
	case '�':	return 0xB0;
	case '�':	return 0xB1;
	case '�':	return 0x61;
	case '�':	return 0xB2;
	case '�':	return 0xB3;
	case '�':	return 0xB4;
	case '�':	return 0xE3;
	case '�':	return 0x65;
	case '�':	return 0xB5;
	case '�':	return 0xB6;
	case '�':	return 0xB7;
	case '�':	return 0xB8;
	case '�':	return 0xB9;
	case '�':	return 0xBA;
	case '�':	return 0xBB;
	case '�':	return 0xBC;
	case '�':	return 0xBD;
	case '�':	return 0x6F;
	case '�':	return 0xBE;
	case '�':	return 0x70;
	case '�':	return 0x63;
	case '�':	return 0xBF;
	case '�':	return 0x79;
	case '�':	return 0xE4;
	case '�':	return 0x78;
	case '�':	return 0xE5;
	case '�':	return 0xC0;
	case '�':	return 0xC1;
	case '�':	return 0xE6;
	case '�':	return 0xC2;
	case '�':	return 0xC3;
	case '�':	return 0xC4;
	case '�':	return 0xC5;
	case '�':	return 0xC6;
	case '�':	return 0xC7;
	default:	return symbol;
	}
}