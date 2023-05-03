/*
 * cuestion_teorica_2.c
 *
 * Created: 17/04/2023 20:18:50
 * Author : Fran
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char mode;

void initTimers(){
	//Timer 0 en modo CTC usando la señal generada por la pwm como reloj.
	TCCR0A = (1 << WGM01);
	TCCR0B = (1 << CS02) | (1 << CS01) | (1 << CS00);
	TIMSK0 = (1 << OCIE0A);
	OCR0A = 250; 
	 
	
	//Timer 1 en modo FastPWM, non inverted con canal A, preescalado de 8 y carga del valor 40000
	//Se carga por defecto 1ms
	TCCR1A = (1 << COM1A1) | (1 << WGM11);
	TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11);
	ICR1H = (40000 >> 8) & 0xFF;
	ICR1L = 40000 & 0x00FF;
	
	//Por defecto el ancho es 500 us
	OCR1A = 1000;
	
	//Asignar salida de la señal pwm como reloj del timer0
	DDRB |= (1 << PINB1) | (1 << PINB2);									 											
}


ISR(TIMER0_COMPA_vect){
	if (mode == 0){
		OCR1A = 10000;
		mode = 1;
	} else {
		OCR1A = 1000;
		mode = 0;
	}
}

int main(void)
{
    //Deshabilitar interrupciones
    cli(); 
    
	initTimers();
    mode = 0;
    //Activar interrupciones
    sei();
    while (1);
}