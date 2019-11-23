#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define UNITTEST "ambassador"

//int cardEffect(int ambassador, int choice1, int choice2, int choice3, struct gameState* testG, int handpos, int* bonus);

int playAmbassador(int handPos, int currentPlayer, int cardToDiscard, int quantityToDiscard, struct gameState* state);

int main()
{
	//int card = ambassador;
	//int choice1 = 0;
	//int choice2 = 0;
	//int choice3 = 0;
	int handPos = 0;
	//int bonus = 0;
	int seed = 1000;
	int j = 0;
	int cardToDiscard = 0;
	int quantityToDiscard = 0;
	//int handCount[p] = {0,1};

	// set your card array
	int k[10] = { ambassador, council_room, feast, gardens, mine, minion, smithy, village, baron, great_hall };

	// declare the game state
	struct gameState G;
	struct gameState testG;
	int currentPlayer = whoseTurn(&testG);
	int s = testG.supplyCount[testG.hand[currentPlayer][cardToDiscard]];

	// declare the arrays
	//int coppers[MAX_HAND];
	//int silvers[MAX_HAND];
	//int golds[MAX_HAND];

	printf("Begin Testing ambassadorCardEffect:\n");

	// set the state of your variables
	memset(&G, 23, sizeof(struct gameState)); // set the game state
	initializeGame(2, k, seed, &G); // initialize a new game
									//G.handCount[p] = handCount[p]; // set any other variables

	//--------------------TEST 1: Test initial -1 return conditions---------
	memcpy(&testG, &G, sizeof(struct gameState));

	// call the refactored function
	playAmbassador(handPos, currentPlayer, cardToDiscard, quantityToDiscard, &testG); 
	//cardEffect(ambassador, 1, choice2, choice3, &testG, handpos, &bonus);
	if (quantityToDiscard > 2 || quantityToDiscard < 0 || cardToDiscard == handPos || j < quantityToDiscard)
		printf("Your turn is ending\n");	


	//----------------TEST 2: Test supply count of chosen discard card--------
	memcpy(&testG, &G, sizeof(struct gameState));

	// call the refactored function again
	playAmbassador(handPos, currentPlayer, cardToDiscard, quantityToDiscard, &testG); 
	//cardEffect(ambassador, choice1, choice2, choice3, &testG, handpos, &bonus);

	if (s == s + quantityToDiscard)
		printf("Your supply count is correct\n");
	else
		printf("Your supply count is NOT correct\n"); 
	

	printf("Test completed!\n");
	return 0;
}

