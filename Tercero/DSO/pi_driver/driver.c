#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/uaccess.h>

#define DRIVER_AUTHOR "Francisco Javier Cano Moreno"
#define DRIVER_DESC "Driver de gestión de los GPIO para RaspberryPI"

#define LED1 9
#define LED2 10
#define LED3 11
#define LED4 17
#define LED5 22
#define LED6 27


/****************************************************************************/
/* GPIO initialization and freeing*/
/****************************************************************************/

int initGPIO(){
    //Request all GPIOs
    if(gpio_is_valid(LED1) < 0) return -1;
	if(gpio_request(LED1, "LED1") < 0) return -1;

    if(gpio_is_valid(LED2) < 0) return -1;
	if(gpio_request(LED2, "LED2") < 0) return -1;

    if(gpio_is_valid(LED3) < 0) return -1;
	if(gpio_request(LED3, "LED3") < 0) return -1;

    if(gpio_is_valid(LED4) < 0) return -1;
	if(gpio_request(LED4, "LED4") < 0) return -1;

    if(gpio_is_valid(LED5) < 0) return -1;
	if(gpio_request(LED5, "LED5") < 0) return -1;

    if(gpio_is_valid(LED6) < 0) return -1;
	if(gpio_request(LED6, "LED6") < 0) return -1;

    //Set GPIO as output
    gpio_direction_output(LED1, 0 );
    gpio_direction_output(LED2, 0 );
    gpio_direction_output(LED3, 0 );
    gpio_direction_output(LED4, 0 );
    gpio_direction_output(LED5, 0 );
    gpio_direction_output(LED6, 0 );

    return 0;
}

void freeGPIO(){
    gpio_free(LED1);
    gpio_free(LED2);
    gpio_free(LED3);
    gpio_free(LED4);
    gpio_free(LED5);
    gpio_free(LED6);
}

/****************************************************************************/
/* Leds driver file operations */
/****************************************************************************/

ssize_t leds_read(struct file *file, const char __user *buf, size_t count, lofft_t *offset){
    char message[80]; 

    if (*offset > 0) return 0;

    int len = sprintf(message, 
                      "STATUS\nLED1 -> %i\nLED2 -> %i\nLED3 -> %i\nLED4 -> %i\nLED5 -> %i\nLED6 -> %i\n",
                      gpio_get_value(LED1), gpio_get_value(LED2), gpio_get_value(LED3), gpio_get_value(LED4),
                      gpio_get_value(LED5), gpio_get_value(LED6));
    copy_to_user(buf, message, len);
    *offset += len;
    return len;
}


/****************************************************************************/
/* Module init / cleanup block. */
/****************************************************************************/
static int r_init(void) {
    if (initGPIO() < 0) {
        printk(KERN_ERR "Error initializating GPIOs");
        return -1;
    }

    printk(KERN_NOTICE "Hey, %s module is being loaded!\n",KBUILD_MODNAME);
    return 0;
}


static void r_cleanup(void) {
    freeGPIO();
    printk(KERN_NOTICE "Removing %s module\n",KBUILD_MODNAME);
    return;
}

module_init(r_init);
module_exit(r_cleanup);


/****************************************************************************/
/* Module licensing/description block. */
/****************************************************************************/
MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
