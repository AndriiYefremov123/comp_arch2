ifneq ($(KERNELRELEASE),)
# Called from kernel build system
obj-m := hello.o

else
# Called from command line
KDIR ?= $(HOME)/repos/linux-stable
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) M=$(PWD) ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- clean

help:
	@echo "Targets:"
	@echo "  default - build module"
	@echo "  clean   - remove built files"

.PHONY: default clean help

endif
