#include "table.h"
#include "card.h"
#include "gameManager.h"

void Table::clearTable(){
    clubPile.clear();
    diamondPile.clear();
    heartPile.clear();
    spadesPile.clear();
}

vector<shared_ptr<Card>> Table::getClubs(){
    return clubPile;
}


vector<shared_ptr<Card>> Table::getDiamonds(){
    return diamondPile;
}

vector<shared_ptr<Card>> Table::getHearts(){
    return heartPile;
}

vector<shared_ptr<Card>> Table::getSpades(){
    return spadesPile;
}

void Table::addCard(shared_ptr<Card> card){
    switch(card->suit){
        case 'C':
            if(clubPile.size() == 0){
                clubPile.push_back(card);
            }else if(card->value < clubPile.front()->value){
                clubPile.insert(clubPile.begin(), card);
            }else if(card->value > clubPile.back()->value){
                clubPile.push_back(card);
            }
            break;
        case 'D':
            if(diamondPile.size() == 0){
                diamondPile.push_back(card);
            }else if(card->value < diamondPile.front()->value){
                diamondPile.insert(diamondPile.begin(), card);
            }else if(card->value > diamondPile.back()->value){
                diamondPile.push_back(card);
            }
            break;
        case 'H':
            if(heartPile.size() == 0){
                heartPile.push_back(card);
            }else if(card->value < heartPile.front()->value){
                heartPile.insert(heartPile.begin(), card);
            }else if(card->value > heartPile.back()->value){
                heartPile.push_back(card);
            }
            break;
        case 'S':
            if(spadesPile.size() == 0){
                spadesPile.push_back(card);
            }else if(card->value < spadesPile.front()->value){
                spadesPile.insert(spadesPile.begin(), card);
            }else if(card->value > spadesPile.back()->value){
                spadesPile.push_back(card);
            }
            break;
    }
}

bool Table::isLegal(shared_ptr<Card> card){
    if(spadesPile.size() == 0){
        if(card->suit == 'S' && card->value == 7){
           return true; 
        }else{
            return false;
        }
    }
    switch(card->suit){
        case 'C':
            if(clubPile.size() == 0){
                if(card->value == 7){
                    return true;
                }else{
                    return false;
                }
            }else if(card->value == clubPile.front()->value - 1){
                return true;
            }else if(card->value == clubPile.back()->value + 1){
                return true;
            }else{
                return false;
            }
            break;
        case 'D':
            if(diamondPile.size() == 0){
                if(card->value == 7){
                    return true;
                }else{
                    return false;
                }
            }else if(card->value == diamondPile.front()->value - 1){
                return true;
            }else if(card->value == diamondPile.back()->value + 1){
                return true;
            }else{
                return false;
            }
            break;
        case 'H':
            if(heartPile.size() == 0){
                if(card->value == 7){
                    return true;
                }else{
                    return false;
                }
            }else if(card->value == heartPile.front()->value - 1){
                return true;
            }else if(card->value == heartPile.back()->value + 1){
                return true;
            }else{
                return false;
            }
            break;
        case 'S':
            if(spadesPile.size() == 0){
                if(card->value == 7){
                    return true;
                }else{
                    return false;
                }
            }else if(card->value == spadesPile.front()->value - 1){
                return true;
            }else if(card->value == spadesPile.back()->value + 1){
                return true;
            }else{
                return false;
            }
            break;
        default:
            break;
    }
}