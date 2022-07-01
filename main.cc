#include "gameManager.h"
#include "card.h"

using namespace std;

#include <algorithm>
#include <random>
#include <stdexcept>
#include <chrono>
#include <iostream>
#include <memory>

int main(int argc, char *argv[]){
    GameManager::getInstance()->table = make_shared<Table>();

    unsigned seed;

    if(argc > 1){
        try{
            seed = stoi(string{ argv[1] });
        }catch( invalid_argument & e ) {
            cerr << e.what() << endl;
            return 1;
        } catch( std::out_of_range & e ) {
            cerr << e.what() << endl;
            return -1;
        }
    }

    default_random_engine rng{seed};

    cout << string{ argv[1] } << endl;

    GameManager::getInstance()->runGame(rng);

    return 0;
}