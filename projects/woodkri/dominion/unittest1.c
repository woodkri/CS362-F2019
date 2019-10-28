/*
 * Author: Kristin Wood
 * Description: Unit test for cardEffectBaron function
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <time.h>
#include <stdio.h>

int main (int argc, char** argv) {
    //Set up game state
    struct gameState G;
    int seed = time(NULL);
    int numPlayers = 2;
    int p = 0;

    //Declare arrays of cards
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

    //Initialize game
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);

    //Find bug 1 by setting first card to estate
    G.hand[p][0] = estate;

    //Find bug 2 by capturing changes in numBuys
    int buys = G.numBuys;
    int coins = G.coins;

    printf("Calling cardEffectBaron with choice 1\n");
    //Call cardEffectBaron with choice to discard estate for player 0
    cardEffectBaron(1, &G, 0);
    //With discard of card, should get 4 more coins
    int result = assert(G.coins == coins+4);
    if (!result) {
        printf("FAIL - Player did not gain 4 coins.\n");
    }
    else {
        printf("PASS - Player gained 4 coins.\n");
    }
    result = assert(G.hand[p][0] != estate);
    if (!result) {
        printf("FAIL - Player did not discard estate card.\n");
    }
    else {
        printf("PASS - Player discarded estate card.\n");
    }
    result = assert(G.numBuys == buys+1);
    if (!result) {
        printf("FAIL - Player did not get an additional buy.\n");
    }
    else {
        printf("PASS - Player got an additional buy.\n");
    }

    buys = G.numBuys;
    coins = G.coins;
    int numEstates = 0;
    for (int i = 0; i < G.handCount[p]; i++) {
        if (G.hand[p][i] == estate) {
            numEstates++;
        }
    }
    for (int i = 0; i < G.deckCount[p]; i++) {
        if (G.deck[p][i] == estate) {
            numEstates++;
        }
    }
    for (int i = 0; i < G.discardCount[p]; i++) {
        if (G.discard[p][i] == estate) {
            numEstates++;
        }
    }

    printf("\nCalling cardEffectBaron with choice 0\n");
    //Call cardEffectBaron with choice to gain an estate
    cardEffectBaron(0, &G, 0);
    result = assert(G.coins == coins);
    if (!result) {
        printf("FAIL - Player's coins changed.\n");
    }
    else {
        printf("PASS - Player's coins did not change'.\n");
    }
    result = assert(G.numBuys == buys+1);
    if (!result) {
        printf("FAIL - Player did not get an additional buy.\n");
    }
    else {
        printf("PASS - Player got an additional buy.\n");
    }
    int numEstatesAfter = 0;
    for (int i = 0; i < G.handCount[p]; i++) {
        if (G.hand[p][i] == estate) {
            numEstatesAfter++;
        }
    }
    for (int i = 0; i < G.deckCount[p]; i++) {
        if (G.deck[p][i] == estate) {
            numEstatesAfter++;
        }
    }
    for (int i = 0; i < G.discardCount[p]; i++) {
        if (G.discard[p][i] == estate) {
            numEstatesAfter++;
        }
    }
    result = assert(numEstatesAfter == numEstates+1);
    if (!result) {
        printf("FAIL - Player did not gain an estate card.\n");
    }
    else {
        printf("PASS - Player gained an estate card.\n");
    }

    //Test the case where player chooses to discard an estate but doesn't have one.
    printf("\nCalling cardEffectBaron with choice 1 but no estate cards\n");
    for (int i = 0; i < G.handCount[p]; i++) {
        if (G.hand[p][i] == estate) {
            G.hand[p][i] = copper;
        }
    }
    buys = G.numBuys;
    coins = G.coins;
    for (int i = 0; i < G.deckCount[p]; i++) {
        if (G.deck[p][i] == estate) {
            numEstates++;
        }
    }
    for (int i = 0; i < G.discardCount[p]; i++) {
        if (G.discard[p][i] == estate) {
            numEstates++;
        }
    }

    cardEffectBaron(1, &G, 0);

    result = assert(G.coins == coins);
    if (!result) {
        printf("FAIL - Player's coins changed.\n");
    }
    else {
        printf("PASS - Player's coins did not change'.\n");
    }
    result = assert(G.numBuys == buys+1);
    if (!result) {
        printf("FAIL - Player did not get an additional buy.\n");
    }
    else {
        printf("PASS - Player got an additional buy.\n");
    }
    numEstatesAfter = 0;
    for (int i = 0; i < G.handCount[p]; i++) {
        if (G.hand[p][i] == estate) {
            numEstatesAfter++;
        }
    }
    for (int i = 0; i < G.deckCount[p]; i++) {
        if (G.deck[p][i] == estate) {
            numEstatesAfter++;
        }
    }
    for (int i = 0; i < G.discardCount[p]; i++) {
        if (G.discard[p][i] == estate) {
            numEstatesAfter++;
        }
    }
    result = assert(numEstatesAfter == numEstates+1);
    if (!result) {
        printf("FAIL - Player did not gain an estate card.\n\n");
    }
    else {
        printf("PASS - Player gained an estate card.\n\n");
    }
}
