CC=gcc
FLAGS=-Wall -Wextra
SANTS=-fsanitize=address,undefined -g
OUTPUT=main.uwu

$(OUTPUT): build/main.o build/parser.o build/tools.o
	$(CC) build/main.o build/parser.o build/tools.o $(FLAGS) $(SANTS) -o build/$(OUTPUT)

builddir:
	mkdir build -p

build/tools.o: src/tools.c
	make builddir
	$(CC) src/tools.c -c -o build/tools.o $(SANTS)

build/main.o: src/main.c
	make builddir
	$(CC) src/main.c -c -o build/main.o $(SANTS)
build/parser.o: src/parser.c
	make builddir
	$(CC) src/parser.c -c -o  build/parser.o $(SANTS)

launch:
	make
	clear
	./build/$(OUTPUT)
