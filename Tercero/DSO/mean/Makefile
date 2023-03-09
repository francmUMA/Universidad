MODULE=mean

KERNEL=`uname -r`
KERNEL_SRC=/lib/modules/${KERNEL}/build
 
obj-m += ${MODULE}.o
 
compile:
	@echo Usando kernel ${KERNEL}
	make -C ${KERNEL_SRC} M=$(PWD) modules

install: 
	sudo insmod ${MODULE}.ko 
	sudo dmesg | tail 

uninstall:
	sudo rmmod ${MODULE} 
	sudo dmesg | tail
