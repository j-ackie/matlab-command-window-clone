linalgebra: src/vector.o src/linalgebra.o test/test-linalgebra.o
	gcc src/vector.o src/linalgebra.o -o linalgebra -fsanitize=address,undefined

vector.o: src/vector.c src/vector.h
	gcc -c src/vector.c -fsanitize=address,undefined

linalgebra.o: src/linalgebra.c
	gcc -c src/linalgebra.c -fsanitize=address,undefined

test-linalgebra.o: test/test-linalgebra.c
	gcc -c test/test-linalgebra.c -fsanitize=address,undefined

clean:
	rm src/*.o linalgebra
