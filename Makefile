all: linalgebra test-vector

linalgebra: src/linalgebra.o src/vector.o
	gcc src/linalgebra.c src/vector.c -fsanitize=address,undefined -o linalgebra

linalgebra.o: src/linalgebra.c src/linalgebra.h
	gcc src/linalgebra.c -fsanitize=address,undefined -c

vector.o: src/vector.c src/vector.h
	gcc src/vector.c -fsanitize=address,undefined -c

test-vector: test/test-vector.o
	gcc test/test-vector.c -fsanitize=address,undefined -o test-vector

test-vector.o: test-vector.c
	gcc test/test-vector.c -fsanitize=address,undefined -c

clean:
	rm -f */*.o linalgebra test-vector
