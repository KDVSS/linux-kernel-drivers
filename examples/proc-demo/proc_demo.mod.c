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
	{ 0x6106f7fb, "proc_create" },
	{ 0x122c3a7e, "_printk" },
	{ 0x71c90ddc, "single_open" },
	{ 0xb70166e7, "seq_printf" },
	{ 0x51aebcc9, "proc_remove" },
	{ 0x661256ad, "seq_read" },
	{ 0x9300ac8c, "seq_lseek" },
	{ 0x10139ad8, "single_release" },
	{ 0x474e54d2, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "056E6E7BD03206D5170CC72");
