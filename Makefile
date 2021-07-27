all: bin/snake

bin/snake: obj bin obj/terminal.o obj/input.o obj/game.o obj/main.o
	gcc -o bin/snake obj/* -lncurses -pthread

obj/game.o: obj game.c game.h
	gcc -c game.c -o obj/game.o

obj/terminal.o: obj terminal.c terminal.h
	gcc -c terminal.c -o obj/terminal.o

obj/input.o: obj input.c input.h
	gcc -c input.c -o obj/input.o

obj/main.o: obj main.c
	gcc -c main.c -o obj/main.o

obj:
	mkdir -p obj

bin:
	mkdir -p bin

install: bin/snake
	cp bin/snake /usr/local/bin/

clear:
	rm -rf obj
	rm -rf bin
