#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>

#define DRIVER_AUTHOR "Francisco Javier Cano Moreno"
#define DRIVER_DESC "Driver de gestión de los GPIO para RaspberryPI"

#define LED1 9
#define LED2 10
#define LED3 11
#define LED4 17
#define LED5 22
#define LED6 27

/****************************************************************************/
/* Leds driver file operations */
/****************************************************************************/

static ssize_t leds_read(struct file *filp, char *buf, size_t count, loff_t *offset){
    char message[80]; 

    if (*offset > 0) return 0;

    int len = sprintf(message, 
                      "STATUS\nLED1 -> %i\nLED2 -> %i\nLED3 -> %i\nLED4 -> %i\nLED5 -> %i\nLED6 -> %i\n",
                      gpio_get_value(LED1), gpio_get_value(LED2), gpio_get_value(LED3), gpio_get_value(LED4),
                      gpio_get_value(LED5), gpio_get_value(LED6));
    if (copy_to_user(buf, message, len)) return -EFAULT;
    *offset += len;
    return len;
}

static ssize_t leds_write(struct file *filp, const char *buf, size_t count, loff_t *offset){
	unsigned char ch;
	if (copy_from_user(&ch, buf, 1)) return -EFAULT;
	printk(KERN_INFO "Valor recibido: %d\n", (int) ch);
	if ((ch >> 6) & 0x00){}
	else if (ch & 0x80){}
	else if (ch & 0x40){}
	else if (ch)
}

static const struct file_operations leds_fops = {
	.read = leds_read,
};

static struct miscdevice leds_miscdev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name  = "leds",
	.fops  = &leds_fops,
	.mode  = S_IRUGO,
};

//Register devices
static int r_dev_config(void){
	int ret = 0;
	ret = misc_register(&leds_miscdev);
	if (ret < 0){
		printk(KERN_ERR "ERROR registering leds\n");
	} else printk(KERN_NOTICE "Leds device has been registered -> leds_miscdev.minor=%d\n", leds_miscdev.minor);
	return ret;
}

/****************************************************************************/
/* Module init / cleanup block. */
/***************************************************************************/

static void r_cleanup(void) {
    gpio_free(LED1);
    gpio_free(LED2);
    gpio_free(LED3);
    gpio_free(LED4);
    gpio_free(LED5);
    gpio_free(LED6);

    if (leds_miscdev.this_device) misc_deregister(&leds_miscdev);
    printk(KERN_NOTICE "Removing %s module\n",KBUILD_MODNAME);
    return;
}

static int r_init(void) {
        if (r_dev_config() < 0){
                r_cleanup();
                return -1;
        }       

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


    printk(KERN_NOTICE "Hey, %s module is being loaded!\n",KBUILD_MODNAME);
    return 0;
}


module_init(r_init);
module_exit(r_cleanup);


/****************************************************************************/
/* Module licensing/description block. */
/****************************************************************************/
MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
