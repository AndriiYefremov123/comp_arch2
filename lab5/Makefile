ifneq ($(KERNELRELEASE),)
# Called from kernel build system

# Add include directory
ccflags-y := -I$(src)/inc

# Build both modules
obj-m := hello1.o hello2.o

else
# Called from command line
KDIR ?= $(HOME)/repos/linux-stable
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) M=$(PWD) ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- clean
	rm -f inc/*~

help:
	@echo "Targets:"
	@echo "  default - build modules"
	@echo "  clean   - remove built files"

.PHONY: default clean help

endif
