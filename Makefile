obj-m := rootest.o
rootest-objs := rootest_main.o kprobes_impl.o stealth.o kretprobes_impl.o signals_impl.o features.o kvm-amd.o

KDIR := ../../linux-5.15.131
PWD := $(shell pwd)

all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean


