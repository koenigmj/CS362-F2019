CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

unittest1: unittest1.c dominion.o player
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)

unittest2: unittest2.c dominion.o player
	gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)

randomtestcard1: randomtestcard1.c dominion.o player
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o $(CFLAGS)
randomtestcard2: randomtestcard2.c dominion.o player
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o $(CFLAGS)
randomtestcard3: randomtestcard3.c dominion.o player
	gcc -o randomtestcard3 -g randomtestcard3.c dominion.o rngs.o $(CFLAGS)

testresults: unittest1 unittest2 randomtestcard1 randomtestcard2 randomtestcard3

##	echo "unittest2.c results:" >> randomtestresults.out
##	$(MAKE) --no - print - directory unittest1
	./unittest1 >> testresults.out
	./unittest2 >> testresults.out
	./randomtestcard1 >> testresults.out
	./randomtestcard2 >> testresults.out
	./randomtestcard3 >> testresults.out
	gcov dominion.c -b -f >> testresults.out
	cat dominion.c.gcov >> testresults.out

interface.o: interface.h interface.c
	gcc -c interface.c -g $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard >> testresults.out
	gcov dominion.c -b -f >> testresults.out
	cat dominion.c.gcov >> testresults.out


player: player.c interface.o
	gcc -o player player.c -g dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testresults

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe unittest1 unittest2 randomtestcard1 randomtestcard2 randomtestcard3


