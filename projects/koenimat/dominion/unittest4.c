#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define UNITTEST "minion"

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
	//int ii_handpos = 0;
	//int ii_choice2 = 0;
	//int p;
	//int a = state->numActions; 
	//int c = state->coins;


	// set your card array
	int k[10] = { ambassador, council_room, feast, gardens, mine, minion, smithy, village, baron, great_hall };

	// declare the game state
	struct gameState G;
	struct gameState testG;
	int a = G.numActions;
	int c = G.coins;

	// declare the arrays
	//int coppers[MAX_HAND];
	//int silvers[MAX_HAND];
	//int golds[MAX_HAND];

	printf("Begin Testing minionCardEffect:\n");

	// set the state of your variables
	memset(&G, 23, sizeof(struct gameState)); // set the game state
	initializeGame(2, k, seed, &G); // initialize a new game
	

	//--------------------TEST 1: Check if action card has incremented---------
	memcpy(&testG, &G, sizeof(struct gameState));

	// call the refactored function
	cardEffect(minion, choice1, choice2, choice3, &testG, handpos, &bonus);
	
	if (G.numActions > a)
		printf("Your action number is correct\n");
	else
		printf("Your action number is incorrect\n"); 			
	
	//----------------TEST 2: Check if the coins increase by 2 if choice1 ie yes--------
	//copy the game state
	memcpy(&testG, &G, sizeof(struct gameState));
	// call the refactored function again
	cardEffect(minion, 1, choice2, choice3, &testG, handpos, &bonus);
	
	if (choice1 && (G.coins == c + 2))
		printf("Choice1 and Choice2 were inverted \n");
	else
		printf("You passed the coin test\n");
	
	//--------------TEST 3: check proper card count ----
	//copy the game state
	memcpy(&testG, &G, sizeof(struct gameState));
	for (int i = 0; i < testG.numPlayers; i++)
	{
	// call the refactored function again
	cardEffect(minion, choice1, 1, choice3, &testG, handpos, &bonus);

	if (testG.handCount[i] == 5)
		printf("You have the correct number of cards in your hand\n");
	else
		printf("Your card count is off\n");

	}

	printf("Test completed!\n");
	return 0;
}
