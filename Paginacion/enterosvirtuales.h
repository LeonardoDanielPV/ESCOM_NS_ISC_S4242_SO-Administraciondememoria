/**
 * enterosvirtuales.h
 * 
 * Márquez Ruíz Itzel Monserrat
 * Pérez Velázquez Leonardo Daniel
 * Roque Villarreal Juan Vicente
 * 
 * 13/04/2024
 * 
 * Verción 4
*/

#ifndef PAGINACION_ENTEROSVIRTUALES_H_
#define PAGINACION_ENTEROSVIRTUALES_H_

#include "memoriavirtual.h"

typedef struct {
  MemoriaVirtual* mv;
  int cantidad;
} VectorEnteros;

VectorEnteros* EVCrear(int cantidad);
void EVLiberar(VectorEnteros* ve);
void EVSetValor(VectorEnteros* ve, int indice, int valor);
int EVGetValor(VectorEnteros* ve, int indice);

#endif  // PAGINACION_ENTEROSVIRTUALES_H_