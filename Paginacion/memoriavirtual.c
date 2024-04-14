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

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "memoriavirtual.h"
#include "bits.h"

int mv_creadas = 0;

// Crear una memoria virtual
// Ejemplo:
//    [Insertar ejemplo]
MemoriaVirtual* MVCrear(int dir_virtuales_longitud, int dir_fisicas_longitud,
                        int marco_pagina_longitud) {
  char nombre_archivo[64] = "memoriaexterna";
  char numero_archivo[64];
  strcat(nombre_archivo, itoa(mv_creadas++, numero_archivo, 10));
  strcat(nombre_archivo, ".mv");

  FILE* memoria_externa = fopen(nombre_archivo, "w+b");
  int bytes_virtuales = dir_virtuales_longitud * marco_pagina_longitud;
  srand(time(NULL));
  for (int i = 0; i < bytes_virtuales; ++i) {
    fputc(rand() % 256, memoria_externa);
  }

  int bytes_fisicos = dir_fisicas_longitud * marco_pagina_longitud;
  byte* memoria_fisica = (char*)malloc(
      sizeof(char) * bytes_fisicos);
  for (int i = 0; i < bytes_fisicos; ++i) {
      memoria_fisica[i] = MVLeerDesdeMemoriaExterna(memoria_externa, i);
  }

  int* tabla_direcciones = (int*)malloc(sizeof(int) * dir_virtuales_longitud);
  for (int i = 0; i < dir_fisicas_longitud; ++i) {
    tabla_direcciones[i] = i;
  }
  for (int i = dir_fisicas_longitud; i < dir_virtuales_longitud; ++i) {
    tabla_direcciones[i] = -1;
  }

  MemoriaVirtual* mv = (MemoriaVirtual*)malloc(sizeof(MemoriaVirtual));
  mv->memoria_externa = memoria_externa;
  mv->tabla_direcciones = tabla_direcciones;
  mv->td_longitud = dir_virtuales_longitud;
  
  mv->memoria_fisica = memoria_fisica;
  mv->dfs_longitud = dir_fisicas_longitud;
  mv->marco_pagina_longitud = marco_pagina_longitud;
  mv->marco_pagina_longitud_log_2 = (int)log2f(marco_pagina_longitud);

  // Para el algoritmo de remplazo de páginass
  Reloj* r = RCrear();
  for (int i = 0; i < dir_fisicas_longitud; ++i) {
    RInsertarMarcoPagina(r, true, i, i);
  }
  mv->r = r;

  return mv;
}

// Para cuando se hace una referencia a memoria
// Ejemplo:
//    [Insertar ejemplo]
byte* MVObtenerDireccionFisica(MemoriaVirtual* mv, int direccion_virtual) {
  int indice_tabla_direcciones =
      direccion_virtual >> mv->marco_pagina_longitud_log_2;

  // Algoritmo para aumentar el tamaño de la memoria virtual (parte dinámica).
  while (indice_tabla_direcciones >= mv->td_longitud) {
    MVAgregarPagina(mv);
  }

  if (mv->tabla_direcciones[indice_tabla_direcciones] < 0) {
    MVRemplazoPagina(mv, direccion_virtual);
  }

  byte* direccion;
  direccion = mv->memoria_fisica +
              mv->marco_pagina_longitud *
              mv->tabla_direcciones[indice_tabla_direcciones] +
              PrimerosNBits(direccion_virtual, mv->marco_pagina_longitud_log_2);

  return direccion;
}

void MVRemplazoPagina(MemoriaVirtual* mv, int direccion_virtual) {
  MVAlgoritmoRempPagReloj(mv, direccion_virtual);
  MVCopiarPaginaVirtualAFisica(
      mv,
      QuitarPrimerosNBits(direccion_virtual,
                          mv->marco_pagina_longitud_log_2));
}

// El algoritmo de remplazo de páginas: reloj.
void MVAlgoritmoRempPagReloj(MemoriaVirtual* mv, int direccion_virtual) {
  int indice_tabla_direcciones =
      direccion_virtual >> mv->marco_pagina_longitud_log_2;

  while (RObtenerMarcoPagina(mv->r)->R) {
    RActualizarR(mv->r, false);
    RMoverManecilla(mv->r, true);
  }
  mv->tabla_direcciones[RObtenerMarcoPagina(mv->r)->indice] = -1;
  RActualizarIndice(mv->r, indice_tabla_direcciones);
  RActualizarR(mv->r, true);

  mv->tabla_direcciones[indice_tabla_direcciones] =
      RObtenerMarcoPagina(mv->r)->nro_pagina;
  
  RMoverManecilla(mv->r, true);
}

// El algoritmo de reemplazo de páginas: Primera en entrar, primera en salir
// (FIFO).
void MVAlgoritmoRempPagFIFO(MemoriaVirtual* mv, int direccion_virtual) {

}

void MVCopiarPaginaVirtualAFisica(MemoriaVirtual* mv, int direccion_virtual) {
  // Si no hay desplazamiento
  if (!PrimerosNBits(direccion_virtual, mv->marco_pagina_longitud_log_2)) {
    int indice_tabla_direcciones =
        direccion_virtual >> mv->marco_pagina_longitud_log_2;

    byte* direccion;
    direccion = mv->memoria_fisica +
                mv->marco_pagina_longitud *
                mv->tabla_direcciones[indice_tabla_direcciones];

    for (int i = 0; i < mv->marco_pagina_longitud; ++i) {
      *(direccion + i) = MVLeerDesdeMemoriaExterna(mv->memoria_externa,
                                                   direccion_virtual + i);
    }
  }
}

// Leer contenido directamente de una memoria virtual
// Ejemplo:
//    [Insertar ejemplo]
byte MVLeerDesdeMemoriaExterna(FILE* memoria_externa, int direccion) {
  byte a_extraer;

  fseek(memoria_externa, direccion, SEEK_SET);
  a_extraer = fgetc(memoria_externa);

  return a_extraer;
}

// Editar contenido directamente de una memoria virtual
// Ejemplo:
//    [Insertar ejemplo]
void MVEditarDesdeMemoriaExterna(FILE* meomoria_externa, int direccion,
                                 byte valor) {
  fseek(meomoria_externa, direccion, SEEK_SET);
  fputc(valor, meomoria_externa);
}

void MVEntrada(MemoriaVirtual* mv, byte entrada, int direccion_virtual) {
  byte* direccion = MVObtenerDireccionFisica(mv, direccion_virtual);

  *direccion = entrada;
  MVEditarDesdeMemoriaExterna(mv->memoria_externa, direccion_virtual, entrada);
}

byte MVSalida(MemoriaVirtual* mv, int direccion_virtual) {
  byte* direccion = MVObtenerDireccionFisica(mv, direccion_virtual);

  return *direccion;
}

// Liberar espacio de una memoria virtual
// Ejemplo:
//    [Insertar ejemplo]
void MVLiberar(MemoriaVirtual* mv) {
  fclose(mv->memoria_externa);
  free(mv->tabla_direcciones);
  free(mv->memoria_fisica);

  mv->memoria_externa = NULL;
  mv->tabla_direcciones = NULL;
  mv->memoria_fisica = NULL;
}

void MVAgregarPagina(MemoriaVirtual* mv) {
  int* tabla_direcciones = (int*)realloc(mv->tabla_direcciones,
                                         sizeof(int) *(mv->td_longitud + 1));
  tabla_direcciones[mv->td_longitud] = -1;
  
  mv->tabla_direcciones = tabla_direcciones;
  mv->td_longitud += 1;

  int direccion_virtual = mv->marco_pagina_longitud * (mv->td_longitud - 1);
  fseek(mv->memoria_externa, direccion_virtual, SEEK_SET);
  for (int i = 0; i < mv->marco_pagina_longitud; ++i) {
    fputc(0, mv->memoria_externa);
  }
}