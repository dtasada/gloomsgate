build:
	gcc -Wall ./src/*.c -o game -lSDL2

run:
	make build && ./game

clean:
	rm game
