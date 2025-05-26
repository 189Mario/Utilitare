CC = gcc
CFLAGS = -Wall -g

TARGET = utilitare.out

OBJ = src/main.o src/header.o src/header1.o src/header2.o src/header3.o src/header4.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

src/main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c -o src/main.o

src/header.o: src/header.c
	$(CC) $(CFLAGS) -c src/header.c -o src/header.o

src/header1.o: src/header1.c
	$(CC) $(CFLAGS) -c src/header1.c -o src/header1.o

src/header2.o: src/header2.c
	$(CC) $(CFLAGS) -c src/header2.c -o src/header2.o

src/header3.o: src/header3.c
	$(CC) $(CFLAGS) -c src/header3.c -o src/header3.o

src/header4.o: src/header4.c
	$(CC) $(CFLAGS) -c src/header4.c -o src/header4.o

execute: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: clean execute
