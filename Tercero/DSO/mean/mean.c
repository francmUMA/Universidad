#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <linux/delay.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("DAC");
MODULE_DESCRIPTION("Modulo que printea la media de los valores introducidos.");

/****************************************************************************/
// Globals
/****************************************************************************/

#define ENTRY_NAME "mean"
#define PERMS 0644

static int counter;		//Guarda el número de valores introducidos
static int suma_acumulada;	//Guarda la suma acumulada de los valores de entrada

/****************************************************************************/
// proc file operations
/****************************************************************************/
ssize_t mean_proc_read(struct file *sp_file, char __user *buf, size_t size, loff_t *offset){
	char message[40];
    int len; 

    if (*offset > 0) return 0;

    printk(KERN_NOTICE "proc has called read\n");
    if (counter == 0) len = sprintf(message, "Aún no se ha introducido ningún valor\n");
    else len = sprintf(message, "COUNT -> %d \n MEDIA -> %d\n", counter, suma_acumulada / counter);    
    copy_to_user(buf, message, len);
    
    *offset += len;

    return len;
}

/*ssize_t mean_proc_write(){*/
	/*;*/
/*}*/


//Modificación de las operaciones de lectura y escritura
static struct proc_ops fops = {
        .proc_read  = mean_proc_read
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
