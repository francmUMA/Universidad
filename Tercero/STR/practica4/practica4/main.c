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
	//Timer 0 en modo FastPWM
	TCCR0A |= (1<<WGM01) | (1<<WGM00);						//FastPWM
	TCCR0A |= (1<<COM0A1);									//Non-Inverted
	TCCR0B |= (1<<CS02);									//Preescalado de 256
	OCR0A = 16;												//256 microsgs
	
	//Timer 1 en modo CTC
	TCCR1B = (1<<WGM12) | (1<<CS12) | (1<<CS10);			//Preescalado = 1024 y top en OCR1A	
	OCR1A = 46875;											//3s
	
	//Timer 2 en modo CTC
	TCCR2A = (1<<WGM21);									//Modo CTC con top en OCRA
	TCCR2B = (1<<CS22) | (1<<CS21) | (1<<CS20);				//Preescalado de 1024
	OCR2A = 157;											//10ms
}

ISR(INT0_vect){
	digitalWrite(0);
	TIMSK1 = (1<<OCIE1A);
	//TIMSK2 = (0<<OCIE2A);
	//TIMSK0 = (1<<TOIE0);
}

ISR(TIMER1_COMPA_vect){
	//Apagar leds y deshabilitar timer 1
	digitalWrite(0xFF);
	//TIMSK1 = (0<<OCIE1A);
	//Habilitar timer 2
	//TIMSK2 = (1<<OCIE2A);
	
}

ISR(TIMER2_COMPA_vect){
	counter += 1;
	digitalWrite(counter);
}

ISR(PCINT0_vect){
	digitalWrite(0);
	TIMSK1 = (1<<OCIE1A);
	//TIMSK2 = (0<<OCIE2A);
	//TIMSK0 = (1<<TOIE0);
}

int main(void)
{
    //Deshabilitar interrupciones
    cli(); 
    
    /*--------------------------------- INTERRUPCION EXTERNA -----------------------------------------*/
    //Mascara para INT0
    EIMSK = 0x01;
    
    //Activacion por flanco de bajada
    EICRA = 0x02;
    
    //Limpieza del registro de flag
    EIFR = 0x00;
    
    /*---------------------------- INTERRUPCION POR CAMBIO DE PIN -------------------------------------*/
    PCICR = (1<<PCIE0);
    PCMSK0 = (1<<PCINT4) | (1<<PCINT3);			//Boton B y A
	
    initLEDS();
	initTimers();
    
    //Activar interrupciones
    sei();
	//Activar timer 1
	//TIMSK1 = (1<<OCIE1A);
	//Arrancan los LEDs 3 segundos
	digitalWrite(0xFF);
    
    while (1);
}

