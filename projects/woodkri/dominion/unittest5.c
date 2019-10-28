//
// Created by krist on 10/23/2019.
// Mine
//

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

    //Trash copper (worth 0), gain village (worth 3)
    G.hand[p][0] = mine;
    G.hand[p][1] = copper;
    G.handCount[p] = 2;
    int villageCount = 0;
    for (int i = 0; i < G.discardCount[p]; i++) {
        if (G.discard[p][i] == village) {
            villageCount++;
        }
    }
    for (int i = 0; i < G.deckCount[p]; i++) {
        if (G.deck[p][i] == village) {
            villageCount++;
        }
    }
    printf("Calling cardEffectMine to trash a copper and gain a village\n");
    cardEffectMine(1, village, &G, 0, 0);
    int result = assert(G.handCount[p] == 0);
    if (!result) {
        printf("FAIL - Mine and copper were not discarded.\n");
    }
    else {
        printf("PASS - Mine and copper were discarded.\n");
    }
    int villageCountAfter = 0;
    for (int i = 0; i < G.discardCount[p]; i++) {
        if (G.discard[p][i] == village) {
            villageCountAfter++;
        }
    }
    for (int i = 0; i < G.deckCount[p]; i++) {
        if (G.deck[p][i] == village) {
            villageCountAfter++;
        }
    }
    result = assert(villageCountAfter == villageCount+1);
    if (!result) {
        printf("FAIL - Did not gain a village.\n");
    }
    else {
        printf("PASS - Gained a village.\n");
    }

    //Trash copper (worth 0), gain feast (worth 4)
    G.hand[p][0] = mine;
    G.hand[p][1] = copper;
    G.handCount[p] = 2;
    int feastCount = 0;
    for (int i = 0; i < G.discardCount[p]; i++) {
        if (G.discard[p][i] == feast) {
            feastCount++;
        }
    }
    for (int i = 0; i < G.deckCount[p]; i++) {
        if (G.deck[p][i] == feast) {
            feastCount++;
        }
    }
    printf("\nCalling cardEffectMine to trash a copper and gain a feast\n");
    cardEffectMine(1, feast, &G, 0, 0);
    result = assert(G.hand[p][0] == mine && G.hand[p][1] == copper && G.handCount[p] == 2);
    if (!result) {
        printf("FAIL - Player's hand changed.\n");
    }
    else {
        printf("PASS - Player's hand did not change.\n");
    }
    int feastCountAfter = 0;
    for (int i = 0; i < G.discardCount[p]; i++) {
        if (G.discard[p][i] == feast) {
            feastCountAfter++;
        }
    }
    for (int i = 0; i < G.deckCount[p]; i++) {
        if (G.deck[p][i] == feast) {
            feastCountAfter++;
        }
    }
    result = assert(feastCountAfter == feastCount);
    if (!result) {
        printf("FAIL - Feast count changed.\n");
    }
    else {
        printf("PASS - Feast count did not change.\n");
    }

    //Bug 2, trash a card the player has more than one of
    G.hand[p][0] = mine;
    G.hand[p][1] = copper;
    G.hand[p][2] = copper;
    G.handCount[p] = 3;
    villageCount = 0;
    for (int i = 0; i < G.discardCount[p]; i++) {
        if (G.discard[p][i] == village) {
            villageCount++;
        }
    }
    for (int i = 0; i < G.deckCount[p]; i++) {
        if (G.deck[p][i] == village) {
            villageCount++;
        }
    }
    printf("\nCalling cardEffectMine to trash a copper when the player has 2 in their hand\n");
    cardEffectMine(1, village, &G, 0, 0);
    result = assert(G.handCount[p] == 1);
    if (!result) {
        printf("FAIL - Player does not only have one card left in hand.\n");
    }
    else {
        printf("PASS - PLayer only has one card left in hand.\n");
    }
    villageCountAfter = 0;
    for (int i = 0; i < G.discardCount[p]; i++) {
        if (G.discard[p][i] == village) {
            villageCountAfter++;
        }
    }
    for (int i = 0; i < G.deckCount[p]; i++) {
        if (G.deck[p][i] == village) {
            villageCountAfter++;
        }
    }
    result = assert(villageCountAfter == villageCount+1);
    if (!result) {
        printf("FAIL - Did not gain a village.\n");
    }
    else {
        printf("PASS - Gained a village.\n");
    }

    //Trash a card that's not a treasure
    G.hand[p][0] = mine;
    G.hand[p][1] = copper;
    G.hand[p][2] = estate;
    G.handCount[p] = 3;
    villageCount = 0;
    for (int i = 0; i < G.discardCount[p]; i++) {
        if (G.discard[p][i] == village) {
            villageCount++;
        }
    }
    for (int i = 0; i < G.deckCount[p]; i++) {
        if (G.deck[p][i] == village) {
            villageCount++;
        }
    }
    printf("\nCalling cardEffectMine to trash a card that's not an estate\n");
    cardEffectMine(2, village, &G, 0, 0);
    result = assert(G.handCount[p] == 3) && G.hand[p][0] == mine && G.hand[p][1] == copper && G.hand[p][2] == estate;
    if (!result) {
        printf("FAIL - Player's hand changed.\n");
    }
    else {
        printf("PASS - Player's hand did not change.\n");
    }
    villageCountAfter = 0;
    for (int i = 0; i < G.discardCount[p]; i++) {
        if (G.discard[p][i] == village) {
            villageCountAfter++;
        }
    }
    for (int i = 0; i < G.deckCount[p]; i++) {
        if (G.deck[p][i] == village) {
            villageCountAfter++;
        }
    }
    result = assert(villageCountAfter == villageCount);
    if (!result) {
        printf("FAIL - Village count changed.\n");
    }
    else {
        printf("PASS - Village count did not change.\n");
    }
}
