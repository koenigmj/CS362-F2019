#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define UNITTEST "mine"

//int cardEffect(int mine, int choice1, int choice2, int choice3, struct gameState* testG, int handpos, int* bonus);

int playMine(int currentPlayer, int handPos, int treasureCard, int desiredCard, struct gameState* state);

int main()
{
//int card = mine;
int treasureCard = 0;
int desiredCard = 0;
//int choice3 = 0;
int handPos = 0;
//int bonus = 0;
int seed = 1000;
//int ii_choice1;
int ii_choice2;

//int currentPlayer = whoseTurn(state);
//int handCount[p] = {0,1};

// set your card array
int k[10] = {ambassador, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };

// declare the game state
struct gameState G;
struct gameState testG;
int currentPlayer = whoseTurn(&testG);

// declare the arrays

printf("Begin Testing mineCardEffect:\n");

// set the state of your variables
memset(&G, 23, sizeof(struct gameState)); // set the game state
initializeGame(2, k, seed, &G); // initialize a new game

//--------------------TEST 1: Test choice1 and choce2 are in bounds---------
for (ii_choice2 = curse; ii_choice2 <= treasure_map; ii_choice2++)
	{
	//copy the game state
	memcpy(&testG, &G, sizeof(struct gameState));

	// call the refactored function
	//cardEffect(mine, choice1, ii_choice2, choice3, &testG, handpos, &bonus);
	playMine(currentPlayer, handPos, treasureCard, desiredCard, &testG);

	if (testG.hand[currentPlayer][treasureCard] <= gold && testG.hand[currentPlayer][treasureCard] >= copper)
		printf("Your choice1 is in bounds\n");
	if (testG.hand[currentPlayer][treasureCard] > gold || testG.hand[currentPlayer][treasureCard] < copper)
		printf("Your choice1 is out of bounds\n");
	if (desiredCard < 0 || desiredCard > treasure_map)
		printf("Your choice2 is out of bounds\n");
	if (desiredCard >= 0 && desiredCard < treasure_map+1)
		printf("Your choice2 is in bounds\n"); 
	}

//----------------TEST 2: Test that new card costs within 3 of old card--------
for (ii_choice2 = curse; ii_choice2 <=treasure_map; ii_choice2++)
	{
	//copy the game state
	memcpy(&testG, &G, sizeof(struct gameState));

	// call the refactored function again
	//cardEffect(mine, choice1, choice2, choice3, &testG, handpos, &bonus);
	playMine(currentPlayer, handPos, treasureCard, desiredCard, &testG);

	if (getCost(testG.hand[currentPlayer][treasureCard]) + 3 <= getCost(desiredCard))
		printf("Your new card is within an acceptable range\n");
	else
		printf("Your new card is NOT within an acceptable range\n"); 
	}

//--------------TEST 3: Test that current player hand is correct size-----
//copy the game state
memcpy(&testG, &G, sizeof(struct gameState));

// call the refactored function again
//cardEffect(mine, choice1, choice2, choice3, &testG, handpos, &bonus);
playMine(currentPlayer, handPos, treasureCard, desiredCard, &testG);

if (testG.handCount[currentPlayer] != 5)
	printf("Your hand is the wrong size\n");
else
	printf("Your hand is the correct size\n");

printf("Test completed!\n");
return 0;
}

