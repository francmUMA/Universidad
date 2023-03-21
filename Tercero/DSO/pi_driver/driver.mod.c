#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x40f2afe2, "module_layout" },
	{ 0x47229b5c, "gpio_request" },
	{ 0x22cf21ef, "misc_register" },
	{ 0x92997ed8, "_printk" },
	{ 0x19ed4106, "misc_deregister" },
	{ 0xfe990052, "gpio_free" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0x3ea1b6e4, "__stack_chk_fail" },
	{ 0x2cfde9a2, "warn_slowpath_fmt" },
	{ 0x51a910c0, "arm_copy_to_user" },
	{ 0x3c3ff9fd, "sprintf" },
	{ 0xa28f08e7, "gpiod_get_raw_value" },
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
	{ 0x63d6f4b5, "gpiod_direction_output_raw" },
	{ 0x699fa999, "gpio_to_desc" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "5BAD83C8F33B693FA08FCC2");
