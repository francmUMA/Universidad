/*
 * cuestion_teorica_2.c
 *
 * Created: 17/04/2023 20:18:50
 * Author : Fran
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

void initTimers(){
	//Timer 0 en modo CTC usando la se�al generada por la pwm como reloj.
	TCCR0A = (1 << WGM01);
	TCCR0B = (1 << CS02) | (1 << CS01) | (1 << CS00);
	TIMSK0 = (1 << OCIE0A);
	OCR0A = 250; 
	 
	
	//Timer 1 en modo FastPWM, non inverted con canal A, preescalado de 8 y carga del valor 40000
	//Se carga por defecto 1ms
	TCCR1A = (1 << COM1A1) | (1 << WGM11);
	TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11);
	TIMSK1 = (1 << OCIE1A);
	ICR1H = (40000 >> 8) & 0xFF;
	ICR1L = 40000 & 0x00FF;
	
	//Por defecto el ancho es 500 us
	OCR1AL = 40;
	
	//Asignar salida de la se�al pwm como reloj del timer0
	DDRB |= (1 << PINB1);										 											
}

ISR(INT0_vect){
	;
}

ISR(TIMER0_COMPA_vect){
	;
}

ISR(PCINT0_vect){
	;
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
	
	initTimers();
    
    //Activar interrupciones
    sei();
    
    while (1);
}