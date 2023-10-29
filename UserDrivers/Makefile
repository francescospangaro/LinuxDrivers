obj-m += hello-5.o 	# this is what is used to build single file modules
			# just write obj-m += xxx.o to have make
			# compile the c file
			# note: xxx.o must match xxx.c

# the combination of this two lines builds both modules together
obj-m += startstop.o
startstop-objs := start.o stop.o


all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)?build M=$(PWD) clean
