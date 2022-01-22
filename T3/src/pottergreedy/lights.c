#include "lights.h"




// void quicksort( Camino arreglo[], int izquierda, int derecha) {
//   if (izquierda < derecha) {
//     int indiceParticion = particion(arreglo, izquierda, derecha);
//     quicksort(arreglo, izquierda, indiceParticion);
//     quicksort(arreglo, indiceParticion + 1, derecha);
//   }
// }


// int particion(Camino arreglo[], int izquierda, int derecha) {
//   // Elegimos el pivote, es el primero
//    Camino pivote = arreglo[izquierda];
//   // Ciclo infinito
//   while (1) {
//     while (arreglo[izquierda].costo < pivote.costo) {
//       izquierda++;
//     }
//     while (arreglo[derecha].costo > pivote.costo) {
//       derecha--;
//     }
//     if (izquierda >= derecha) {
//       return derecha;
//     } else {
//         Camino temp = arreglo[izquierda];
//         arreglo[izquierda] = arreglo[derecha];
//         arreglo[derecha] = temp;
//         izquierda++;
//         derecha--;
//     }
//   }
// }