/**
 * matematicas.c
 * 
 * Márquez Ruíz Itzel Monserrat
 * Pérez Velázquez Leonardo Daniel
 * Roque Villarreal Juan Vicente
 * 
 * 13/04/2024
 * 
 * Verción 4
*/

#include "matematicas.h"

int DivCeil(int a, int b) {
  int div_ceil;
  
  div_ceil = a / b;
  if (a % b) {
    ++div_ceil;
  }

  return div_ceil;
}