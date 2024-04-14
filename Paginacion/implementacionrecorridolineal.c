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

// Este programa crea una memoria virtual y despues hace un recorrido en ella,
// pero cada vez que se hace un referencia a memoria, se usa la memoria física.
//
// Para compilar en consola (con el compilardor MinGW), dirigase
// a la ruta donde se encuentran el codigo fuente e introducir:
//
//    gcc bits.c bytes.c implementacionrecorridolineal.c listascirculares.c logica.c memoriavirtual.c reloj.c -o implementacion.exe
// 
// Despues, para ejecutar el programa en consola, introducir:
//
//    implementacion.exe
//
// Si en la fila 7, columna 3 se muestra 00, su algoritmo de remplazo de
// páginas funciona correctamente.

#include <stdlib.h>

#include "memoriavirtual.h"

int main(int argc, char* argv[]) {
  MemoriaVirtual* mv = MVCrear(128, 4, 64);

  /*char* buffer;
  for (int i = 0; i < 128; ++i) {
    printf("%s ", (buffer = ByteAHex(*(MVObtenerDireccionFisica(mv, i)))));
    free(buffer);
  }*/

  MVEntrada(mv, 00, 64 * 7 + 2);
  /*byte* actual = MVObtenerDireccionFisica(mv, 16 * 7 + 2);
  *actual = 255;*/

  for (int i = 0; i < 128; ++i) {
    for (int j = 0; j < 64; ++j) {
      printf("%02X", MVSalida(mv, i * 64 + j));

      if (j + 1 < 64) {
        putchar(' ');
      }
    }
    if (i + 1 < 128) {
      putchar('\n');
    }
  }

  MVLiberar(mv);
  return 0;
}