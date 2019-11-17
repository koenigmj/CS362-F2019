#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define RANDOMTEST "minion"

int cardEffect(int minion, int choice1, int choice2, int choice3, struct gameState* testG, int handpos, int* bonus);

int main()
{
//int card = minion;
int choice1 = 0;
int choice2 = 0;
int choice3 = 0;
int handpos = 0;
int bonus = 0;
int seed = 1000;
int count = 0;


// set your card array
int k[10] = {ambassador, council_room, feast, gardens, minion, remodel, smithy, village, baron, great_hall };

// declare the game state
struct gameState G;
struct gameState testG;
//int currentPlayer = whoseTurn(&testG);
int a = G.numActions;
int c = G.coins;

// declare the arrays
srand(time(0));
printf("Begin Testing minionCardEffect:\n");
 
// set the state of your variables
memset(&G, 23, sizeof(struct gameState)); // set the game state
initializeGame(2, k, seed, &G); // initialize a new game

//--------------------TEST 1: Test choice1 and choce2 are in bounds---------

while (count < 1000)
{
//call the refactored function
memcpy(&testG, &G, sizeof(struct gameState));
count++;
choice1 = (rand () % 26);
choice2 = (rand () % 26); 		
cardEffect(minion, choice1, choice2, choice3, &testG, handpos, &bonus);

	if (G.numActions > a)
		printf("Your action number is correct\n");
	else
		printf("Your action number is incorrect\n");
}

//----------------TEST 2: Test that new card costs within 3 of old card--------
//copy the game state

while (count < 1000)
{
memcpy(&testG, &G, sizeof(struct gameState));
count++;
choice1 = (rand () % 26);
// call the refactored function again
cardEffect(minion, choice1, choice2, choice3, &testG, handpos, &bonus);
if ((choice1 >= 0)  && (G.coins == c + 2))
	printf("Choice1 and Choice2 were inverted \n");
else
	printf("You passed the coin test\n");
}
	
//--------------TEST 3: Test that current player hand is correct size-----
//copy the game state
memcpy(&testG, &G, sizeof(struct gameState));
for (int i = 0; i < testG.numPlayers; i++)
	{
	// call the refactored function again
	cardEffect(minion, choice1, choice2, choice3, &testG, handpos, &bonus);
	if (testG.handCount[i] == 5)
		printf("You have the correct number of cards in your hand\n");
	else
		printf("Your card count is off\n");
	}


printf("Test completed!\n");
return 0;
}

