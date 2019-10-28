//
// Created by krist on 10/23/2019.
// Tribute
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
    int o = 1;

    //Declare arrays of cards
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

    //Initialize game
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);

    //Call with 2 treasures
    G.deck[o][0] = silver;
    G.deck[o][1] = gold;
    G.deckCount[o] = 2;
    G.hand[p][0] = tribute;
    int tributeRevealedCards[2] = {-1, -1};
    int actions = G.numActions;
    int coins = G.coins;
    int cards = G.handCount[p] + G.discardCount[p] + G.deckCount[p];
    printf("Calling cardEffectTribute with 2 treasure cards\n");
    cardEffectTribute(&G, 0, 1, tributeRevealedCards);
    int result = assert(G.coins == coins+4);
    if (!result) {
        printf("FAIL - Coins did not increase by 4.\n");
    }
    else {
        printf("PASS - Coins increased by 4.\n");
    }
    result = assert(G.numActions == actions);
    if (!result) {
        printf("FAIL - Number of actions changed.\n");
    }
    else {
        printf("PASS - Number of actions did not change.\n");
    }
    result = assert(cards == G.handCount[p] + G.discardCount[p] + G.deckCount[p]);
    if (!result) {
        printf("FAIL - Number of cards changed.\n");
    }
    else {
        printf("PASS - Number of cards did not change.\n");
    }

    //Call with 2 actions
    G.deck[o][0] = baron;
    G.deck[o][1] = mine;
    G.deckCount[o] = 2;
    G.hand[p][0] = tribute;
    actions = G.numActions;
    coins = G.coins;
    cards = G.handCount[p] + G.discardCount[p] + G.deckCount[p];
    printf("\nCalling cardEffectTribute with 2 action cards\n");
    cardEffectTribute(&G, 0, 1, tributeRevealedCards);
    result = assert(G.coins == coins);
    if (!result) {
        printf("FAIL - Number of coins changed.\n");
    }
    else {
        printf("PASS - Number of coins did not change.\n");
    }
    result = assert(G.numActions == actions+4);
    if (!result) {
        printf("FAIL - Number of actions did not increase by 4.\n");
    }
    else {
        printf("PASS - Number of actions increased by 4.\n");
    }
    result = assert(cards == G.handCount[p] + G.discardCount[p] + G.deckCount[p]);
    if (!result) {
        printf("FAIL - Number of cards changed.\n");
    }
    else {
        printf("PASS - Number of cards did not change.\n");
    }

    //Call with 2 victories
    G.deck[o][0] = estate;
    G.deck[o][1] = province;
    G.deckCount[o] = 2;
    G.hand[p][0] = tribute;
    actions = G.numActions;
    coins = G.coins;
    cards = G.handCount[p] + G.discardCount[p] + G.deckCount[p];
    printf("\nCalling cardEffectTribute with 2 victory cards\n");
    cardEffectTribute(&G, 0, 1, tributeRevealedCards);
    result = assert(G.coins == coins);
    if (!result) {
        printf("FAIL - Number of coins changed.\n");
    }
    else {
        printf("PASS - Number of coins did not change.\n");
    }
    result = assert(G.numActions == actions);
    if (!result) {
        printf("FAIL - Number of actions changed.\n");
    }
    else {
        printf("PASS - Number of actions did not change.\n");
    }
    result = assert(cards == G.handCount[p] + G.discardCount[p] + G.deckCount[p] + 4);
    if (!result) {
        printf("FAIL - Number of cards did not increase by 4.\n");
    }
    else {
        printf("PASS - Number of cards increased by 4.\n");
    }

    //Call with 2 of the same
    G.deck[o][0] = baron;
    G.deck[o][1] = baron;
    G.deckCount[o] = 2;
    G.hand[p][0] = tribute;
    actions = G.numActions;
    coins = G.coins;
    cards = G.handCount[p] + G.discardCount[p] + G.deckCount[p];
    printf("\nCalling cardEffectTribute with 2 of the same action cards\n");
    cardEffectTribute(&G, 0, 1, tributeRevealedCards);
    result = assert(G.coins == coins);
    if (!result) {
        printf("FAIL - Number of coins changed.\n");
    }
    else {
        printf("PASS - Number of coins did not change.\n");
    }
    result = assert(G.numActions == actions+2);
    if (!result) {
        printf("FAIL - Number of actions did not increase by 2.\n");
    }
    else {
        printf("PASS - Number of actions increased by 2.\n");
    }
    result = assert(cards == G.handCount[p] + G.discardCount[p] + G.deckCount[p]);
    if (!result) {
        printf("FAIL - Number of cards changed.\n");
    }
    else {
        printf("PASS - Number of cards did not change.\n");
    }

    //Call with 0 deck, 1 discard
    G.deckCount[o] = 0;
    G.discardCount[o] = 1;
    G.discard[o][0] = curse;
    G.hand[p][0] = tribute;
    actions = G.numActions;
    coins = G.coins;
    cards = G.handCount[p] + G.discardCount[p] + G.deckCount[p];
    printf("\nCalling cardEffectTribute with no cards in the deck but 1 curse in discard\n");
    cardEffectTribute(&G, 0, 1, tributeRevealedCards);
    result = assert(G.coins == coins);
    if (!result) {
        printf("FAIL - Number of coins changed.\n");
    }
    else {
        printf("PASS - Number of coins did not change.\n");
    }
    result = assert(G.numActions == actions);
    if (!result) {
        printf("FAIL - Number of actions changed.\n");
    }
    else {
        printf("PASS - Number of actions did not change.\n");
    }
    result = assert(cards == G.handCount[p] + G.discardCount[p] + G.deckCount[p]);
    if (!result) {
        printf("FAIL - Number of cards changed.\n");
    }
    else {
        printf("PASS - Number of cards did not change.\n");
    }

    //Call with 0 deck, 2 discard
    G.deckCount[o] = 0;
    G.discardCount[o] = 2;
    G.discard[o][0] = curse;
    G.discard[o][1] = silver;
    G.hand[p][0] = tribute;
    actions = G.numActions;
    coins = G.coins;
    cards = G.handCount[p] + G.discardCount[p] + G.deckCount[p];
    printf("\nCalling cardEffectTribute with no cards in the deck but 1 curse and 1 treasure in discard\n");
    cardEffectTribute(&G, 0, 1, tributeRevealedCards);
    result = assert(G.coins == coins+2);
    if (!result) {
        printf("FAIL - Number of coins did not increase by 2.\n");
    }
    else {
        printf("PASS - Number of coins increased by 2.\n");
    }
    result = assert(G.numActions == actions);
    if (!result) {
        printf("FAIL - Number of actions changed.\n");
    }
    else {
        printf("PASS - Number of actions did not change.\n");
    }
    result = assert(cards == G.handCount[p] + G.discardCount[p] + G.deckCount[p]);
    if (!result) {
        printf("FAIL - Number of cards changed.\n");
    }
    else {
        printf("PASS - Number of cards did not change.\n");
    }

    //Call with 0 deck, 0 discard
    G.deckCount[o] = 0;
    G.discardCount[o] = 0;
    G.hand[p][0] = tribute;
    actions = G.numActions;
    coins = G.coins;
    cards = G.handCount[p] + G.discardCount[p] + G.deckCount[p];
    printf("\nCalling cardEffectTribute with no cards in the deck or discard\n");
    cardEffectTribute(&G, 0, 1, tributeRevealedCards);
    result = assert(G.coins == coins);
    if (!result) {
        printf("FAIL - Number of coins changed.\n");
    }
    else {
        printf("PASS - Number of coins did not change.\n");
    }
    result = assert(G.numActions == actions);
    if (!result) {
        printf("FAIL - Number of actions changed.\n");
    }
    else {
        printf("PASS - Number of actions did not change.\n");
    }
    result = assert(cards == G.handCount[p] + G.discardCount[p] + G.deckCount[p]);
    if (!result) {
        printf("FAIL - Number of cards changed.\n");
    }
    else {
        printf("PASS - Number of cards did not change.\n");
    }
}
