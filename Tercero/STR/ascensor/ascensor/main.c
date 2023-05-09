/*
 * ascensor.c
 *
 * Created: 06/05/2023 10:29:42
 * Author : Fran
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#define FLOOR_0 1
#define FLOOR_1 2
#define FLOOR_2 3
#define STOPPED 0

#define PARADO		10000
#define ASCIENDE	200
#define DESCIENDE	20000

volatile uint8_t current_floor = FLOOR_0;
volatile uint8_t target_floor = STOPPED;
volatile uint8_t doors = STOPPED;
volatile uint8_t people = 0;				//hay gente dentro del ascensor
volatile uint8_t elevator = 0;				//Parado = 0, Moviendose = 1
volatile uint8_t is_free = 1;

void print_open_doors(unsigned char data){		
	PORTB = ((data & 0x01) << PINB2) | (((PORTB >> PINB1) & 0x01) << PINB1) | (((data & 0x02) >> 1) << PINB0);
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
	if (!elevator){
		if (people && doors == STOPPED){
			target_floor = FLOOR_2;
			stop_timer0();
			if (target_floor == current_floor){
				//NO SE HACE NADA
				;
			} else{
				// Sabemos que solo se puede ascender
				target_floor = FLOOR_2;
				print_target_floor(target_floor);
				OCR1AH = (ASCIENDE >> 8) & 0xFF;
				OCR1AL = ASCIENDE & 0x00FF;
			
				// Se carga el delay correspondiente
				OCR0A  = 50 * (target_floor - current_floor);
				elevator = 1;
				start_timer0();
			}
		}else if(is_free){
			target_floor = FLOOR_2;
			is_free = 0;
			if (target_floor == current_floor){
				// El ascensor se abre para que entre gente
				people = 1;
				doors = FLOOR_2;
				print_open_doors(doors);
				start_timer0();
			} else{
				// Sabemos que solo se puede ascender
				target_floor = FLOOR_2;
				print_target_floor(target_floor);
				OCR1AH = (ASCIENDE >> 8) & 0xFF;
				OCR1AL = ASCIENDE & 0x00FF;
			
				// Se carga el delay correspondiente
				OCR0A  = 50 * (target_floor - current_floor);
				elevator = 1;
				start_timer0();
			}
		}
	}
}

ISR(TIMER0_COMPA_vect){
	if (elevator == 0){
		if (doors != STOPPED) {
			doors = STOPPED;
			print_open_doors(doors);
		} else {
			stop_timer0();
			is_free = 1;
		}
	} else {
		current_floor = target_floor;
		print_current_floor(current_floor);
		target_floor = STOPPED;
		print_target_floor(target_floor);
		
		//Parar ascensor
		OCR1AH = (PARADO >> 8) & 0xFF;
		OCR1AL = PARADO & 0x00FF;
		
		//Abrir puertas
		elevator = 0;
		doors = current_floor;
		print_open_doors(doors);
		OCR0A = 250;
		if (people) people = 0;
		else people = 1;
	}
}

ISR(PCINT0_vect){
	if (!elevator){
		if (PINB & (1 << PINB3)){			//Boton A
			if (people && doors == STOPPED){
				target_floor = FLOOR_0;
				stop_timer0();
				if (target_floor == current_floor){
					//NO SE HACE NADA
					;
				} else{
					// Sabemos que solo se puede descender
					print_target_floor(target_floor);
					OCR1AH = (DESCIENDE >> 8) & 0xFF;
					OCR1AL = DESCIENDE & 0x00FF;
				
					// Se carga el delay correspondiente
					OCR0A  = 50 * (current_floor - target_floor);
					elevator = 1;
					start_timer0();
				}
			}else if(is_free){
				target_floor = FLOOR_0;
				is_free = 0;
				if (target_floor == current_floor){
					// El ascensor se abre para que entre gente
					people = 1;
					doors = FLOOR_0;
					print_open_doors(doors);
					start_timer0();
				} else{
					// Sabemos que solo se puede descender
					target_floor = FLOOR_0;
					print_target_floor(target_floor);
					OCR1AH = (DESCIENDE >> 8) & 0xFF;
					OCR1AL = DESCIENDE & 0x00FF;
				
					// Se carga el delay correspondiente
					OCR0A  = 50 * (current_floor - target_floor);
					elevator = 1;
					start_timer0();
				}
			}
		}
	
	
		else if (PINB & (1<<PINB4)){		//Boton B
			if (people && doors == STOPPED){
				target_floor = FLOOR_1;
				stop_timer0();
				if (target_floor == current_floor){
					//NO SE HACE NADA
					;
				} else{
					// Tenemos que averiguar si hay que ascender o descender
					print_target_floor(target_floor);
					if (target_floor > current_floor){
						OCR1AH = (ASCIENDE >> 8) & 0xFF;
						OCR1AL = ASCIENDE & 0x00FF;
					} else {
						OCR1AH = (DESCIENDE >> 8) & 0xFF;
						OCR1AL = DESCIENDE & 0x00FF;
					}
				
					// Se carga el delay correspondiente
					OCR0A  = 50;
					elevator = 1;
					start_timer0();
				}
			}else if (is_free){
				target_floor = FLOOR_1;
				is_free = 0;
				if (target_floor == current_floor){
					// El ascensor se abre para que entre gente
					people = 1;
					doors = FLOOR_1;
					print_open_doors(doors);
					start_timer0();
				} else{
					// Tenemos que averiguar si hay que subir o bajar
					target_floor = FLOOR_1;
					print_target_floor(target_floor);
					if (target_floor > current_floor){
						OCR1AH = (ASCIENDE >> 8) & 0xFF;
						OCR1AL = ASCIENDE & 0x00FF;
					} else {
						OCR1AH = (DESCIENDE >> 8) & 0xFF;
						OCR1AL = DESCIENDE & 0x00FF;
					}
				
					// Se carga el delay correspondiente
					OCR0A  = 50 * (target_floor - current_floor);
					elevator = 1;
					start_timer0();
				}
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

