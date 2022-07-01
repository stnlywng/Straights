#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include <memory>
#include "card.h"

using namespace std;

class Table{
    vector<shared_ptr<Card>> clubPile;
    vector<shared_ptr<Card>> diamondPile;
    vector<shared_ptr<Card>> heartPile;
    vector<shared_ptr<Card>> spadesPile;

 public:
    vector<shared_ptr<Card>> getClubs();
    vector<shared_ptr<Card>> getDiamonds();
    vector<shared_ptr<Card>> getHearts();
    vector<shared_ptr<Card>> getSpades();

    bool isLegal(shared_ptr<Card> card);
    void clearTable();
    void addCard(shared_ptr<Card> card);
};

#endif