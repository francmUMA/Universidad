MODULE=driver

KERNEL_SRC=/lib/modules/`uname -r`/build

obj-m += $(MODULE).o



compile:
	make -C $(KERNEL_SRC) M=${CURDIR} modules

install:
	sudo insmod $(MODULE).ko
	sudo dmesg | tail

uninstall:
	sudo rmmod $(MODULE)
	sudo dmesg | tail
