#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <memory.h>
#include "set.h"
#include <stdio.h>

typedef struct mst{
    int V;
    int E;
} MST;




MST* make_mst(int V, int E);

int kruskal(MST* mst,Arista* aristas,FILE *output_file);
int kruskal_finished(MST* mst,Arista* aristas, FILE *output_file);

int kruskal_print(MST* mst,FILE *output_file);

void create_aristas(MST* mst, Arista* aristas, Punto* puntos);
void add_aristas(MST* mst, Arista* aristas, Punto* puntos, int index_new);
int lessthan(const void* a, const void* b);

int manhattan_dist(Punto punto_a, Punto punto_b);

void quicksort( Arista arreglo[], int izquierda, int derecha);
int particion(Arista arreglo[], int izquierda, int derecha) ;
void inversequicksort( Arista arreglo[], int izquierda, int derecha);

int inversePartition(Arista arreglo[], int izquierda, int derecha) ;