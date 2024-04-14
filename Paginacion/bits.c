/**
 * bits.c
 * 
 * Márquez Ruíz Itzel Monserrat
 * Pérez Velázquez Leonardo Daniel
 * Roque Villarreal Juan Vicente
 * 
 * 13/04/2024
 * 
 * Verción 4
*/

#include <math.h>

#include "bits.h"

int PrimerosNBits(int nro, int n) {
  int bits;
  
  //bits = ((int)powf(2, n) - 1) & nro;
  bits = ((1 << n) - 1) & nro;

  return bits;
}

int QuitarPrimerosNBits(int nro, int n) {
  int bits;

  bits = (nro >> n) << n;

  return bits; 
}