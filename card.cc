#include "card.h"
#include <iostream>

using namespace std;

Card::Card(char suit, int value)
    : suit{suit}, value{value}
{}

ostream & operator<<(ostream &out, const Card &c){
    out << c.suit << c.value << endl;
    return out;
}