#include "players.h"
#include "gameManager.h"
#include "table.h"

#include <memory>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

Player::Player(bool isBot, int id)
    : isBot{isBot}, id{id}
{
}

void Player::addToHand(shared_ptr<Card> newCard){
    hand.push_back(newCard);   
}

void Player::yourTurn(){
    if(isBot){
        botTurn();
    }else{
        humanPlayerTurn();
    }
}

void Player::botTurn(){
    for(int i=0; i<hand.size(); i++){
        if(GameManager::getInstance()->table->isLegal(hand.at(i))){
            cout << "Player" << id << " plays " << GameManager::getInstance()->printCardValue(hand.at(i)) << hand.at(i)->suit << endl;
            GameManager::getInstance()->table->addCard(hand.at(i));
            hand.erase(hand.begin() + i);
            return;
        }
    }

    discarded.push_back(hand.at(0));
    cout << "Player" << id << " discards " << GameManager::getInstance()->printCardValue(hand.at(0)) << hand.at(0)->suit << "." << endl;
    hand.erase(hand.begin());
}

void Player::humanPlayerTurn(){
    cout << "Cards on the table:" << endl;
    cout << "Clubs:";
    printCards('C');
    cout << "Diamonds:";
    printCards('D');
    cout << "Hearts:";
    printCards('H');
    cout << "Spades:";
    printCards('S');
    cout << "Your Hand:";
    printCards('P');
    hasLegalCard = false;
    cout << "Legal Plays:";
    printCards('L');
    processInput();
}

void Player::processInput(){
    string s;
    while(getline(cin, s)){
        istringstream ss {s};
        string cmd;
        if(ss >> cmd){
            if(cmd == "play"){
                string card;
                if(ss >> card){
                    try{
                        int value = translateCardToNum(card.substr(0, 1));
                        char suit = getCharFromString(card.substr(1, 1));

                        if(card.length() == 3){
                            value = translateCardToNum(card.substr(0, 2));
                            suit = getCharFromString(card.substr(2, 1));
                        }
                        
                        if(checkHandForCardAndRemove(suit, value, true)){    
                            cout << "Player" << id << " plays " << translateNumToCard(value) << suit << "." << endl;                        
                            break;
                        }else{
                            cout << "This is not a legal play." << endl;
                        }
                    }catch(invalid_argument iarg){
                        cout << "This is not a legal play." << endl;
                    }
                }
            }else if(cmd == "discard"){
                if(hasLegalCard){
                    cout << "You have a legal play. You may not discard." << endl;
                    continue;
                }

                string card;
                if(ss >> card){
                    try{
                        int value = translateCardToNum(card.substr(0, 1));
                        char suit = getCharFromString(card.substr(1, 1));
                        
                        if(checkHandForCardAndRemove(suit, value, false)){  
                            cout << "Player" << id << " discards " << translateNumToCard(value) << suit << "." << endl;                           
                            break;
                        }
                    }catch(invalid_argument iarg){
                        cout << "Invalid Argument" << endl;
                    }
                }
            }else if(cmd == "deck"){
                GameManager::getInstance()->printDeck();
            }else if(cmd == "quit"){
                exit(0);
            }else if(cmd == "ragequit"){
                isBot = true;
                cout << "Player" << id << " ragequits. A computer will now take over." << endl;
                botTurn();
                break;
            }
        }
    }
}

int Player::translateCardToNum(string s){
    if(s == "A"){
        return 1;
    }else if(s == "J"){
        return 11;
    }else if(s == "Q"){
        return 12;
    }else if(s == "K"){
        return 13;
    }else{
        return stoi(s);
    }
}

string Player::translateNumToCard(int num){
    if(num == 1){
        return "A";
    }else if(num == 11){
        return "J";
    }else if(num == 12){
        return "Q";
    }else if(num == 13){
        return "K";
    }else{
        return to_string(num);
    }
}

char Player::getCharFromString(string s){
    if(s == "C"){
        return 'C';
    }else if(s == "D"){
        return 'D';
    }else if(s == "H"){
        return 'H';
    }else if(s == "S"){
        return 'S';
    }
}

bool Player::checkHandForCardAndRemove(char suit, int value, bool toTable){
    for(int i=0; i<hand.size(); i++){
        if(hand.at(i)->suit == suit && hand.at(i)->value == value){
            if(toTable){
                if(!GameManager::getInstance()->table->isLegal(hand.at(i))){
                    //cout << "This is not a legal play." << endl;
                    return false;
                }
                GameManager::getInstance()->table->addCard(hand.at(i));
            }else{
                discarded.push_back(hand.at(i));
            }

            hand.erase(hand.begin() + i);
            //printCards('P');
            return true;
        }
    }
    return false;
}


void Player::printCards(char suit){
    vector<shared_ptr<Card>> suitWanted; 
    
    switch(suit){
        case 'C':
            suitWanted = GameManager::getInstance()->table->getClubs();
            break;
        case 'D':
            suitWanted = GameManager::getInstance()->table->getDiamonds();
            break;
        case 'H':
            suitWanted = GameManager::getInstance()->table->getHearts();
            break;
        case 'S':
            suitWanted = GameManager::getInstance()->table->getSpades();
            break;
        // PLAYER HAND
        case 'P':
            suitWanted = hand;
            break;
        // LEGAL PLAYS
        case 'L':
            suitWanted = hand;
            break;
    }
    
    for(int i=0; i<suitWanted.size(); i++){
        if(suit == 'P'){
            cout << " " << GameManager::getInstance()->printCardValue(suitWanted.at(i)) << suitWanted.at(i)->suit;
        }else if(suit == 'L'){
            if(GameManager::getInstance()->table->isLegal(suitWanted.at(i))){
                hasLegalCard = true;
                cout << " " << GameManager::getInstance()->printCardValue(suitWanted.at(i)) << suitWanted.at(i)->suit;
            }
        }else{
            cout << " " << GameManager::getInstance()->printCardValue(suitWanted.at(i));
        }
    }
    cout << endl;
}

int Player::countAndDiscardTrashPile(){
    cout << "Player" << id << "'s discards:";
    int total = 0;
    for(int i=0; i<discarded.size(); i++){
        total += discarded.at(i)->value;
        cout << " " << GameManager::getInstance()->printCardValue(discarded.at(i)) << discarded.at(i)->suit;
    }
    cout << endl;
    hand.clear();
    discarded.clear();
    return total;
}
