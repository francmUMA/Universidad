#include <avr/io.h>

int main(){
    unsigned char b;
    DDRD = (1<<PIND0) | (1<<PIND1) | (1<<PIND2);    //Salida los 3 primeros bits
    DDRB = 0x00;                                    //Entrada
    DDRC = 0xFF;                                    //Salida

    while(1){
        b = PINB;
        PORTC = b;                                  //Escribe en el 7 segmentos
        switch (b) {
            case 58: 
                PORTD ^= (1<<PIND0);
                break;
            case 69:
                PORTD ^= (1<<PIND1);
                break;
            case 70:
                PORTD ^= (1<<PIND2);
                break;
            default:
                PORTD &= ~(0x07);
        }
    }
}
