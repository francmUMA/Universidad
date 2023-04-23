/*
 * Practica5.c
 *
 * Created: 17/04/2023 20:18:50
 * Author : Fran
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

static uint8_t entra_coche = 0;
static uint8_t sale_coche = 0;
static uint8_t reposo = 1;
static uint8_t configuracion = 0;
static int counter = 0;

void print(unsigned char data){
	PORTB = (((PORTB >> PINB1) & 0x01) << PINB1) | (((PORTB >> PINB2) & 0x01) << PINB2) | ((data & 0x01) << PINB0);
	PORTD = (((PORTD >> PIND4) & 0x01) << PIND4) | (((data & 0x04) >> 2) << PIND5) | (((data & 0x02) >> 1) << PIND7);
}

void initLEDS(){
	DDRB |= (1 << PINB2) | (1 << PINB0);
	DDRC |= (1 << PINC3) | (1 << PINC4);
	DDRD |= (1 << PIND5) | (1 << PIND7);
}

void initTimers(){
	//Timer 0 en modo CTC usando la señal generada por la pwm como reloj.
	TCCR0A = (1 << WGM01); 
	TIMSK0 = (1 << OCIE0A);
	OCR0A = 5;											//0.1s
	 
	
	//Timer 1 en modo FastPWM, non inverted con canal A, preescalado de 8 y carga del valor 40000
	//Se carga por defecto 1ms
	TCCR1A = (1 << COM1A1) | (1 << WGM11);
	TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11);
	TIMSK1 = (1 << OCIE1A);
	ICR1H = (40000 >> 8) & 0xFF;
	ICR1L = 40000 & 0x00FF;
	OCR1AH = (2000 >> 8) & 0xFF;
	OCR1AL = 2000 & 0x00FF;
	
	//Asignar salida de la señal pwm como reloj del timer0
	DDRB |= (1 << PINB1);										 											
}

ISR(INT0_vect){
	;
}

ISR(TIMER0_COMPA_vect){
	PORTB = (!((PORTB >> PINB2) & 0x01) << PINB2);
}

ISR(PCINT0_vect){
	if (PINB & (1 << PINB3)){			//Boton A
		if (reposo) {
			reposo = 0;
			entra_coche = 1;
			
			//Apagar led7 y led6
			PORTC = 0;
			
			//Activo parpadeo y levanto barrera
			TCCR0B = (1 << CS02) | (1 << CS01) | (1 << CS00);
			OCR1AH = (3000 >> 8) & 0xFF;
			OCR1AL = 3000 & 0x00FF;
		} 
	} else if (PINB & (1<<PINB4)){		//Boton B
		if (reposo) {
			reposo = 0;
			sale_coche = 1;
			
			//Apagar led7 y led6
			PORTC = 0;
			
			//Activo parpadeo y levanto barrera
			TCCR0B = (1 << CS02) | (1 << CS01) | (1 << CS00);
			OCR1AH = (3000 >> 8) & 0xFF;
			OCR1AL = 3000 & 0x00FF;
		} else if (entra_coche){
			reposo = 1;
			entra_coche = 0;
			
			//Enciendo semaforo
			PORTC = (1 << PINC3) | (1 << PINC4);						//LED6 y LED7
			
			//Apagar luz parpadeante
			TCCR0B = 0;
			
			//Bajar barrera
			OCR1AH = (3000 >> 8) & 0xFF;
			OCR1AL = 3000 & 0x00FF;
			
			counter += 1;
			print(counter);
		}
	}
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
    PCMSK0 = (1<<PCINT4) | (1<<PCINT3);							//Boton B y A
	
    initLEDS();
	initTimers();
    
    //Activar interrupciones
    sei();
	
	//Enciendo semaforo
	PORTC = (1 << PINC3) | (1 << PINC4);						//LED6 y LED7
    
    while (1);
}
