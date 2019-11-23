#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define UNITTEST "tribute"

//int cardEffect(int tribute, int choice1, int choice2, int choice3, struct gameState* testG, int handpos, int* bonus);

int playTribute(int currentPlayer, int nextPlayer, struct gameState* state);

int main()
{
	//int choice1 = 0;
	//int choice2 = 0;
	//int choice3 = 0;
	//int handpos = 0;
	//int bonus = 0;
	int seed = 1000;

	// set your card array
	int k[10] = { ambassador, council_room, feast, gardens, mine, minion, smithy, village, tribute, great_hall };
	
	// declare the game state

	struct gameState G;
	struct gameState testG;
	int currentPlayer = whoseTurn(&testG);
	int nextPlayer = currentPlayer + 1;
	int deckC = testG.deckCount[nextPlayer];
	int discardC = testG.discardCount[nextPlayer];
	int c = testG.coins;
	int count1 = 0;
	// declare the arrays

	srand(time(0));
 	printf("Begin Testing tributeCardEffect:\n");
	// set the state of your variables
	memset(&G, 23, sizeof(struct gameState)); // set the game state
	initializeGame(2, k, seed, &G); // initialize a new game

	//--------------------TEST 1: Check whether deck/discardCounts are correct_---------
	memcpy(&testG, &G, sizeof(struct gameState));

	// call the refactored function
	while (count1 < 100)
	{
	count1++;
	currentPlayer = (rand () % 2);
	//cardEffect(tribute, choice1, choice2, choice3, &testG, handpos, &bonus);
	playTribute(currentPlayer, nextPlayer, &testG);
	if (testG.deckCount[nextPlayer] + testG.discardCount[nextPlayer] <= 1)
		{
		if (testG.deckCount[nextPlayer] > 0)
			{
			if (testG.deckCount[nextPlayer] < deckC)
				printf ("Your deck count is correct\n");
			else
				printf ("Your deck count is INcorrect\n");
			}
		else if (testG.discardCount[nextPlayer] > 0)
			{
			if (testG.discardCount[nextPlayer] < discardC)
				printf ("Your discard count is correct\n");
			else
				printf ("Your discard count is INcorrect\n");
			}
		else
			printf("No count to check\n");
		}
	else
		printf("The counts were over 1\n");
	}
//----------------TEST 2: Check whether deckCount and discardCount decremented/incremented correctly--------
	memcpy(&testG, &G, sizeof(struct gameState));
	
	// call the refactored function again

	//cardEffect(tribute, choice1, choice2, choice3, &testG, handpos, &bonus);
	playTribute(currentPlayer, nextPlayer, &testG);

	if (testG.deckCount[nextPlayer] == 0)
		{
		if (deckC ==  testG.deckCount[nextPlayer])
			printf("Nothing incremented....FAILURE\n");
		if (discardC == testG.discardCount[nextPlayer])
                	printf("Nothing decremented....FAILURE\n");
		}
	else
		{
		if (deckC == testG.deckCount[nextPlayer])
			printf("You did NOT decrement your deck Count\n");
		}

//--------------TEST 3: Check coin value is correct--------------- 
	memcpy(&testG, &G, sizeof(struct gameState));
	
	// call the refactored function again
	//cardEffect(tribute, choice1, choice2, choice3, &testG, handpos, &bonus);
	playTribute(currentPlayer, nextPlayer, &testG);

	if (testG.coins == c+2)
		printf("Your coin count is correct\n");
	else
		printf("Your coin count is INcorrect\n");

	printf("Test completed!\n");
	return 0;
}
