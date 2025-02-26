TARGET=main.exe

all: $(TARGET)

$(TARGET): main.o vector.o
	gcc main.o vector.o -o $(TARGET)

main.o: main.c
	gcc -c main.c -o main.o

vector.o: vector.c
	gcc -c vector.c -o vector.o

.PHONY: clean

clean:
	del /f *.o

fullclean: clean
	del /f *.exe
