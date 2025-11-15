#include <linux/module.h>
#include <linux/export-internal.h>
#include <linux/compiler.h>

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



static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x122c3a7e, "_printk" },
	{ 0x36a78de3, "devm_kmalloc" },
	{ 0xef7fa408, "platform_get_resource" },
	{ 0xcae3b64b, "devm_ioremap_resource" },
	{ 0x23e91bcc, "platform_device_unregister" },
	{ 0x61fd46a9, "platform_driver_unregister" },
	{ 0xdcb764ad, "memset" },
	{ 0xdcbfa77, "platform_device_register_full" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0xfa474811, "__platform_driver_register" },
	{ 0x474e54d2, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "EB3017A58A7EBCB63C884B4");
