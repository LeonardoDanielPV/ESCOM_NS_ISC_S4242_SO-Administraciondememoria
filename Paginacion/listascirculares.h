/**
 * listascirculares.h
 * 
 * Márquez Ruíz Itzel Monserrat
 * Pérez Velázquez Leonardo Daniel
 * Roque Villarreal Juan Vicente
 * 
 * 13/04/2024
 * 
 * Verción 4
*/

#ifndef PAGINACION_LISTASCIRCULARES_H_
#define PAGINACION_LISTASCIRCULARES_H_

typedef struct VectorNodo {
  void* valor;
  struct VectorNodo* siguiente;
  struct VectorNodo* anterior;
} NodoEnlazadoDoble;

typedef struct {
  NodoEnlazadoDoble* top;
} ListaCircular;

NodoEnlazadoDoble* LCCrearNodoEnlazadoDoble(void* valor);
ListaCircular* LCCrearListaCircular();
// Se inserta `valor` como un nuevo nodo en la lista circular `lc`. Este nodo
// será el que este en el inicio, o en la sima, de la lista.
void LCInsertarValorTop(ListaCircular* lc, void* valor);
void LCInsertarValorDown(ListaCircular* lc, void* valor);
// Se elimina que este en el inicio, o en la sima, de la lista circular `ls`.
void LCEliminarTop(ListaCircular* lc);
void LCEliminarDown(ListaCircular* lc);
void* LCTop(ListaCircular* lc);
void* LCDown(ListaCircular* lc);
void LCLiberarLista(ListaCircular* lc);

#endif  // PAGINACION_LISTASCIRCULARES_H_