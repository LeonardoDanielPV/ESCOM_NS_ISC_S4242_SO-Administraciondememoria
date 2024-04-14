/**
 * memoriavirtual.c
 * 
 * Márquez Ruíz Itzel Monserrat
 * Pérez Velázquez Leonardo Daniel
 * Roque Villarreal Juan Vicente
 * 
 * 13/04/2024
 * 
 * Verción 4
*/

#ifndef PAGINACION_RELOJ_H_
#define PAGINACION_RELOJ_H_

#include "listascirculares.h"
#include "logica.h"

typedef struct {
  boolean R;
  int indice;
  // Variable constante
  int nro_pagina;
} MarcoPagina;

typedef struct {
  ListaCircular* lc;
  NodoEnlazadoDoble* manecilla;
} Reloj;

Reloj* RCrear();
MarcoPagina* RCrearMarcoPagina(boolean R, int indice, int nro_pagina);
void RInsertarMarcoPagina(Reloj* r, boolean R, int indice, int nro_pagina);
void RActualizarR(Reloj* r, boolean R);
void RActualizarIndice(Reloj* r, int indice);
// Mueve la manesilla en el sentido de las agujas del reloj (hacia abajo)
// si `sentido` = true, o en sentido inverso si `sentido` = false
void RMoverManecilla(Reloj* r, boolean sentido);
MarcoPagina* RObtenerMarcoPagina(Reloj* r);

#endif  // PAGINACION_RELOJ_H_