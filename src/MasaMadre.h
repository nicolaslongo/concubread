#ifndef MASAMADRE_H_
#define MASAMADRE_H_

#include <random>
#include <ctime>
// #include "../utils/Random.h"

#include <sys/shm.h>

using namespace std;

class MasaMadre {

    private:
        int racionNumero;
        int gramaje;
        void setearGramaje(unsigned int seed_number);
        bool consumida = false;

    protected:

    public:
        MasaMadre(int racionNumero);
        ~MasaMadre();
        int getGramaje();
        void setearConsumida();

};

#endif