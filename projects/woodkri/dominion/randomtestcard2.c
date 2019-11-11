/*
 * Author: Kristin Wood
 * Description: Randomized Unit test for cardEffectMinion function
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

void checkMinion(int p, int choice1, int choice2, int handPos, struct gameState* G, int numPlayers) {
    struct gameState pre;
    memcpy(&pre, G, sizeof(struct gameState));

    printf("Testing cardEffectMinion with %d choice1, %d choice2, %d handPos, player %d.\n", choice1, choice2, handPos, p);

    cardEffectMinion(choice1, choice2, G, handPos, p);

    if (choice1) {
        pre.coins+=2;
    }
    else if (choice2) {
        for (int i = 0; i < numPlayers; i++) {
            if (i == p || pre.handCount[i] > 5) {
                memcpy(pre.discard[i], G->discard[i], sizeof(int)*pre.handCount[i]);
                pre.discardCount[i] += pre.handCount[i];
                memcpy(pre.hand[i], G->hand[i], sizeof(int) * 4);
                pre.handCount[i] = 4;
            }
        }
    }
    pre.numActions++;

    int r = assert(pre.coins == G->coins);
    if (r == 0) {
        printf("Coins are not the same\n");
    }
    r = assert(pre.numActions == G->numActions);
    if (r==0) {
        printf("NumActions are not the same.\n");
    }
    r = assert(pre.handCount[p] == G->handCount[p]);
    if (r==0) {
        printf("Hand count is not the same.\n");
    }
    r = assert(pre.discardCount[p] == G->discardCount[p]);
    if (r==0) {
        printf("Discard count is not the same.\n");
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
        int choice1 = rand() % 2;
        int choice2;
        if (choice1 == 1) {
            choice2 = 0;
        }
        else {
            choice2 = 1;
        }
        initializeGame(numPlayers, k, seed, &G);
        int handPos;
        if (G.handCount[p] != 0) {
            if (G.handCount[p] >= 5) {
                G.handCount[p]--;
            }
            handPos = rand() % G.handCount[p];
            G.hand[p][handPos] = minion;
        }
        else {
            //When handcount is 0, often causes a seg fault
            continue;
        }
        checkMinion(p, choice1, choice2, handPos, &G, numPlayers);
    }
}