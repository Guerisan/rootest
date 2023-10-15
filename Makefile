obj-m += rootest.o 

PWD := $(CURDIR) 

all: 

		make -C ../../linux-5.15.131 M=$(PWD) modules 

clean: 

		make -C ../../linux-5.15.131 M=$(PWD) clean


