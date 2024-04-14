/**
 * implementacionvectorenteros.c
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
//    gcc bits.c bytes.c enterosvirtuales.c implementacionvectorenteros.c listascirculares.c logica.c matematicas.c memoriavirtual.c reloj.c -o implementacion.exe
// 
// Despues, para ejecutar el programa en consola, introducir:
//
//    implementacion.exe
//
// Si en la fila 7, columna 3 se muestra 00, su algoritmo de remplazo de
// páginas funciona correctamente.

#include "enterosvirtuales.h"

int main(int argc, char* argv[]) {
  int numeros_cantidad = 5000;
  VectorEnteros* ve = EVCrear(numeros_cantidad);

  printf("Editando...");
  for (int i = 0; i < numeros_cantidad; ++i) {
    EVSetValor(ve, i, i);
  }
  printf("\nEditado\n");

  for (int i = 0; i < numeros_cantidad; ++i) {
    printf("%d ", EVGetValor(ve, i));
  }

  EVLiberar(ve);
  return 0;
}