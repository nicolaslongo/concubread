#ifndef CONSTANTES_H_
#define CONSTANTES_H_

#include <string.h>

const int PARENT_PROCESS = 0;
const int CHILD_PROCESS = 1;

const int PEDIDO_NULO = 0;
const int PEDIDO_PAN_FLAG = 1;
const int PEDIDO_PIZZA_FLAG = 2;

const char* const PEDIDO_PAN = "Pedido de Panes\n";
const char* const PEDIDO_PIZZA = "Pedido de Pizza\n";
const int LARGO_PEDIDO = strlen(PEDIDO_PAN);

const char* const PEDIDO_MM = "Solicito una ración de Masa Madre al compañero Especialista\n";

#endif