/*
 * Author: Kristin Wood
 * Description: Randomized Unit test for cardEffectTribute function
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

void checkTribute(int p, int nextPlayer, struct gameState* G, int* tributeRevealedCards) {
    struct gameState pre;
    memcpy(&pre, G, sizeof(struct gameState));

    cardEffectTribute(G, p, nextPlayer, tributeRevealedCards);
    printf("Testing cardEffectTribute with %d first card, %d second card, player %d and next player %d.\n", tributeRevealedCards[0], tributeRevealedCards[1], p, nextPlayer);

    if (tributeRevealedCards[0] == tributeRevealedCards[1]) {
        tributeRevealedCards[1] = -1;
    }
    for (int i = 0; i < 2; i++) {
        if (tributeRevealedCards[i] != -1) {
            if (tributeRevealedCards[i] == copper || tributeRevealedCards[i] == silver || tributeRevealedCards[i] == gold) {
                G->coins+=2;
            }
            else if (tributeRevealedCards[i] == estate || tributeRevealedCards[i] == duchy || tributeRevealedCards[i] == province || tributeRevealedCards[i] == gardens || tributeRevealedCards[i] == great_hall) {
                memcpy(pre.hand[p], G->hand[p], sizeof(int)*G->handCount[p]);
                pre.handCount[p]+=2;
            }
            else if (tributeRevealedCards[i] != curse) {
                pre.numActions+=2;
            }
        }
    }


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

        initializeGame(numPlayers, k, seed, &G);

        int tributeRevealedCards[2] = {-1, -1};
        int nextPlayer = p+1;
        if (nextPlayer > G.numPlayers-1) {
            nextPlayer = 0;
        }
        G.deckCount[nextPlayer] = rand() % MAX_DECK;
        G.discardCount[nextPlayer] = rand() % 5;
        G.deck[nextPlayer][G.deckCount[nextPlayer]-1] = rand() % 26;
        G.deck[nextPlayer][G.deckCount[nextPlayer]-2] = rand() % 26;
        G.deck[nextPlayer][G.deckCount[nextPlayer]-3] = rand() % 26;
        G.discard[nextPlayer][G.discardCount[nextPlayer]-1] = rand() % 26;
        G.discard[nextPlayer][G.discardCount[nextPlayer]-2] = rand() % 26;
        G.discard[nextPlayer][G.discardCount[nextPlayer]-3] = rand() % 26;
        checkTribute(p, nextPlayer, &G, tributeRevealedCards);
    }
}