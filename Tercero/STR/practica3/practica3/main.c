/*
 * practica3.c
 *
 * Created: 17/03/2023 11:07:50
 * Author : Fran
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

void digitalWrite(unsigned char data){
	PORTB = ((data & 0x01) << PINB2) | (((data & 0x02) >> 1) << PINB1) | (((data & 0x04) >> 2) << PINB0);
	PORTD = (((data & 0x20) >> 5) << PIND4) | (((data & 0x10) >> 4) << PIND5) | (((data & 0x08) >> 3) << PIND7);
	PORTC = (((data & 0x80) >> 7) << PINC3) | (((data & 0x40) >> 6) << PINC4);
}

static uint8_t count = 0;

ISR(INT0_vect){
	ADCSRA = (1<<ADIE) | (1<<ADSC) | (1<<ADEN) |(1<<ADPS2);
}

ISR(PCINT0_vect){
	ADCSRA = 0;
	if (PINB & (1 << PINB3)){
		count++;
	} else if (PINB & (1<<PINB4)){
		count--;
	}
	digitalWrite(count);
}

ISR(ADC_vect){
	//Escritura del resultado de la conversion
	digitalWrite(ADCH);
	
	//Inicio la conversion
	ADCSRA |= (1<<ADSC);
}

void initADC(){
	//Voltaje externo, ajuste a la izquierda y el canal 5
	ADMUX = (1 << REFS0) | (1<<ADLAR) | (5 & 0x0F);
	
	//Activar ADC y divisor de 16 bits
	ADCSRA = (1<<ADEN) |(1<<ADPS2);
}

void initLEDS(){
	DDRB |= (1 << PINB2) | (1 << PINB1) | (1 << PINB0);
	DDRC |= (1 << PINC3) | (1 << PINC4);
	DDRD |= (1 << PIND4) | (1 << PIND5) | (1 << PIND7);
}

int main(void)
{	
	//Deshabilitar interrupciones
	cli(); 
	
	
	/*--------------------------------- INTERRUPCION EXTERNA -----------------------------------------*/
	//Máscara para INT0
	EIMSK = 0x01;
	
	//Activación por flanco de bajada
	EICRA = 0x02;
	
	//Limpieza del registro de flag
	EIFR = 0x00;
	
	/*---------------------------- INTERRUPCION POR CAMBIO DE PIN -------------------------------*/
	PCICR = (1<<PCIE0);
	PCMSK0 = (1<<PCINT4) | (1<<PCINT3);			//Boton B y A
	
	initADC();
	initLEDS();
	
	digitalWrite(count);
	
	//Activar interrupciones
	sei();
	
    while (1);
}

