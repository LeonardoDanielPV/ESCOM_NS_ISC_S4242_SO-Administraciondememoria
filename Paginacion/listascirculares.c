/**
 * listascirculares.c
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

#include "listascirculares.h"

NodoEnlazadoDoble* LCCrearNodoEnlazadoDoble(void* valor) {
  NodoEnlazadoDoble* ned = (NodoEnlazadoDoble*)malloc(
      sizeof(NodoEnlazadoDoble));
  ned->valor = valor;
  ned->siguiente = NULL;
  ned->anterior = NULL;

  return ned;
}

ListaCircular* LCCrearListaCircular() {
  ListaCircular* lc = (ListaCircular*)malloc(sizeof(ListaCircular));
  lc->top = NULL;

  return lc;
}

// Se inserta `valor` como un nuevo nodo en la lista circular `lc`. Este nodo
// será el que este en el inicio, o en la sima, de la lista.
void LCInsertarValorTop(ListaCircular* lc, void* valor) {
  NodoEnlazadoDoble* nodo = LCCrearNodoEnlazadoDoble(valor);

  if (lc->top == NULL) {
    nodo->siguiente = nodo;
    nodo->anterior = nodo;
    lc->top = nodo;
  } else {
    NodoEnlazadoDoble* top_pasado = lc->top;
    
    nodo->siguiente = top_pasado;
    nodo->anterior = top_pasado->anterior;

    top_pasado->anterior->siguiente = nodo;
    top_pasado->anterior = nodo;

    lc->top = nodo;
  }
}

void LCInsertarValorDown(ListaCircular* lc, void* valor) {
  NodoEnlazadoDoble* nodo = LCCrearNodoEnlazadoDoble(valor);

  if (lc->top == NULL) {
    nodo->siguiente = nodo;
    nodo->anterior = nodo;
    lc->top = nodo;
  } else {
    NodoEnlazadoDoble* down_pasado = lc->top->anterior;

    nodo->siguiente = down_pasado->siguiente;
    nodo->anterior = down_pasado;

    down_pasado->siguiente->anterior = nodo;
    down_pasado->siguiente = nodo;
  }
}

// Se elimina que este en el inicio, o en la sima, de la lista circular `ls`.
void LCEliminarTop(ListaCircular* lc) {
  if (lc->top != NULL) {
    NodoEnlazadoDoble* top_pasado = lc->top;

    if (top_pasado->siguiente == top_pasado) {
      lc->top = NULL;
    } else {
      top_pasado->anterior->siguiente = top_pasado->siguiente;
      top_pasado->siguiente->anterior = top_pasado->anterior;

      lc->top = top_pasado->siguiente;
    }
  }
}

void LCEliminarDown(ListaCircular* lc) {
  if (lc->top != NULL) {
    NodoEnlazadoDoble* down_pasado = lc->top->anterior;

    if (down_pasado->anterior == down_pasado) {
      lc->top = NULL;
    } else {
      down_pasado->siguiente->anterior = down_pasado->anterior;
      down_pasado->anterior->siguiente = down_pasado->siguiente;
    }
  }
}

void* LCTop(ListaCircular* lc) {
  return lc->top->valor;
}

void* LCDown(ListaCircular* lc) {
  return lc->top->anterior->valor;
}

void LCLiberarLista(ListaCircular* lc) {
  while (lc->top != NULL) {
    LCEliminarTop(lc);
  }
}