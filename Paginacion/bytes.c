/**
 * bytes.c
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

#include "bytes.h"

char diccionario[16] = {48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 65, 66, 67, 68,
                        69, 70};

char* ByteAHex(byte b) {
  char* b_hex = (char*)malloc(sizeof(char) * 3);

  b_hex[0] = diccionario[((unsigned char)b) / 16];
  b_hex[1] = diccionario[((unsigned char)b) % 16];
  b_hex[2] = '\0';

  return b_hex;
}