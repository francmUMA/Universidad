#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* - Para poder usar las lineas de C/D y de STB/SCK, se debe poner a 0 CS
 *
 *
*/

void LCD_enable(){
    HAL_GPIO_WritePin(GPIOX,1);
}

void LCD_disable(){
    HAL_GPIO_WritePin(GPIOX, 0);
}

void LCD_enviarByte(uint8_t comando, uint8_t byte){
    //Comprobar si BUSY esta listo
    LCD_ocupado;

    //Activar CS
    HAL_GPIO_WritePin(GPIO_CS_PIN, 0);
    
    //Señalizamos con la entrada la linea CD
    HAL_GPIO_WritePin(GPIO_CD_PIN, comando);

    //Envio del dato
    for (int i = 7; i >= 0; i--){
        HAL_GPIO_WritePin(GPIO_SCK_PIN, 1);
        delay(1);
        HAL_GPIO_WritePin(GPIO_SCK_PIN, 0);
        delay(1);
        HAL_GPIO_WritePin(GPIO_SI_PIN, (byte >> i) & 1);
    }

    //Desactivar CS
    HAL_GPIO_WritePin(GPIO_CS_PIN, 1);
}

//0 entran por la izquierda, 1 entran por la derecha
void LCD_inicializacion(int banco, int entrada_caracteres){
    LCD_enable();

    //Poner la frecuencia por defecto
    LCD_enviarByte(1, 0x10);

    //Banco = 0 -> 18, Banco = 1 -> 19
    if (banco == 0) LCD_enviarByte(1, 0x18);
    else if (banco == 1) LCD_enviarByte(1, 0x19);
    
    //Display ON -> 0x09
    LCD_enviarByte(1, 0x09);

    //Entrada de caracteres
    if (entrada_caracteres) LCD_enviarByte(1, 71);
    else LCD_enviarByte(1, 72);
    
}

void LCD_ocupado(void){ 
    while (!HAL_GPIO_ReadPin(GPIOA, BUSY_Pin)); 
}
