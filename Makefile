CC = gcc

all:
	$(CC) src/*.c src/*.h -o orbits -lm

clean:
	rm -f *.o server
