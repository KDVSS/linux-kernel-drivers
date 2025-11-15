KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

obj-m := platform_driver_core.o

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	rm -f *.ko
