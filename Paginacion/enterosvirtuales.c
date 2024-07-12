/**
 * enterosvirtuales.c
 * 
 * Márquez Ruíz Itzel Monserrat
 * Pérez Velázquez Leonardo Daniel
 * Roque Villarreal Juan Vicente
 * 
 * 13/04/2024
 * 
 * Verción 4
*/

#include <stdlib.h>

#include "enterosvirtuales.h"
#include "matematicas.h"
#include "bits.h"

VectorEnteros* EVCrear(int cantidad) {
  const int enteros_por_pagina = 8;
  const int bytes_por_enteros = sizeof(int);
  // Para tener 8 enteros de 4 bytes por cada marco de pagina se necesitan
  // 4 * 8 = 32 bytes en el marco de pagina.
  const int marco_pagina_longitud = enteros_por_pagina * bytes_por_enteros;
  const int dir_fisicas_longitud = 4;

  int dir_virtuales_longitud = DivCeil(cantidad, enteros_por_pagina);

  MemoriaVirtual* mv = MVCrear(dir_virtuales_longitud,
                               dir_fisicas_longitud,
                               marco_pagina_longitud);
                               
  VectorEnteros* ve = (VectorEnteros*)malloc(sizeof(VectorEnteros));
  ve->mv = mv;
  ve->cantidad = cantidad;

  return ve;
}

void EVLiberar(VectorEnteros* ve) {
  MVLiberar(ve->mv);
  free(ve);
}

void EVSetValor(VectorEnteros* ve, int indice, int valor) {
  if (indice < ve->cantidad) {
    int direccion_virtual = indice * 4;
    byte b0 = valor >> 3 * 8;
    byte b1 = ((valor << 1 * 8) >> 1 * 8) >> 2 * 8;
    byte b2 = ((valor << 2 * 8) >> 2 * 8) >> 1 * 8;
    byte b3 = ((valor << 3 * 8) >> 3 * 8);

    MVEntrada(ve->mv, b0, direccion_virtual); 
    MVEntrada(ve->mv, b1, direccion_virtual + 1);
    MVEntrada(ve->mv, b2, direccion_virtual + 2);
    MVEntrada(ve->mv, b3, direccion_virtual + 3);
  }
}

int EVGetValor(VectorEnteros* ve, int indice) {
  int valor = 0;
  if (indice < ve->cantidad) {
    int direccion_virtual = indice * 4;
    byte b0 = MVSalida(ve->mv, direccion_virtual);
    byte b1 = MVSalida(ve->mv, direccion_virtual + 1);
    byte b2 = MVSalida(ve->mv, direccion_virtual + 2);
    byte b3 = MVSalida(ve->mv, direccion_virtual + 3);

    valor = (valor << 8) | b0;
    valor = (valor << 8) | b1;
    valor = (valor << 8) | b2;
    valor = (valor << 8) | b3;
  }

  return valor;
}