all: linalgebra test-vector

linalgebra: src/linalgebra.o src/vector.o
	gcc -o src/linalgebra.c src/vector.c

linalgebra.o: src/linalgebra.c src/linalgebra.h
	gcc -c src/linalgebra.c

vector.o: src/vector.c src/vector.h
	gcc -c src/vector.c

test: test/test-vector.o
	gcc -o test/test-vector.c

test-vector.o: test-vector.c
	gcc -c test/test-vector.c

clean:
	rm */*.o linalgebra test
