#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/uaccess.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("DAC");
MODULE_DESCRIPTION("Modulo que printea la media de los valores introducidos.");

/****************************************************************************/
// Globals
/****************************************************************************/

#define ENTRY_NAME "mean"
#define PERMS 0666

static int counter;		//Guarda el número de valores introducidos
static int suma_acumulada;	//Guarda la suma acumulada de los valores de entrada

//Atoi
int atoi(const char* S, long *val)
{
    long num = 0;
    int i = 0;
    int numeric = S[i] && (S[i] >= '0' && S[i] <= '9');
    
 
    // run till the end of the string is reached, or the
    // current character is non-numeric
    while (numeric)
    { 
        num = num * 10 + (S[i] - '0');
        i++;   
        numeric = S[i] && (S[i] >= '0' && S[i] <= '9');
    }

    if (numeric) (*val) = num;
    else if ((!numeric && S[i] == '\n' && i > 0) || (!numeric && S[i] == '\0' && i > 0)) {
        numeric = 1;
        (*val) = num;
    } 
    
    return numeric;
}
 


/****************************************************************************/
// proc file operations
/****************************************************************************/
ssize_t mean_proc_read(struct file *sp_file, char __user *buf, size_t size, loff_t *offset){
	char message[40];
    int len; 

    if (*offset > 0) return 0;

    printk(KERN_NOTICE "proc has called read\n");
    if (counter == 0) len = sprintf(message, "Aún no se ha introducido ningún valor\n");
    else {
        int media = (suma_acumulada * 100) / counter;
        len = sprintf(message, "COUNT -> %d \nMEDIA -> %d.%02d\n", counter, media/100, media%100);
    }
    copy_to_user(buf, message, len);
    
    *offset += len;

    return len;
}

ssize_t mean_proc_write(struct file *filp, const char __user *buf, size_t count, loff_t *offset){
    char str_value[20];
    long value;
    if (copy_from_user(str_value, buf, count)) return -EFAULT;
    printk(KERN_NOTICE "Introducido: %s\n", str_value);
    if(strcmp(str_value, "CLEAR") == 0 || strcmp(str_value, "CLEAR\n") == 0) {
        counter = 0;
        suma_acumulada = 0;
    } else {
        int ret = atoi(str_value, &value);
        if (!ret) return -EINVAL;  
        counter += 1; 
        suma_acumulada += value;
    }
        *offset += count;
        return count;
}

//Modificación de las operaciones de lectura y escritura
static struct proc_ops fops = {
        .proc_read  = mean_proc_read,
        .proc_write = mean_proc_write
};



/****************************************************************************/
/* Module init / cleanup block.                                             */
/****************************************************************************/
int r_init(void){
	printk(KERN_NOTICE "Hello, loading mean module!\n");
	counter = 0;
	suma_acumulada = 0;
	printk(KERN_NOTICE "/proc/%s create\n", ENTRY_NAME);
        if (!proc_create(ENTRY_NAME, PERMS, NULL, &fops)) 
        {
                printk(KERN_ERR "ERROR! proc_create\n");
                remove_proc_entry(ENTRY_NAME, NULL);
                return -ENOMEM;
        }
    	return 0;
}

void r_cleanup(void){
	printk(KERN_NOTICE "DSO %s module cleaning up...\n",KBUILD_MODNAME);
    remove_proc_entry(ENTRY_NAME, NULL);
	printk(KERN_NOTICE "Removing /proc/%s.\n", ENTRY_NAME);
	printk(KERN_NOTICE "Done. Bye\n");
	return;

}

module_init(r_init);
module_exit(r_cleanup);
