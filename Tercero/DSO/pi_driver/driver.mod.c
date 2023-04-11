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
	{ 0x96c7326, "param_ops_int" },
	{ 0x92d5838e, "request_threaded_irq" },
	{ 0xc0a2d172, "gpiod_to_irq" },
	{ 0x63d6f4b5, "gpiod_direction_output_raw" },
	{ 0x47229b5c, "gpio_request" },
	{ 0x22cf21ef, "misc_register" },
	{ 0xc1514a3b, "free_irq" },
	{ 0x2b68bd2f, "del_timer" },
	{ 0xea3c74e, "tasklet_kill" },
	{ 0x19ed4106, "misc_deregister" },
	{ 0xfe990052, "gpio_free" },
	{ 0x2cfde9a2, "warn_slowpath_fmt" },
	{ 0xa28f08e7, "gpiod_get_raw_value" },
	{ 0x9d2ab8ac, "__tasklet_schedule" },
	{ 0xc38c83b8, "mod_timer" },
	{ 0x526c3a6c, "jiffies" },
	{ 0xca54fee, "_test_and_set_bit" },
	{ 0x7f02188f, "__msecs_to_jiffies" },
	{ 0xae353d77, "arm_copy_from_user" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0x92997ed8, "_printk" },
	{ 0x3ea1b6e4, "__stack_chk_fail" },
	{ 0x49970de8, "finish_wait" },
	{ 0x647af474, "prepare_to_wait_event" },
	{ 0x1000e51, "schedule" },
	{ 0xfe487975, "init_wait_entry" },
	{ 0x51a910c0, "arm_copy_to_user" },
	{ 0x5f754e5a, "memset" },
	{ 0x3c3ff9fd, "sprintf" },
	{ 0xca5a7528, "down_interruptible" },
	{ 0x800473f, "__cond_resched" },
	{ 0x581cde4e, "up" },
	{ 0x3dcf1ffa, "__wake_up" },
	{ 0x857b710b, "gpiod_set_raw_value" },
	{ 0x699fa999, "gpio_to_desc" },
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "58C7F4A83C64CDE0A077C52");
