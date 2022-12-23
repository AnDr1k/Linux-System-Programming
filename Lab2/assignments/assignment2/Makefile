CC=${CROSS-COMPILE}gcc

CFLAGS= -g -Wall

default: writer

writer: writer.c
	${CC} ${CFLAGS} -o $@ $^

clean:
	rm -f writer
