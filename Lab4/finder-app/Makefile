all:
	make clean
	make default

clean:
	rm -rf ./writer ./*.o

objects: writer.c
	$(CROSS_COMPILE)gcc -g -Wall -c -o writer.o writer.c

default: writer.o objects
	$(CROSS_COMPILE)gcc -g -Wall -o writer writer.o
