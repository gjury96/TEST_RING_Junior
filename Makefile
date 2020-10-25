CC = gcc

ifeq ($(detected_OS),Windows)
    CFLAGS += -D WIN32
endif
ifeq ($(detected_OS),Darwin)        
    CFLAGS += -D OSX
endif
ifeq ($(detected_OS),Linux)        
    CFLAGS += -D Linux
endif

ifeq ($(CFLAGS),WIN32)
test.exe: test.o aes.o CRC32.o
	$(CC) -o test.exe test.o aes.o CRC32.o 
endif
ifeq ($(CFLAGS),Linux)        
test: test.o aes.o CRC32.o
	$(CC) test.o aes.o CRC32.o -o test
endif
ifeq ($(CFLAGS),OSX)        
test: test.o aes.o CRC32.o
	$(CC) test.o aes.o CRC32.o -o test
endif

test.o: test.c aes.h aes.h CRC32.c CRC32.h
	$(CC) -c test.c

aes.o: aes.c aes.h
	$(CC) -c aes.c

CRC32.o: CRC32.c CRC32.h
	$(CC) -c CRC32.c

clean:
	rm -f *.o *.exe 
	del -rf *.o *.exe 
	
