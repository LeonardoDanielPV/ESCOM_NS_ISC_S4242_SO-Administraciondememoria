/**
 * segmento.c
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

#include "segmento.h"

const int segs_max = 10;

// Regresa el número del segmento creado
// Ejemplo:
//    [Insertar ejemplo]
int SCrearSegmento(SegmentoDelDescriptor* sd,
                   int dir_virtuales_longitud,
                   int dir_fisicas_longitud,
                   int marco_pagina_longitud) {
  if (sd->cantidad == segs_max) {
    return -1;
  }

  MemoriaVirtual* mv = MVCrear(dir_virtuales_longitud,
                               dir_fisicas_longitud,
                               marco_pagina_longitud);
  
  DescriptorDeSegmento* ds = (DescriptorDeSegmento*)malloc(
      sizeof(DescriptorDeSegmento));
  
  ds->mv = mv;
  ds->esta_paginado = true;
  ds->esta_protegido = false;

  SAgregarDescriptorDeSegmento(sd, ds);

  return sd->cantidad - 1;
}

SegmentoDelDescriptor* SCrearSegmentoDelDescriptor() {
  SegmentoDelDescriptor* sd = (SegmentoDelDescriptor*)malloc(
      sizeof(SegmentoDelDescriptor));

  sd->ds = (DescriptorDeSegmento**)malloc(
      sizeof(DescriptorDeSegmento*) * segs_max);
  sd->cantidad = 0;

  for (int i = 0; i < segs_max; ++i) {
    sd->ds[i] = NULL;
  }
  
  return sd;
}

void SAgregarDescriptorDeSegmento(SegmentoDelDescriptor* sd,
                                  DescriptorDeSegmento* ds) {
  sd->ds[sd->cantidad] = ds;
  sd->cantidad += 1;
}

byte SSalida(SegmentoDelDescriptor* sd, DireccionVirtual dv) {
  DescriptorDeSegmento* ds = sd->ds[dv.nro_segmento];

  if (ds == NULL) {
    // Fallo de segmento
    return 0;
  }
  if (ds->esta_protegido) {
    // Fallo (trap)
    return 0;
  }

  int direccion_virtual = dv.nro_pagina * ds->mv->marco_pagina_longitud +
                          dv.desplazamiento;

  byte salida = MVSalida(ds->mv, direccion_virtual);
  return salida;
}

byte SEntrada(SegmentoDelDescriptor* sd, byte entrada, DireccionVirtual dv) {
  DescriptorDeSegmento* ds = sd->ds[dv.nro_segmento];

  if (ds == NULL) {
    // Fallo de segmento
    return 0;
  }
  if (ds->esta_protegido) {
    // Fallo (trap)
    return 0;
  }

  int direccion_virtual = dv.nro_pagina * ds->mv->marco_pagina_longitud +
                          dv.desplazamiento;
  
  MVEntrada(ds->mv, entrada, direccion_virtual);
}

void SLiberarSegementoDelDescriptor(SegmentoDelDescriptor* sd) {
  MemoriaVirtual* mv;
  int i = 0;
  while (sd->ds[i] != NULL && i < segs_max) {
    mv = sd->ds[i]->mv;
    MVLiberar(mv);
    free(sd->ds[i]);
    ++i;
  }
  free(sd->ds);
  free(sd);
}