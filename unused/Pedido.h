#ifndef PEDIDO_H_
#define PEDIDO_H_

typedef struct {
	int despachado = 0;
	int tomado = 0;
} Estado_t;

class Pedido { 
    
    private:
    // Todo esto debe ser shared memory!
    int tipoDePedido;
    int shmIdEstado;        
    Estado_t* estado;       // esto va a ser memoria compartida :)

    // despacharPedido();
    // tomarPedido();

    protected:

	public:
    // inicializarEstado()  // la primera funcion a la que llamo. Esta inicializa
                            // la shared memory en mi proceso. Recien ahi puedo
                            // operar realmente con el pedido. Hasta entonces es un
                            // simple puntero más
    //lockEstado(); // tiene que ser un lock de escritura.
                    // antes de interactuar con el estado pido
                    // este lock.
    //unlockEstado();
    //estaDespachado();
    //estaTomado();
	Pedido();
	~Pedido() { };

};


#endif