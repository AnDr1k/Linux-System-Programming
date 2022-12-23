CC := $(CROSS_COMPILE)gcc
SRC := writer.c
TARGET = writer
OBJS := $(SRC:.c=.o)

all: $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

clean:
	-rm -f *.o $(TARGET)
