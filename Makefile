CC = gcc

test: test.o aes.o CRC32.o
	$(CC) test.o aes.o CRC32.o -o test

test.exe: test.o aes.o CRC32.o
	$(CC) -o test.exe test.o aes.o CRC32.o 

test.o: test.c aes.h aes.h CRC32.c CRC32.h
	$(CC) -c test.c

aes.o: aes.c aes.h
	$(CC) -c aes.c

CRC32.o: CRC32.c CRC32.h
	$(CC) -c CRC32.c

clean:
	rm -f *.o *.exe 
	del -rf *.o *.exe 
