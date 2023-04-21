/*
 * practica4.c
 *
 * Created: 23/03/2023 10:56:46
 * Author : Fran
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

static uint8_t counter = 0;
static uint8_t mode = 1;

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
	TCCR0A = (1<<WGM01) | (1<<WGM00);						//FastPWM
	TCCR0A |= (1<<COM0A1);									//Non-Inverted
	OCR0A = 16;												//256 microsgs
	PORTD |= (1 << PIND6);									//Salida de la onda pwm
	
	//Timer 1 en modo CTC
	TCCR1B = (1<<WGM12) | (1<<CS12) | (1<<CS10);			//Preescalado = 1024 y top en OCR1A	
	TIMSK1 = (1<<OCIE1A);
	OCR1A = 46875;											//3s
	
	//Timer 2 en modo CTC
	TCCR2A = (1<<WGM21);									//Modo CTC con top en OCRA
	TIMSK2 = (1<<OCIE2A);
	OCR2A = 157;											//10ms
	
}

ISR(INT0_vect){
		mode = 3;
		
		digitalWrite(0x00);
		
		//Deshabilitar Timer 1 y volverlo a activar
		TCCR1B = 0;
		OCR2A = 0;
		OCR2A = 157;
		TCCR1B = (1<<WGM12) | (1<<CS12) | (1<<CS10);
		
		//Deshabilitar timer 2
		TCCR2B = 0;
		
		//Habilitar timer 0
		TCCR0B |= (1<<CS02);									//Preescalado de 256
}

ISR(TIMER1_COMPA_vect){
	if (mode == 1){
		//Habilito timer 2
		 TCCR2B = (1<<CS22) | (1<<CS21) | (1<<CS20);				//Preescalado de 1024
		 mode = 2;
	} else if (mode == 2) {
		digitalWrite(0xFF);
		//Deshabilitar timer 2
		TCCR2B = 0;
		mode = 1;
	} else if (mode == 3){
		mode = 1;
		TCCR0B = 0;
		digitalWrite(0xFF);
	}
	
}

ISR(TIMER2_COMPA_vect){
	counter += 1;
	digitalWrite(counter);
}

ISR(PCINT0_vect){
	mode = 3;
	
	digitalWrite(0x00);
	
	//Deshabilitar Timer 1 y volverlo a activar
	TCCR1B = 0;
	OCR2A = 0;
	OCR2A = 157;
	TCCR1B = (1<<WGM12) | (1<<CS12) | (1<<CS10);
	
	//Deshabilitar timer 2
	TCCR2B = 0;
	
	//Habilitar timer 0
	TCCR0B |= (1<<CS02);									//Preescalado de 256
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
	
	//Arrancan los LEDs 3 segundos
	digitalWrite(0xFF);
    
    while (1);
}

