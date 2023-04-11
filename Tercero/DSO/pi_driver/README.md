# Driver de control de los leds, el speaker y los botones de la placa auxiliar Raspberry PI

Para la realización del driver, se crean tres archivos en el directorio */dev*: *leds*, *speaker* y *buttons*. 

## LEDS
El archivo *leds* permite encender y apagar los leds de la placa auxiliar. Para ello, se debe escribir en el archivo un carácter, que representa un byte, donde los dos bits más significativos describen el modo de encendido de los leds, y el resto el estado de los leds. Después, con el comando *cat* se puede leer el estado de los leds.

### Modos de encendido
- *00*: Los leds se encienden y apagan con el valor de cada bit.
- *01*: Solamente se encienden los leds que tienen valor 1 y el resto se queda como está.
- *10*: Solamente se apagan los leds que tienen valor 1 y el resto se queda como está.
- *11*: Se encienden los leds de forma inversa, es decir, los leds que tienen valor 0 se encienden y los que tienen valor 1 se apagan.

### Implementación
- En primer lugar, se ha necesitado de una función que recibe un byte por parámetro y escribe en los leds el valor correspondiente según el modo. Dicha función es *byte2leds*.
- El driver debe ser de escritura y de lectura por lo que se crean dos funciones, *leds_read* y *leds_write*, que se encargan de leer y escribir en el archivo *leds* respectivamente.
- La función *leds_read* lee el estado de los leds y lo escribe en el buffer de lectura mediante la función *copy_to_user*. Por otro lado, la función *leds_write* recibe el byte que se quiere escribir en los leds mediante *copy_from_user* y lo escribe mediante la función *byte2leds*.
- Para la configuración de los GPIOs, en *r_init*, solicitamos los GPIOs de los leds mediante *gpio_request* y los configuramos como salida mediante *gpio_direction_output*. Después, en *r_cleanup*, liberamos los GPIOs mediante *gpio_free*.
- Por último, debemos registrar el device mediante *misc_register* y desregistrarlo mediante *misc_deregister*.