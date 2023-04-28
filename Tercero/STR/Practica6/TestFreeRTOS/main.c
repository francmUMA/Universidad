#include "FreeRTOS.h"
#include "task.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "semphr.h"
// GLOBAL VARS
unsigned char contador = 0;
SemaphoreHandle_t mi_semaforo;

void initLEDS(){
	DDRB |= (1 << PINB2) | (1 << PINB1) | (1 << PINB0);
	DDRC |= (1 << PINC3) | (1 << PINC4);
	DDRD |= (1 << PIND4) | (1 << PIND5) | (1 << PIND7);
}

void digitalWrite(unsigned char data){
	PORTB = ((data & 0x01) << PINB2) | (((data & 0x02) >> 1) << PINB1) | (((data & 0x04) >> 2) << PINB0);
	PORTD = (((data & 0x20) >> 5) << PIND4) | (((data & 0x10) >> 4) << PIND5) | (((data & 0x08) >> 3) << PIND7);
	PORTC = (((data & 0x80) >> 7) << PINC3) | (((data & 0x40) >> 6) << PINC4);
}

void incrementarContador(void* parameter)
{
	while(mi_semaforo == NULL); // Wait for semaphore to be ready
	for (;;)
	{
		// See if we can obtain the semaphore. If the semaphore is not
		// available wait 10 ticks to see if it becomes free.
		if(xSemaphoreTake(mi_semaforo, ( TickType_t ) 10 ) == pdTRUE )
		{
			// WE GOT THE SEMAPHORE
			contador++;
			digitalWrite(contador);
		}
		else {
			// WE COULD NOT GET THE SEMAPHORE, WAIT AGAIN
		}
	}
}
// MAIN PROGRAM
int main(void)
{
	initLEDS();
	// CONFIGURE IRQ
	PCICR = 0x01;
	PCMSK0 = 0x10;
	sei();
	
	// CREATE BLINKER TASK AND ITS SEMPAHORE
	mi_semaforo = xSemaphoreCreateBinary();
	xTaskCreate(incrementarContador, 
				"mitask", 
				configMINIMAL_STACK_SIZE, 
				NULL,
				tskIDLE_PRIORITY, 
				NULL);
	// START SCHELUDER
	vTaskStartScheduler();
	return 0;
}
// IDLE TASK
void vApplicationIdleHook(void)
{
	// THIS RUNS WHILE NO OTHER TASK RUNS
}
ISR(PCINT0_vect)
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	xSemaphoreGiveFromISR(mi_semaforo, &xHigherPriorityTaskWoken);
}