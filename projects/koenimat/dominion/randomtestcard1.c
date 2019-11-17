#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define RANDOMTTEST "baron"

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
	int count = 0;	
	//int handCount[p] = {0,1};

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
	srand(time(0));
	printf("Begin Testing baronCardEffect:\n");

	// set the state of your variables
	memset(&G, 23, sizeof(struct gameState)); // set the game state
	initializeGame(2, k, seed, &G); // initialize a new game
	//G.handCount[p] = handCount[p]; // set any other variables

	//--------------------TEST 1: Test whether numBuys is correct---------
	memcpy(&testG, &G, sizeof(struct gameState));

	// call the refactored function
	cardEffect(baron, choice1, choice2, choice3, &testG, handpos, &bonus);
	if (n < testG.numBuys)
		printf("Your numBuys is correct\n");	
	else
		printf ("Your numBuys is INcorrect\n");

	//----------------TEST 2: Test wherther supplyCount is correct--------
	memcpy(&testG, &G, sizeof(struct gameState));
	while (count < 100)
	//for (choice1 = 0; choice1 < 50; choice1++)
	{
	count++;
	choice1 = (rand () % 26); 	
	// call the refactored function again
	cardEffect(baron, choice1, choice2, choice3, &testG, handpos, &bonus);
	printf("Choice1 = %d\n",choice1);
	if (choice1 < 1)
		{
		if (testG.supplyCount[estate] <= s)
			printf("The supply count for estates is correct\n");
		else
			printf("The supply count for estates is INcorrect\n"); 
		}
	}
	//--------------TEST 3: _____________----

	memcpy(&testG, &G, sizeof(struct gameState));

	// call the refactored function again
	while (count < 100)
	{
	count++;
	choice1 = (rand () % 26);
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
		else
			printf("card_not_discarded is 0\n");
		}
	else
		printf("Choice is 0\n");
	}
	printf("Test completed!\n");
	return 0;
}

