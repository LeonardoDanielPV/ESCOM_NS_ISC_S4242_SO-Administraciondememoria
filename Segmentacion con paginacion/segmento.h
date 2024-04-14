/**
 * segmento.h
 * 
 * Márquez Ruíz Itzel Monserrat
 * Pérez Velázquez Leonardo Daniel
 * Roque Villarreal Juan Vicente
 * 
 * 13/04/2024
 * 
 * Verción 4
*/

#ifndef SEGMENTACIONCONPAGINACION_SEGMENTO_H
#define SEGMENTACIONCONPAGINACION_SEGMENTO_H

#include "../Paginacion/memoriavirtual.h"

typedef struct {
  // Dirección de memoria principal de la tabla de páginas.
  MemoriaVirtual* mv;
  
  // Longitud del segmento (en páginas):
  // mv->td_longitud

  // Tamaño de página
  // mv->marco_pagina_longitud
  
  boolean esta_paginado;
  boolean esta_protegido;
} DescriptorDeSegmento;

typedef struct {
  DescriptorDeSegmento** ds;
  int cantidad;
} SegmentoDelDescriptor;

typedef struct {
  int nro_segmento;

  int nro_pagina;
  int desplazamiento;
} DireccionVirtual;

int SCrearSegmento(SegmentoDelDescriptor* sd,
                   int dir_virtuales_longitud,
                   int dir_fisicas_longitud,
                   int marco_pagina_longitud);
SegmentoDelDescriptor* SCrearSegmentoDelDescriptor();
void SAgregarDescriptorDeSegmento(SegmentoDelDescriptor* sd,
                                  DescriptorDeSegmento* ds);
byte SSalida(SegmentoDelDescriptor* sd, DireccionVirtual dv);
byte SEntrada(SegmentoDelDescriptor* sd, byte entrada, DireccionVirtual dv);
void SLiberarSegementoDelDescriptor(SegmentoDelDescriptor* sd);

#endif  // SEGMENTACIONCONPAGINACION_SEGMENTO_H