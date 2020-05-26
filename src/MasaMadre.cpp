#include "MasaMadre.h"

const int GRAMAJE_ESTANDAR = 100;

MasaMadre::MasaMadre(int racionNumero) {
    racionNumero = racionNumero;
    setearGramaje((unsigned int)racionNumero);
}

void MasaMadre::setearGramaje(unsigned int seed_number) {

    std::srand(seed_number * std::time(0));

    int desvio = 1 + (int) (20.0 * std::rand()/(RAND_MAX+1.0) ) - 10;
    
    gramaje = GRAMAJE_ESTANDAR + desvio;
}

void MasaMadre::setearConsumida() {
    consumida = true;
}

int MasaMadre::getGramaje(){
    return gramaje;
}

MasaMadre::~MasaMadre() {

}
