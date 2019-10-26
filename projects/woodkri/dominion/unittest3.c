//
// Created by krist on 10/23/2019.
// Ambassador
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

    //Find bug 1 by choosing to discard 2 of a card the player has 1 of
    G.hand[p][0] = ambassador;
    G.hand[p][1] = copper;
    G.hand[p][2] = estate;
    G.handCount[p] = 3;
    G.hand[1][0] = copper;
    G.hand[1][1] = copper;
    G.handCount[1] = 2;
    int supplyCount = G.supplyCount[copper];
    printf("Calling cardEffectAmbassador with choice to discard 2 cards when player has 1\n");
    int result = cardEffectAmbassador(1, 2, &G, 0, p);
    result = assert(result == -1);
    if (!result) {
        printf("FAIL - Function exited with wrong exit code.\n");
    }
    else {
        printf("PASS - Function exited with correct exit code.\n");
    }
    result = assert(supplyCount == G.supplyCount[copper]);
    if (!result) {
        printf("FAIL - Supply count of card to discard changed.\n");
    }
    else {
        printf("PASS - Supply count of card to discard did not change.\n");
    }
    result = assert(G.hand[p][0] == ambassador && G.hand[p][1] == copper && G.hand[p][2] == estate);
    if (!result) {
        printf("FAIL - Player's hand changed.\n");
    }
    else {
        printf("PASS - Player's hand did not change.\n");
    }
    result = assert(G.hand[1][0] == copper && G.hand[1][1] == copper);
    if (!result) {
        printf("FAIL - Opponent's hand changed.\n");
    }
    else {
        printf("PASS - Opponent's hand did not change.\n");
    }

    //Find bug 2 by comparing the number of cards of the discard type the player had before the turn and subtracting
    // the number they chose to discard
    G.hand[p][0] = ambassador;
    G.hand[p][1] = copper;
    G.hand[p][2] = estate;
    G.hand[p][3] = copper;
    G.hand[p][4] = copper;
    G.handCount[p] = 5;
    G.hand[1][0] = copper;
    G.hand[1][1] = copper;
    G.handCount[1] = 2;
    supplyCount = G.supplyCount[copper];
    printf("\nCalling cardEffectAmbassador with choice to discard 2 cards when player has at least 2\n");
    cardEffectAmbassador(1, 2, &G, 0, p);

    //Supply count should increase by 2 with discard, then decrease by 1 with opponent card gain
    result = assert(supplyCount+1 == G.supplyCount[copper]);
    if (!result) {
        printf("FAIL - Supply count of card to discard not incremented by 1.\n");
    }
    else {
        printf("PASS - Supply count of card incremented by 1.\n");
    }
    result = assert(G.hand[p][0] == estate && G.hand[p][1] == copper && G.handCount[p] == 2);
    if (!result) {
        printf("FAIL - Estate and 1 copper card are not the only ones left.\n");
    }
    else {
        printf("PASS - Estate and 1 copper card are the only ones left.\n");
    }
    result = assert(G.hand[1][2] == copper);
    if (!result) {
        printf("FAIL - Opponent did not gain copper.\n");
    }
    else {
        printf("PASS - Opponent gained copper.\n");
    }

    //Call with choice to discard 1 card that the player has.
    G.hand[p][0] = ambassador;
    G.hand[p][1] = copper;
    G.hand[p][2] = estate;
    G.hand[p][3] = copper;
    G.hand[p][4] = copper;
    G.handCount[p] = 5;
    G.hand[1][0] = copper;
    G.hand[1][1] = copper;
    G.handCount[1] = 2;
    supplyCount = G.supplyCount[copper];
    printf("\nCalling cardEffectAmbassador with choice to discard 1 card that the player has\n");
    cardEffectAmbassador(1, 1, &G, 0, p);

    //Supply count should increase by 1 with discard, then decrease by 1 with opponent card gain
    result = assert(supplyCount == G.supplyCount[copper]);
    if (!result) {
        printf("FAIL - Supply count of card to discard incorrect.\n");
    }
    else {
        printf("PASS - Supply count of card to discard correct.\n");
    }
    result = assert(G.handCount[p] == 3);
    if (!result) {
        printf("FAIL - Number of cards in hand is incorrect.\n");
    }
    else {
        printf("PASS - Number of cards in hand is correct.\n");
    }
    result = assert(G.hand[1][2] == copper);
    if (!result) {
        printf("FAIL - Opponent did not gain copper.\n");
    }
    else {
        printf("PASS - Opponent gained copper.\n");
    }
}
