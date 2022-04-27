CC=gcc
CFLAGS=-g -Wall -Werror
LD=-lSDL2 -lSDL2main -lSDL2_ttf -lSDL2_image -lm
BINPATH=bin
SRCPATH=src

build: $(BINPATH)/engine

$(BINPATH)/engine: $(BINPATH)/main.o
	$(CC) $(BINPATH)/*.o -o $(BINPATH)/engine ${LD}

$(BINPATH)/main.o: $(SRCPATH)/main.* $(BINPATH)/engine.o
	$(CC) -c ${CFLAGS} $(SRCPATH)/main.c -o $(BINPATH)/main.o

$(BINPATH)/engine.o: $(SRCPATH)/engine.* $(BINPATH)/object.o
	$(CC) -c ${CFLAGS} $(SRCPATH)/engine.c -o $(BINPATH)/engine.o

$(BINPATH)/object.o: $(SRCPATH)/object.* $(BINPATH)/vector.o $(BINPATH)/circle.o
	$(CC) -c ${CFLAGS} $(SRCPATH)/object.c -o $(BINPATH)/object.o

$(BINPATH)/vector.o: $(SRCPATH)/vector.*
	$(CC) -c ${CFLAGS} $(SRCPATH)/vector.c -o $(BINPATH)/vector.o

$(BINPATH)/circle.o: $(SRCPATH)/circle.*
	$(CC) -c ${CFLAGS} $(SRCPATH)/circle.c -o $(BINPATH)/circle.o


clean:
	rm -f $(BINPATH)/*.*