obj-m := rootest.o
rootest-objs := rootest_main.o kprobes_impl.o

KDIR := ../../linux-5.15.131
PWD := $(shell pwd)

all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean


