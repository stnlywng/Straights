#include "gameManager.h"
#include <algorithm>
#include <memory>
#include <iostream>

using namespace std;

shared_ptr<GameManager> GameManager::instance = nullptr;

GameManager::GameManager(){
    // to keep track of the beginning of first round, check newRound().
    curPlayer = -1;
}

shared_ptr<GameManager> GameManager::getInstance()
{
    if(GameManager::instance == nullptr){
        GameManager::instance = make_shared<GameManager>();
    }
    return GameManager::instance;
}


void GameManager::shuffleDeck(default_random_engine rng){
    if(shuffledDeck.size() > 0){
        shuffle(shuffledDeck.begin(), shuffledDeck.end(), rng);
    }else{
        for(int i=0; i<4; i++){
            for(int y=1; y<14; y++){
                switch(i){
                    case 0:
                        shuffledDeck.push_back(make_shared<Card>('C', y));
                        break;
                    case 1:
                        shuffledDeck.push_back(make_shared<Card>('D', y));
                        break;
                    case 2:
                        shuffledDeck.push_back(make_shared<Card>('H', y));
                        break;
                    case 3:
                        shuffledDeck.push_back(make_shared<Card>('S', y));
                        break;
                    default:
                        break;
                }
            }
        }
        shuffle(shuffledDeck.begin(), shuffledDeck.end(), rng);
    }
}

void GameManager::runGame(default_random_engine rng){
    //DO THE INPUT STUFF HERE FOR PC/BOT.
    for(int i=0; i<4; i++){
        cout << "Is Player a human (h) or a computer (c)?" << endl;
        char c;
        cin >> c;
        if(c == 'h'){
            addPlayer(false, i+1);
        }else if(c == 'c'){
            addPlayer(true, i+1);
        }
    }

    newRound(rng);
}

void GameManager::runAllTurns(default_random_engine rng){
    for(int i=0; i<52; i++){
        playerGo();
    }
    newRound(rng);
}

void GameManager::playerGo(){
    players.at((curPlayer % 4))->yourTurn();
    curPlayer++;
}

void GameManager::addPlayer(bool isBot, int id){
    players.push_back(make_shared<Player>(isBot, id));
}

// DISTRIBUTE AND ALSO SET curPlayerWithSevenSpades for this round!
void GameManager::distributeCards(){
    for(int i=0; i<13; i++){
        players.at(0)->addToHand(shuffledDeck.at(i));
        if(shuffledDeck.at(i)->value == 7 && shuffledDeck.at(i)->suit == 'S'){
            curPlayerWithSevenSpades = 0;
        }
    }
    for(int i=13; i<26; i++){
        players.at(1)->addToHand(shuffledDeck.at(i));
        if(shuffledDeck.at(i)->value == 7 && shuffledDeck.at(i)->suit == 'S'){
            curPlayerWithSevenSpades = 1;
        }
    }
   
    for(int i=26; i<39; i++){
        players.at(2)->addToHand(shuffledDeck.at(i));
        if(shuffledDeck.at(i)->value == 7 && shuffledDeck.at(i)->suit == 'S'){
            curPlayerWithSevenSpades = 2;
        }
    }
    
    for(int i=39; i<52; i++){
        players.at(3)->addToHand(shuffledDeck.at(i));
        if(shuffledDeck.at(i)->value == 7 && shuffledDeck.at(i)->suit == 'S'){
            curPlayerWithSevenSpades = 3;
        }
    }
}

// sets up the next Round
void GameManager::newRound(default_random_engine rng){
    //add last round points
    
    for(int i=0; i<4; i++){
        // curPlayer = -1 in constructor. Changed when game starts. this stops it from running at the beginning of round 1
        if(curPlayer == -1){ 
            break;
        }
        int oldScore = points[i];
        int newScore = players.at(i)->countAndDiscardTrashPile();
        points[i] += newScore;
        cout << "Player" << i << "'s score: " << oldScore << " + " << newScore << " = " << points[i] << endl;
    }

    //Check for end of game
    if(points[0] >= 80 || points[1] >= 80 || points[2] >= 80 || points[3] >= 80){
        bool winner = false;
        for(int i=0; i<81; i++){
            if(points[0] == i){
                cout << "Player1 wins!" << endl;
                winner = true;
            }
            if(points[1] == i){
                cout << "Player2 wins!" << endl;
                winner = true;
            }
            if(points[2] == i){
                cout << "Player3 wins!" << endl;
                winner = true;
            }   
            if(points[3] == i){
                cout << "Player4 wins!" << endl;
                winner = true;
            }
            if(winner){
                return;
            }
        }
    }
    //setup next round
    else{
        table->clearTable();
        shuffleDeck(rng);
        distributeCards();
        curPlayer = curPlayerWithSevenSpades;
        cout << "A new round begins. It’s Player" << curPlayer+1 << "’s turn to play." << endl;
        runAllTurns(rng);
    }
}

void GameManager::printDeck(){
    for(int i=0; i<4; i++){
        for(int y=0; y<13; y++){
            cout << printCardValue(shuffledDeck.at(i*13 + y)) << shuffledDeck.at(i*13 + y)->suit;
            if(y != 12){
                cout << " ";
            }
        }
        cout << endl;
    }
}

char GameManager::printCardValue(shared_ptr<Card> card){
    if(card->value == 1){
        return 'A';
    }else if(card->value == 11){
        return 'J';
    }else if(card->value == 12){
        return 'Q';
    }else if(card->value == 13){
        return 'K';
    }else if(card->value == 10){
        cout << 1;
        return '0';
    }else{
        return ('0' + card->value);
    }
}