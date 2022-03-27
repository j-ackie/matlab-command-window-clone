all: linalgebra test-vector test-matrix
	./test-vector
	./test-matrix

linalgebra: src/linalgebra.o src/matrix.o src/vector.o 
	gcc src/linalgebra.o src/matrix.o src/vector.o -fsanitize=address,undefined -pedantic-errors -lreadline -o linalgebra

linalgebra.o: src/linalgebra.c src/linalgebra.h
	gcc src/linalgebra.c -fsanitize=address,undefined -pedantic-errors -c

matrix.o: src/matrix.c src/matrix.h
	gcc src/matrix.c -fsanitize=address,undefined -pedantic-errors -c

vector.o: src/vector.c src/vector.h
	gcc src/vector.c -fsanitize=address,undefined -pedantic-errors -c

test-vector: test/test-vector.o src/vector.o
	gcc test/test-vector.o src/vector.o -fsanitize=address,undefined -pedantic-errors -o test-vector

test-vector.o: test/test-vector.c
	gcc test/test-vector.c -fsanitize=address,undefined -pedantic-errors -c

test-matrix: test/test-matrix.o src/matrix.o src/vector.o
	gcc test/test-matrix.o src/matrix.o src/vector.o -fsanitize=address,undefined -pedantic-errors -o test-matrix

test-matrix.o: test/test-matrix.c
	gcc test/test-matrix.c -fsanitize=address,undefined -pedantic-errors -c

clean:
	rm -f */*.o linalgebra test-vector test-matrix
