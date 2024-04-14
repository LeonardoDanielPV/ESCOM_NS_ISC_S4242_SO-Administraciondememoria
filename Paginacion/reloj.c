/**
 * reloj.c
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

#include "reloj.h"

Reloj* RCrear() {
  Reloj* r = (Reloj*)malloc(sizeof(Reloj));

  r->lc = LCCrearListaCircular();
  r->manecilla = NULL;

  return r;
}

MarcoPagina* RCrearMarcoPagina(boolean R, int indice, int nro_pagina) {
  MarcoPagina* mp = (MarcoPagina*)malloc(sizeof(MarcoPagina));

  mp->R = R;
  mp->indice = indice;
  mp->nro_pagina = nro_pagina;

  return mp;
}

void RInsertarMarcoPagina(Reloj* r, boolean R, int indice, int nro_pagina) {
  MarcoPagina* mp = RCrearMarcoPagina(R, indice, nro_pagina);
  LCInsertarValorDown(r->lc, mp);

  r->manecilla = r->lc->top->anterior;
}

void RActualizarR(Reloj* r, boolean R) {
  if (r->manecilla != NULL) {
    ((MarcoPagina*)(r->manecilla->valor))->R = R;
  }
}

void RActualizarIndice(Reloj* r, int indice) {
  if (r->manecilla != NULL) {
    ((MarcoPagina*)(r->manecilla->valor))->indice = indice;
  }
}

// Mueve la manesilla en el sentido de las agujas del reloj (hacia abajo)
// si `sentido` = true, o en el otro sentido `sentido` = false
void RMoverManecilla(Reloj* r, boolean sentido) {
  if (r->manecilla != NULL) {
    if (sentido) {
      r->manecilla = r->manecilla->siguiente;
    } else {
      r->manecilla = r->manecilla->anterior;
    }
  }
}

MarcoPagina* RObtenerMarcoPagina(Reloj* r) {
  MarcoPagina* mp;
  if (r->manecilla == NULL) {
    mp = NULL;
  } else {
    mp = r->manecilla->valor;
  }
}