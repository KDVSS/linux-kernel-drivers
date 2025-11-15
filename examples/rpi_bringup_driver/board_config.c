#include <common.h>
//#include <asm/io.h>
#include <linux/types.h>


#define CLOCK_CONTROLLER_BASE 0x44000000
#define DRAM_CONTROLLER_BASE  0x44100000
#define UART_CONTROLLER_BASE  0x44E09000

#define CLK_PLL_REG             (CLOCK_CONTROLLER_BASE + 0x04)
#define DRAM_TIMING_REG         (DRAM_CONTROLLER_BASE + 0x10)
#define UART_BAUD_REG           (UART_CONTROLLER_BASE + 0x00)

static void early_system_init(void){
	writel(0x01E03001, CLK_PLL_REG);
}

static int dram_init(void){
	writel(0x5432, DRAM_TIMING_REG);
	return 0;
}

int board_init_r(struct global_data *gd, bd_t *bd){
	early_system_init();
	writel(96, UART_BAUD_REG);

	printk(KERN_NOTICE "U-Boot: Board Relocation Stage started.\n");
	printk(KERN_INFO "U-Boot: Console (UART) is Active.\n");

	dram_inti();
	printk(KERN_INFO "U-Boot: Memory and Basic clocks configured.\n");

	//mmc_init_controller();
	printk(KERN_INFO "U-Boot: Loading kernel from MMC/SD card...\n");

	return 0;
}



