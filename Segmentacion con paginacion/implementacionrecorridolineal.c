/**
 * implementacionrecorridolineal.c
 * 
 * Márquez Ruíz Itzel Monserrat
 * Pérez Velázquez Leonardo Daniel
 * Roque Villarreal Juan Vicente
 * 
 * 13/04/2024
 * 
 * Verción 4
*/

// Para compilar en consola (con el compilardor MinGW), dirigase
// a la ruta donde se encuentran el codigo fuente e introducir:
//
//    gcc ../Paginacion/bits.c ../Paginacion/bytes.c ../Paginacion/listascirculares.c ../Paginacion/logica.c ../Paginacion/memoriavirtual.c ../Paginacion/reloj.c segmento.c implementacionrecorridolineal.c -o implementacion.exe
// 
// Despues, para ejecutar el programa en consola, introducir:
//
//    implementacion.exe

#include <stdio.h>

#include "segmento.h"

int main(int argc, char* argv) {
  SegmentoDelDescriptor* sd = SCrearSegmentoDelDescriptor();

  DireccionVirtual dv1;
  dv1.nro_segmento = SCrearSegmento(sd, 100, 4, 32);

  dv1.nro_pagina = 11;
  dv1.desplazamiento = 2;
  SEntrada(sd, 0, dv1);
  dv1.desplazamiento = 3;
  SEntrada(sd, 0, dv1);
  dv1.desplazamiento = 4;
  SEntrada(sd, 0, dv1);
  dv1.desplazamiento = 5;
  SEntrada(sd, 0, dv1);

  for (int i = 0; i < 100; ++i) {
    dv1.nro_pagina = i;
    for (int j = 0; j < 32; ++j) {
      dv1.desplazamiento = j;
      printf("%02X ", SSalida(sd, dv1));
    }
    putchar('\n');
  }
  putchar('\n');

  DireccionVirtual dv2;
  dv2.nro_segmento = SCrearSegmento(sd, 16, 4, 32);

  dv2.nro_pagina = 11;
  dv2.desplazamiento = 2;
  SEntrada(sd, 255, dv2);
  dv2.desplazamiento = 3;
  SEntrada(sd, 255, dv2);
  dv2.desplazamiento = 4;
  SEntrada(sd, 255, dv2);
  dv2.desplazamiento = 5;
  SEntrada(sd, 255, dv2);

  for (int i = 0; i < 16; ++i) {
    dv2.nro_pagina = i;
    for (int j = 0; j < 32; ++j) {
      dv2.desplazamiento = j;
      printf("%02X ", SSalida(sd, dv2));
    }
    putchar('\n');
  }
  putchar('\n');

  dv1.nro_pagina = 102;
  dv1.desplazamiento = 0;
  SEntrada(sd, 254, dv1);

  dv1.nro_pagina = 109;
  dv1.desplazamiento = 2;
  SEntrada(sd, 254, dv1);

  for (int i = 0; i < sd->ds[dv1.nro_segmento]->mv->td_longitud; ++i) {
    for (int j = 0; j < sd->ds[dv1.nro_segmento]->mv->marco_pagina_longitud; ++j) {
      dv1.nro_pagina = i;
      dv1.desplazamiento = j;
      printf("%02X ", SSalida(sd, dv1));
    }
    putchar('\n');
  }
  putchar('\n');

  SLiberarSegementoDelDescriptor(sd);
}