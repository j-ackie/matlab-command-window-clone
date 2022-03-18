output: src/vector.o src/linalgebra.o
	gcc src/vector.o src/linalgebra.o -o linalgebra

vector.o: src/vector.c src/vector.h
	gcc -c src/vector.c

linalgebra.o: src/linalgebra.c
	gcc -c src/linalgebra.c

clean:
	rm src/*.o linalgebra
