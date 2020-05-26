#ifndef RANDOM_H_
#define RANDOM_H_

#include <random>
#include <ctime>

int getRandomNumber(int seed_number);

int getRandomNumber(int seed_number) {

    std::srand(seed_number * std::time(0));

    return 1 + (int) (20.0 * std::rand()/(RAND_MAX+1.0) ) - 10;
}


#endif 