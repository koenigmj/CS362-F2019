#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define UNITTEST "baron"

int cardEffect(int baron, int choice1, int choice2, int choice3, struct gameState* testG, int handpos, int* bonus); 	

int main()
{
	//int card = baron;
	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;
	int handpos = 0;
	int bonus = 0;
	int seed = 1000;
	int p = 0;
//	int card_not_discarded = 1;

	// set your card array
	int k[10] = { ambassador, council_room, feast, gardens, mine, minion, smithy, village, baron, great_hall };

	// declare the game state
	struct gameState G;
	struct gameState testG;
	int currentPlayer = whoseTurn(&testG);
	int n = testG.numBuys;
	int s = testG.supplyCount[estate];
	int c = testG.coins;
	int cP = testG.handCount[currentPlayer];	
	// declare the arrays
	//int coppers[MAX_HAND];
	//int silvers[MAX_HAND];
	//int golds[MAX_HAND];

	printf("Begin Testing baronCardEffect:\n");

	// set the state of your variables
	memset(&G, 23, sizeof(struct gameState)); // set the game state
	initializeGame(2, k, seed, &G); // initialize a new game

	//--------------------TEST 1: Test whether numBuys is correct---------
	memcpy(&testG, &G, sizeof(struct gameState));

	// call the refactored function
	cardEffect(baron, choice1, choice2, choice3, &testG, handpos, &bonus);
	if (n < testG.numBuys)
		printf("Your numBuys is correct\n");
	else
		printf("Your numBuys is INcorrect\n");

	//----------------TEST 2: Test whether supplyCount is correct-------
	memcpy(&testG, &G, sizeof(struct gameState));

	// call the refactored function again
	cardEffect(baron, choice1, choice2, choice3, &testG, handpos, &bonus);

	if (choice1 < 1)
		{
		if (testG.supplyCount[estate] <= s)
			printf ("The supply count for estates is correct\n");
		else
			printf ("The supply count for estates is INcorrect\n");
		}

	//--------------TEST 3: Test major conditions of card_not_discarded while loop-------
	memcpy(&testG, &G, sizeof(struct gameState));

	// call the refactored function again
	choice1 = 1;
	cardEffect(baron, choice1, choice2, choice3, &testG, handpos, &bonus);
	int p2 = p;
	int card_not_discarded = 1;
 
	//printf("choice1:%d\n",choice1);
	if (choice1 > 0)
		{
		if (card_not_discarded > 0)
			{
			if (testG.hand[currentPlayer][1] == estate)
				{
				if (testG.coins > c)
					printf("You found an estate card\n");
				if (testG.coins >= c)
					printf("You did not find the estate card you were supposed to\n");
				if (testG.handCount[currentPlayer] < cP)
					printf("Your hand count is correct\n");
				if (testG.handCount[currentPlayer] >= cP)
					printf("Your hand count is INcorrect\n");  
				}
			else if (p > testG.handCount[currentPlayer])
				{
				if(testG.supplyCount[estate] < s)
					printf("You took an estate card from the supply\n");
				else	
                                	printf("You DID NOT take an estate card from the supply you were supposed to\n");
				}
			else
				{
				if(p > p2)
					printf("p was incremented\n");
				else
					printf("p was NOT incremented\n");
				}
			}
		}

	printf("Test completed!\n");
	return 0;
}
