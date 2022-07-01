#ifndef _GAMEMANAGER_H

#define _GAMEMANAGER_H

#include "players.h"
#include "table.h"
#include "card.h"

#include <random>
#include <memory>

using namespace std;

class GameManager{
    static shared_ptr<GameManager> instance;

    vector<shared_ptr<Player>> players;
    vector<shared_ptr<Card>> originalDeck;
    vector<shared_ptr<Card>> shuffledDeck;

    int points[4] = {0};
    int curPlayer;
    int curPlayerWithSevenSpades;

    void playerGo();
    void distributeCards();
    void newRound(default_random_engine rng);

    public:
    static shared_ptr<GameManager> getInstance();

    shared_ptr<Table> table;

    void runGame(default_random_engine rng);
    void runAllTurns(default_random_engine rng);
    void shuffleDeck(default_random_engine rng);
    char printCardValue(shared_ptr<Card> card);
    void printDeck();

    void addPlayer(bool isBot, int id);

    GameManager();
};

#endif