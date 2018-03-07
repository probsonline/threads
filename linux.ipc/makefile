
LIB_OBJS=\
	producer.o \
	consumer.o \
	
.PHONY: all

all: $(LIB_OBJS) testIPC.o
	gcc -o test $(LIB_OBJS) testIPC.o
	
producer.o:producer.c defs.h
	gcc -Wall -g -c -o producer.o producer.c
	
consumer.o:consumer.c defs.h
	gcc -Wall -g -c -o consumer.o consumer.c
	
testIPC.o:testIPC.c defs.h
	gcc -Wall -g -c -o testIPC.o testIPC.c
	
.PHONY: clean

clean:
	rm -f *.o
	rm test
