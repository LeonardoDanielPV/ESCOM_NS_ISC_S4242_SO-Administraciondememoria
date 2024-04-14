/**
 * memoriavirtual.h
 * 
 * Márquez Ruíz Itzel Monserrat
 * Pérez Velázquez Leonardo Daniel
 * Roque Villarreal Juan Vicente
 * 
 * 13/04/2024
 * 
 * Verción 4
*/

#ifndef PAGINACION_MEMORIAVIRTUAL_H_
#define PAGINACION_MEMORIAVIRTUAL_H_

#include <stdio.h>

#include "bytes.h"
#include "reloj.h"

typedef struct {
  FILE* memoria_externa;
  int* tabla_direcciones;
  // td: tabla direcciones
  // dvs: direcciones_virtuales_longitud
  // td_longitud = dvs_longitud
  int td_longitud;

  byte* memoria_fisica;
  // dfs: direcciones físicas
  int dfs_longitud;
  // El tamaño de una página virtual es igual al de una marco de pagina
  int marco_pagina_longitud;
  int marco_pagina_longitud_log_2;

  // Para el algoritmo de remplazo de páginas
  Reloj* r;
} MemoriaVirtual;

MemoriaVirtual* MVCrear(int dir_virtuales_longitud, int dir_fisicas_longitud,
                        int marco_pagina_longitud);
byte* MVObtenerDireccionFisica(MemoriaVirtual* mv, int direccion_virtual);
void MVRemplazoPagina(MemoriaVirtual* mv, int indice_tabla_direcciones);

// El algoritmo de remplazo de páginas: reloj.
void MVAlgoritmoRempPagReloj(MemoriaVirtual* mv, int direccion_virtual);
// El algoritmo de reemplazo de páginas: Primera en entrar, primera en salir
// (FIFO).
void MVAlgoritmoRempPagFIFO(MemoriaVirtual* mv, int direccion_virtual);

void MVCopiarPaginaVirtualAFisica(MemoriaVirtual* mv, int direccion_virtual);
byte MVLeerDesdeMemoriaExterna(FILE* memoria_externa, int direccion);
void MVEditarDesdeMemoriaExterna(FILE* meomoria_externa, int direccion,
                                 byte valor);
void MVEntrada(MemoriaVirtual* mv, byte entrada, int direccion_virtual);
byte MVSalida(MemoriaVirtual* mv, int direccion_virtual);
void MVLiberar(MemoriaVirtual* mv);

void MVAgregarPagina(MemoriaVirtual* mv);

#endif  // PAGINACIONS_MEMORIAVIRTUAL_H_