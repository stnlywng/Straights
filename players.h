#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "table.h"
#include "card.h"

using namespace std;

class Player{
    vector<shared_ptr<Card>> hand;
    vector<shared_ptr<Card>> discarded;

    bool isBot;
    bool hasLegalCard;

    void botTurn();
    void humanPlayerTurn();

    void printCards(char suit);
    void processInput();
    char getCharFromString(string s);
    bool checkHandForCardAndRemove(char suit, int value, bool toTable);

    int translateCardToNum(string s);
    string translateNumToCard(int n);

 public:
    int id;

    void yourTurn();
    void addToHand(shared_ptr<Card> newCard);
    int countAndDiscardTrashPile();

    Player(bool isBot, int id);
};

#endif