#include "set.h"


int get_representante(Set* sets, int indice){
    if (sets[indice].r == indice){
        return indice;
    }
    // realizamos compresion de camino
    sets[indice].r = get_representante(sets, sets[indice].r);
    
    return sets[indice].r;
}

void make_union(Set* sets, int punto_a, int punto_b){
    Set* representante_a = &sets[get_representante(sets, punto_a)];
    Set* representante_b = &sets[get_representante(sets, punto_b)];

     if (representante_a->rango > representante_b->rango){
         representante_b->r = representante_a->r;
     }
     else if (representante_b->rango > representante_a->rango){
         representante_a->r = representante_b->r;
     }
     else{
        representante_b->r = representante_a->r;
        representante_a->rango+=1;
     }

}
