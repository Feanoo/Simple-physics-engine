CC=gcc
CFLAGS=-g -Wall -Werror
LD=-lSDL2 -lSDL2main -lSDL2_ttf -lSDL2_image -lm
BINPATH=bin
SRCPATH=src

build: $(BINPATH)/engine

$(BINPATH)/engine: $(BINPATH)/main.o
	$(CC) $(BINPATH)/*.o -o $(BINPATH)/engine ${LD}

$(BINPATH)/main.o: $(SRCPATH)/main.*
	$(CC) -c ${CFLAGS} $(SRCPATH)/main.c -o $(BINPATH)/main.o

clean:
	rm -f $(BINPATH)/*.*