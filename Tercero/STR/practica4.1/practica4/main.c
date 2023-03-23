/*
 * practica4.c
 *
 * Created: 23/03/2023 10:56:46
 * Author : Fran
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

static uint8_t counter = 0;

void digitalWrite(unsigned char data){
	PORTB = ((data & 0x01) << PINB2) | (((data & 0x02) >> 1) << PINB1) | (((data & 0x04) >> 2) << PINB0);
	PORTD = (((data & 0x20) >> 5) << PIND4) | (((data & 0x10) >> 4) << PIND5) | (((data & 0x08) >> 3) << PIND7);
	PORTC = (((data & 0x80) >> 7) << PINC3) | (((data & 0x40) >> 6) << PINC4);
}

void initLEDS(){
	DDRB |= (1 << PINB2) | (1 << PINB1) | (1 << PINB0);
	DDRC |= (1 << PINC3) | (1 << PINC4);
	DDRD |= (1 << PIND4) | (1 << PIND5) | (1 << PIND7);
}

void initTimers(){
	TCCR1B |= (1<<WGM12) | (1<<CS11) | (1<<CS10);
	TIMSK1 |= (1<<OCIE1A);
	OCR1A = 62500;
}

ISR(TIMER1_COMPA_vect){
	counter += 1;
	if (counter > 63) counter = 0;
	digitalWrite(counter);
}

int main(void)
{
    //Deshabilitar interrupciones
    cli(); 
    
    /*--------------------------------- INTERRUPCION EXTERNA -----------------------------------------*/
    //M?scara para INT0
    //EIMSK = 0x01;
    
    //Activaci?n por flanco de bajada
    //EICRA = 0x02;
    
    //Limpieza del registro de flag
    //EIFR = 0x00;
    
    /*---------------------------- INTERRUPCION POR CAMBIO DE PIN -------------------------------------*/
    //PCICR = 0x01;
    //PCMSK0 = 0x01;
	
    initLEDS();
	initTimers();
	digitalWrite(counter);
    
    //Activar interrupciones
    sei();
    
    while (1);
}

