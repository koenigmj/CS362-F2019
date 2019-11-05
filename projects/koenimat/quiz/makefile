CFLAGS = -Wall -fpic -coverage -lm -std=c99

default: tests.out

tests.out: testme.c

        echo "Result for running random tests:" > tests.out
        gcc -o tM  testme.c $(CFLAGS)
        ./tM >> tests.out
        gcov testme.c >> tests.out

clean:
        rm tests.out

cleanall:
        rm tests.out tM  *.gcda *.gcno *.gcov

