/*
 * Author: Kristin Wood
 * Description: Randomized Unit test for cardEffectBaron function
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int assert(int expression) {
    if (expression) {
        //true
        return 1;
    }
    else {
        //false
        return 0;
    }
}

void checkBaron(int player, int choice, struct gameState* G) {
    struct gameState pre;
    memcpy(&pre, G, sizeof(struct gameState));
    int numEstates = 0;
    for (int i = 0; i < pre.handCount[player]; i++) {
        if (pre.hand[player][i] == estate) {
            numEstates++;
        }
    }

    printf("Testing cardEffectBaron with %d estate(s), choice %d, player %d.\n", numEstates, choice, player);

    playBaron(G, choice, player);

    int handCount = pre.handCount[player];

    if (choice == 1) {
        if (numEstates > 0) {
            pre.coins+=4;
        }
        else {
            pre.handCount[player]++;
            pre.hand[player][handCount] = estate;
        }
    }
    else if (choice == 0) {
        pre.handCount[player]++;
        pre.hand[player][handCount] = estate;
    }
    pre.numBuys++;

    int r = assert(pre.coins == G->coins);
    if (r == 0) {
        printf("Coins are not the same\n");
    }
    r = assert(pre.numBuys == G->numBuys);
    if (r==0) {
        printf("NumBuys are not the same.\n");
    }
    r = assert(memcmp(&pre, G, sizeof(struct gameState)) == 0);
    if (r == 0) {
        printf("Test failed.\n\n");
    }
    else {
        printf("Test passed.\n\n");
    }
}

int main (int argc, char** argv) {
    //Set up game state
    struct gameState G;
    int seed = time(NULL);
    srand(seed);

    //Declare arrays of cards
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

    //Randomize struct and call function
    //Adapted from lecture slides on Randomized Testing
    for (int n = 0; n < 2000; n++) {
        for (int i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&G)[i] = rand() % 256;
        }
        int p = rand() % 2;
        //Minimum 2 players
        int numPlayers = rand() % (MAX_PLAYERS -1) + 2;
        int choice = rand() % 2;
        initializeGame(numPlayers, k, seed, &G);
        checkBaron(p, choice, &G);
    }
}