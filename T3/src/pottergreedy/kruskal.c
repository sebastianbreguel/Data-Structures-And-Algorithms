#include "kruskal.h"


MST* make_mst(int V, int E){
    MST* mst = malloc(1*sizeof(MST));
    mst->V = V;
    mst->E = E;
    return mst;
}

int manhattan_dist(Punto punto_a, Punto punto_b){
    return abs(punto_a.x - punto_b.x) + abs(punto_a.y - punto_b.y);
}

int kruskal(MST* mst,Arista* aristas, FILE *output_file){
    int costo_minimo = 0;
    Set* sets = (Set*)malloc(mst->V * sizeof(Set));

    for(int v=0; v<mst->V; v++){
        sets[v].rango = 0;
        sets[v].r = v;
    }

    int count = 0;
    quicksort(aristas, 0 , mst->E-1);
    for(int i=0; i<mst->E; i++){

        Arista edge = aristas[i];
        Punto* punto_a = edge.punto_a;
        Punto* punto_b = edge.punto_b;
        int representante_a = get_representante(sets, punto_a->id);
        int representante_b = get_representante(sets, punto_b->id);

        if(representante_a != representante_b){
                count++;
                costo_minimo+= edge.costo;
                make_union(sets, representante_a, representante_b);
                }

        if (count >= mst->V-1){
            break;
        }
      
    }
    
    free(sets);
    return costo_minimo;
}
int kruskal_finished(MST* mst,Arista* aristas, FILE *output_file){
    int costo_minimo = 0;
    Set* sets = (Set*)malloc(mst->V * sizeof(Set));

    for(int v=0; v<mst->V; v++){
        sets[v].rango = 0;
        sets[v].r = v;
    }

    int count = 0;
    quicksort(aristas, 0 , mst->E-1);
    for(int i=0; i<mst->E; i++){

        Arista edge = aristas[i];
        Punto* punto_a = edge.punto_a;
        Punto* punto_b = edge.punto_b;
        int representante_a = get_representante(sets, punto_a->id);
        int representante_b = get_representante(sets, punto_b->id);

        if(representante_a != representante_b){
                count++;
                costo_minimo+= edge.costo;
                make_union(sets, representante_a, representante_b);
                fprintf(output_file ,"%4d %4d %4d %4d\n", punto_a-> y,punto_a->x,  punto_b-> y, punto_b->x);
                }

        if (count >= mst->V-1){
            break;
        }
    }
    free(sets);
    return costo_minimo;
}

void create_aristas(MST* mst, Arista* aristas, Punto* puntos){
    int count = 0;
    for(int i=0; i<mst->V; i++){
        for(int j=i+1; j<mst->V; j++){
            Arista arista = aristas[count];
            arista.punto_a = &puntos[i];
            arista.punto_b = &puntos[j];
            arista.costo = manhattan_dist(puntos[i], puntos[j]);
            aristas[count] = arista;
            count++;
        }
    }
    mst->E = count;
}


// References from https://parzibyte.me/blog/2019/10/08/quicksort-c-algoritmo/

void quicksort( Arista arreglo[], int izquierda, int derecha) {
  if (izquierda < derecha) {
    int indiceParticion = particion(arreglo, izquierda, derecha);
    quicksort(arreglo, izquierda, indiceParticion);
    quicksort(arreglo, indiceParticion + 1, derecha);
  }
}


int particion(Arista arreglo[], int izquierda, int derecha) {
  // Elegimos el pivote, es el primero
   Arista pivote = arreglo[izquierda];
  // Ciclo infinito
  while (1) {
    while (arreglo[izquierda].costo < pivote.costo  ) {
      izquierda++;
    }
    while (arreglo[derecha].costo > pivote.costo) {
      derecha--;
    }
    if (izquierda >= derecha) {
      return derecha;
    } else {
        Arista temp = arreglo[izquierda];
        arreglo[izquierda] = arreglo[derecha];
        arreglo[derecha] = temp;
        izquierda++;
        derecha--;
    }
  }
}


void inversequicksort( Arista arreglo[], int izquierda, int derecha) {
  if (izquierda < derecha) {
    int indiceParticion = inversePartition(arreglo, izquierda, derecha);
    inversequicksort(arreglo, izquierda, indiceParticion);
    inversequicksort(arreglo, indiceParticion + 1, derecha);
  }
}


int inversePartition(Arista arreglo[], int izquierda, int derecha) {
  // Elegimos el pivote, es el primero
   Arista pivote = arreglo[izquierda];
  // Ciclo infinito
  while (1) {
    while (arreglo[izquierda].costo > pivote.costo  ) {
      izquierda++;
    }
    while (arreglo[derecha].costo < pivote.costo  ) {
      derecha--;
    }
    if (izquierda >= derecha) {
      return derecha;
    } else {
        Arista temp = arreglo[izquierda];
        arreglo[izquierda] = arreglo[derecha];
        arreglo[derecha] = temp;
        izquierda++;
        derecha--;
    }
  }
}