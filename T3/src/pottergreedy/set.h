#pragma once
#include <stdlib.h>

typedef struct set{ 
    int r;
    int rango;
} Set;

typedef struct punto{ 
    int x;
    int y;
    int id;
} Punto;

typedef struct arista{
    Punto* punto_a;
    Punto* punto_b;
    int costo;
} Arista;


//Encuentra al conjunto, aka find_set   
int get_representante(Set* sets, int indice); 

// Realiza union de los conjuntos retornando el representante comun
void make_union(Set* sets, int punto_a, int punto_b);