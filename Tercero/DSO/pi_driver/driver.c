#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/interrupt.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/jiffies.h>

#define DRIVER_AUTHOR "Francisco Javier Cano Moreno"
#define DRIVER_DESC "Driver de gestión de los GPIO para RaspberryPI"

#define LED1 9
#define LED2 10
#define LED3 11
#define LED4 17
#define LED5 22
#define LED6 27

#define SPEAKER 4

#define BUTTON1 2
#define BUTTON2 3

static int LED_GPIOS[] = {LED6, LED5, LED4, LED3, LED2, LED1};
static char pulsaciones[100];
static int pulsaciones_counter = 0;

static void byte2leds(char ch, int mode){
    int i;
    int val = (int) ch;
    if (mode == 0){
        for (i = 0; i<6; i++) gpio_set_value(LED_GPIOS[i], (val >> i) & 1);
    } else if (mode == 1){
        for (i = 0; i<6; i++) {
            if ((val >> i) & 0x01) gpio_set_value(LED_GPIOS[i], 1);
        }
    } else if (mode == 2){
        for (i = 0; i<6; i++) {
            if (!((val >> i) & 0x01)) gpio_set_value(LED_GPIOS[i], 0);
        }
    } else if (mode == 3){
        for (i = 0; i<6; i++) {
            if ((val >> i) & 0x01) gpio_set_value(LED_GPIOS[i], 0);
            else gpio_set_value(LED_GPIOS[i], 1); 
        }
    }
}   

/****************************************************************************/
/* Leds driver file operations */
/****************************************************************************/

static ssize_t leds_read(struct file *filp, char *buf, size_t count, loff_t *offset){
    char message[80]; 

    if (*offset > 0) return 0;

    int len = sprintf(message, 
                      "STATUS\nLED6 -> %i\nLED5 -> %i\nLED4 -> %i\nLED3 -> %i\nLED2 -> %i\nLED1 -> %i\n",
                      gpio_get_value(LED6), gpio_get_value(LED5), gpio_get_value(LED4), gpio_get_value(LED3),
                      gpio_get_value(LED2), gpio_get_value(LED1));
    if (copy_to_user(buf, message, len)) return -EFAULT;
    *offset += len;
    return len;
}

static ssize_t leds_write(struct file *filp, const char *buf, size_t count, loff_t *offset){
	unsigned char ch;
	if (copy_from_user(&ch, buf, 1)) return -EFAULT;
	printk(KERN_INFO "Valor recibido: %d\n", (int) ch);
    if ((ch >> 6) & 0x01){
        byte2leds(ch, 1);
    }
    else if ((ch >> 6) & 0x02){
        byte2leds(ch, 2);            
    }
    else if ((ch >> 6) & 0x03){
        byte2leds(ch, 3);
    } else {
        byte2leds(ch, 0);
    }
        
    return 1;
}

    

static const struct file_operations leds_fops = {
	.read = leds_read,
    .write = leds_write,
};


static struct miscdevice leds_miscdev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name  = "leds",
	.fops  = &leds_fops,
	.mode  = S_IRUGO | S_IWUGO,
};

/****************************************************************************/
/* Speaker driver file operations */
/****************************************************************************/

static ssize_t speaker_write(struct file *filp, const char *buf, size_t count, loff_t *offset){
    unsigned char ch;
	if (copy_from_user(&ch, buf, 1)) return -EFAULT;
    printk(KERN_INFO "Valor recibido: %d\n", (int) ch);
    if (ch == '0') gpio_set_value(SPEAKER, 0);
    else gpio_set_value(SPEAKER, 1);
    return 1;
}

static const struct file_operations speaker_fops = {
	.write = speaker_write,
};


static struct miscdevice speaker_miscdev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name  = "speaker",
	.fops  = &speaker_fops,
	.mode  = S_IWUGO,
};

/****************************************************************************/
/* Buttons driver file operations */
/****************************************************************************/
static short int irq_BUTTON1 = 0;
static short int irq_BUTTON2 = 0;

static void tasklet_handler(unsigned long dato){
    if (dato == 1) pulsaciones[pulsaciones_counter] = '1';
    else pulsaciones[pulsaciones_counter] = '2';
    pulsaciones_counter+=1;
}

static DECLARE_TASKLET(tasklet_button, tasklet_handler);

static irqreturn_t irq_handler(int irq, void *dev_id, struct pt_regs *regs){
    unsigned long data;
    if (irq == irq_BUTTON1) data = 1;
    else if (irq == irq_BUTTON2) data = 2;
    tasklet_init(&tasklet_button, tasklet_handler, data);
    tasklet_schedule(&tasklet_button);
    return IRQ_HANDLED;
}

static ssize_t buttons_read(struct file *filp, char *buf, size_t count, loff_t *offset){
    if (*offset > 0) return 0;
    int len = strlen(pulsaciones);
    if (copy_to_user(buf, pulsaciones, len)) return -EFAULT;
    *offset += len;
    return len;
}


static const struct file_operations buttons_fops = {
	.read = buttons_read,
};


static struct miscdevice buttons_miscdev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name  = "buttons",
	.fops  = &buttons_fops,
	.mode  = S_IRUGO,
};


//Register devices
static int r_dev_config(void){
	int ret = 0;
	ret = misc_register(&leds_miscdev);
	if (ret < 0){
		printk(KERN_ERR "ERROR registering leds\n");
	} else printk(KERN_NOTICE "Leds device has been registered -> leds_miscdev.minor=%d\n", leds_miscdev.minor);
	
    ret = misc_register(&speaker_miscdev);
    if (ret < 0){
		printk(KERN_ERR "ERROR registering speaker\n");
	} else printk(KERN_NOTICE "Speaker device has been registered -> speaker_miscdev.minor=%d\n", speaker_miscdev.minor);
    
    ret = misc_register(&buttons_miscdev);
    if (ret < 0){
		printk(KERN_ERR "ERROR registering buttons\n");
	} else printk(KERN_NOTICE "Buttons device has been registered -> buttons_miscdev.minor=%d\n", buttons_miscdev.minor);

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
    gpio_free(SPEAKER);
    gpio_free(BUTTON1);
    gpio_free(BUTTON2);

    if (leds_miscdev.this_device) misc_deregister(&leds_miscdev);
    if (speaker_miscdev.this_device) misc_deregister(&speaker_miscdev);
    if (buttons_miscdev.this_device) misc_deregister(&buttons_miscdev);

    if (irq_BUTTON1) free_irq(irq_BUTTON1, "Se ha pulsado el boton 1");
    if (irq_BUTTON2) free_irq(irq_BUTTON2, "Se ha pulsado el boton 2");

    tasklet_kill(&tasklet_button);

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

    if(gpio_is_valid(SPEAKER) < 0) return -1;
        if(gpio_request(SPEAKER, "SPEAKER") < 0) return -1;
    if(gpio_is_valid(BUTTON1) < 0) return -1;
        if(gpio_request(BUTTON1, "BUTTON1") < 0) return -1;
    if(gpio_is_valid(BUTTON2) < 0) return -1;
        if(gpio_request(BUTTON2, "BUTTON2") < 0) return -1;  

    //Set GPIO as output
    gpio_direction_output(LED1, 0 );
    gpio_direction_output(LED2, 0 );
    gpio_direction_output(LED3, 0 );
    gpio_direction_output(LED4, 0 );
    gpio_direction_output(LED5, 0 );
    gpio_direction_output(LED6, 0 );
    gpio_direction_output(LED6, 0 );
    gpio_direction_output(SPEAKER, 0 );

    //Configure irqs
    if ((irq_BUTTON1 = gpio_to_irq(BUTTON1)) < 0){
        printk(KERN_ERR "GPIO to irq mapping failed.\n");
        return irq_BUTTON1;
    }

    if ((irq_BUTTON2 = gpio_to_irq(BUTTON2)) < 0){
        printk(KERN_ERR "GPIO to irq mapping failed.\n");
        return irq_BUTTON2;
    }

    int res = 0;
    if ((res = request_irq(irq_BUTTON1,
                           (irq_handler_t) irq_handler,
                           IRQF_TRIGGER_FALLING,
                           "BUTTON1",
                           "Se ha pulsado el boton 1"))) {
        printk(KERN_ERR "IRQ request failed\n");
        return res;
    }
    if ((res = request_irq(irq_BUTTON2,
                           (irq_handler_t) irq_handler,
                           IRQF_TRIGGER_FALLING,
                           "BUTTON2",
                           "Se ha pulsado el boton 2"))) {
        printk(KERN_ERR "IRQ request failed\n");
        return res;
    }


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
