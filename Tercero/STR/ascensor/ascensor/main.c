/*
 * ascensor.c
 *
 * Created: 06/05/2023 10:29:42
 * Author : Fran
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#define CLOSED  0x00
#define DOOR_0  0x01
#define DOOR_1  0x10
#define DOOR_2  0x11

#define FLOOR_0 0x01
#define FLOOR_1 0x10
#define FLOOR_2 0x11
#define STOPPED 0x00

#define PARADO		10000
#define ASCIENDE	200
#define DESCIENDE	20000

volatile uint8_t current_floor = FLOOR_0;
volatile uint8_t target_floor = STOPPED;
volatile uint8_t doors = CLOSED;
volatile uint8_t people = 0;				//hay gente dentro del ascensor

void print_open_doors(unsigned char data){		
	PORTB = (((data & 0x02) >> 1) << PINB0) | ((data & 0x01) << PINB2) | (((PORTB >> PINB1) & 0x01) << PINB1);
}

void print_current_floor(unsigned char data){
	PORTD = (((PORTD >> PIND4) & 0x01) << PIND4) | (((data & 0x02) >> 1) << PIND5) | ((data & 0x01) << PIND7);
}

void print_target_floor(unsigned char data){
	PORTC = (((data & 0x02) >> 1) << PINC3) | ((data & 0x01) << PINC4);
}

void initLEDS(){
	DDRB |= (1 << PINB2) | (1 << PINB0);
	DDRC |= (1 << PINC3) | (1 << PINC4);
	DDRD |= (1 << PIND5) | (1 << PIND7);
}

void initTimers(){
	//Timer 0 en modo CTC usando la se?al generada por la pwm como reloj.
	TCCR0A = (1 << WGM01);
	OCR0A = 250;											//5s
	
	
	//Timer 1 en modo FastPWM, non inverted con canal A, preescalado de 8 y carga del valor 40000
	//Se carga por defecto 1ms
	TCCR1A = (1 << COM1A1) | (1 << WGM11);
	TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11);
	ICR1H = (40000 >> 8) & 0xFF;
	ICR1L = 40000 & 0x00FF;
	OCR1AH = (PARADO >> 8) & 0xFF;
	OCR1AL = PARADO & 0x00FF;
	
	//Asignar salida de la se?al pwm como reloj del timer0
	DDRB |= (1 << PINB1);
}

void start_timer0(){
	TCCR0B = (1 << CS02) | (1 << CS01) | (1 << CS00);
	TIMSK0 = (1 << OCIE0A);
}

void stop_timer0(){
	TCCR0B = 0;
	TIMSK0 = 0;
	TCNT0 = 0;
}

//Boton C
ISR(INT0_vect){
	if (people){
		if (target_floor == current_floor){
			//NO SE HACE NADA
			;
		} else{
			
		}
	}else{
		if (target_floor == current_floor){
			// El ascensor se abre para que entre gente
			people = 1;
			doors = DOOR_2;
			print_open_doors(doors);
			start_timer0();
		} else{
			
		}
	}
}

ISR(TIMER0_COMPA_vect){
	if (doors != CLOSED) {
		doors = CLOSED;
		print_open_doors(CLOSED);
	} else {
		stop_timer0();
	}
}

ISR(PCINT0_vect){
	if (PINB & (1 << PINB3)){			//Boton A
		if (people){
			if (target_floor == current_floor){
				//NO SE HACE NADA
				;
			} else{
				// Sabemos que solo se puede descender
				target_floor = FLOOR_0;
				print_target_floor(target_floor);
				OCR1AH = (DESCIENDE >> 8) & 0xFF;
				OCR1AL = DESCIENDE & 0x00FF;
				//DELAY de 2s para ir de una diferencia de 2 plantas
				//DELAY de 1s para ir a una planta consecutiva
			}
		}else{
			if (target_floor == current_floor){
				// El ascensor se abre para que entre gente
				people = 1;
				doors = DOOR_0;
				print_open_doors(doors);
				start_timer0();
			} else{
				
			}
		}
	}else if (PINB & (1<<PINB4)){		//Boton B
		if (people){
			if (target_floor == current_floor){
				//NO SE HACE NADA
				;
			} else{
				
			}
		}else{
			if (target_floor == current_floor){
				// El ascensor se abre para que entre gente
				people = 1;
				doors = DOOR_1;
				print_open_doors(doors);
				start_timer0();
			} else{
				
			}
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
	
	// Estado por defecto
	print_current_floor(current_floor);
	print_target_floor(target_floor);
	print_open_doors(doors);
	
	while (1);
}

