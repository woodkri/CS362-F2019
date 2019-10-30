/*
 * Author: Kristin Wood
 * Description: Unit test for cardEffectMinion function
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

    //Call with choice to gain coins
    G.hand[p][0] = minion;
    G.handCount[p] = 1;
    G.hand[1][0] = copper;
    G.handCount[1] = 1;
    int actions = G.numActions;
    int coins = G.coins;
    //Capture number of cards beforehand
    int myDiscardCount = G.discardCount[p];
    int opponentDiscardCount = G.discardCount[1];
    int myHandCount = G.handCount[p];
    int opponentHandCount = G.handCount[1];
    printf("Calling cardEffectMinion with choice to gain coins\n");
    cardEffectMinion(1, 0, &G, 0, 0);

    int result = assert(G.numActions == actions+1);
    if (!result) {
        printf("FAIL - Player did not gain an action.\n");
    }
    else {
        printf("PASS - Player gained an action.\n");
    }
    //Find bug 2
    result = assert(G.coins == coins+2);
    if (!result) {
        printf("FAIL - Player did not gain 2 coins.\n");
    }
    else {
        printf("PASS - Player gained two coins.\n");
    }
    //Only played card should be discarded
    result = assert(G.discardCount[p] == myDiscardCount+1);
    if (!result) {
        printf("FAIL - More or less than one card was discarded.\n");
    }
    else {
        printf("PASS - Only one card was discarded.\n");
    }
    result = assert(G.handCount[p] == myHandCount-1);
    if (!result) {
        printf("FAIL - Hand count was not decremented by one.\n");
    }
    else {
        printf("PASS - Hand count was decremented by one.\n");
    }
    result = assert(G.handCount[1] == opponentHandCount);
    if (!result) {
        printf("FAIL - Opponent's hand count changed.\n");
    }
    else {
        printf("PASS - Opponent's hand count did not change.\n");
    }
    result = assert(G.discardCount[1] == opponentDiscardCount);
    if (!result) {
        printf("FAIL - Opponent's discard count changed.\n");
    }
    else {
        printf("PASS - Opponent's discard count did not change.\n");
    }

    //Call with choice to discard and draw, other player has 5 cards
    G.hand[p][0] = minion;
    actions = G.numActions;
    coins = G.coins;
    G.hand[1][0] = copper;
    G.hand[1][1] = copper;
    G.hand[1][2] = copper;
    G.hand[1][3] = copper;
    G.hand[1][4] = copper;
    G.handCount[1] = 5;
    //Capture number of cards beforehand
    myDiscardCount = G.discardCount[p];
    opponentDiscardCount = G.discardCount[1];
    myHandCount = G.handCount[p];
    opponentHandCount = G.handCount[1];
    printf("\nCalling cardEffectMinion with choice to discard and draw while the opponent has 5 cards\n");
    cardEffectMinion(0, 1, &G, 0, 0);

    result = assert(G.numActions == actions+1);
    if (!result) {
        printf("FAIL - Player did not gain an action.\n");
    }
    else {
        printf("PASS - Player gained an action.\n");
    }
    //Find bug 2
    result = assert(G.coins == coins);
    if (!result) {
        printf("FAIL - Player's coins changed.\n");
    }
    else {
        printf("PASS - Player's coins did not change.\n");
    }

    result = assert(G.discardCount[p] == myDiscardCount + myHandCount);
    if (!result) {
        printf("FAIL - Player 0's discard count does not include previous hand.\n");
    }
    else {
        printf("PASS - Player 0's discard count includes previous hand.\n");
    }
    result = assert(G.handCount[p] == 4);
    if (!result) {
        printf("FAIL - Player 0 does not have 4 cards in their hand.\n");
    }
    else {
        printf("PASS - Player 0 has 4 cards in their hand.\n");
    }
    result = assert(G.discardCount[1] == opponentDiscardCount + opponentHandCount);
    if (!result) {
        printf("FAIL - Player 1's discard count does not include previous hand.\n");
    }
    else {
        printf("PASS - Player 1's discard count includes previous hand.\n");
    }
    result = assert(G.handCount[1] == 4);
    if (!result) {
        printf("FAIL - Player 1 does not have 4 cards in their hand.\n");
    }
    else {
        printf("PASS - Player 1 has 4 cards in their hand.\n");
    }

    //Call with choice to discard and draw, other player has 2 cards
    G.hand[p][0] = minion;
    actions = G.numActions;
    coins = G.coins;
    G.hand[1][0] = copper;
    G.hand[1][1] = copper;
    G.handCount[1] = 2;
    //Capture number of cards beforehand
    myDiscardCount = G.discardCount[p];
    opponentDiscardCount = G.discardCount[1];
    myHandCount = G.handCount[p];
    opponentHandCount = G.handCount[1];
    printf("\nCalling cardEffectMinion with choice to discard and draw while the opponent has 2 cards\n");
    cardEffectMinion(0, 1, &G, 0, 0);

    result = assert(G.numActions == actions+1);
    if (!result) {
        printf("FAIL - Player did not gain an action.\n");
    }
    else {
        printf("PASS - Player gained an action.\n");
    }
    //Find bug 2
    result = assert(G.coins == coins);
    if (!result) {
        printf("FAIL - Player's coins changed.\n");
    }
    else {
        printf("PASS - Player's coins did not change.\n");
    }
    result = assert(G.discardCount[p] == myDiscardCount + myHandCount);
    if (!result) {
        printf("FAIL - Player 0's discard count does not include previous hand.\n");
    }
    else {
        printf("PASS - Player 0's discard count includes previous hand.\n");
    }
    result = assert(G.handCount[p] == 4);
    if (!result) {
        printf("FAIL - Player 0 does not have 4 cards in their hand.\n");
    }
    else {
        printf("PASS - Player 0 has 4 cards in their hand.\n");
    }
    result = assert(G.discardCount[1] == opponentDiscardCount);
    if (!result) {
        printf("FAIL - Player 1's discard count changed.\n");
    }
    else {
        printf("PASS - Player 1's discard count did not change.\n");
    }
    result = assert(G.handCount[1] == opponentHandCount);
    if (!result) {
        printf("FAIL - Player 1's hand count changed.\n\n");
    }
    else {
        printf("PASS - Player 1's hand count did not change.\n\n");
    }
}
