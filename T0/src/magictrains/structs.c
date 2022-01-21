#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "structs.h"



Estacion* create_estacion(int id, int andenes)
{
  Estacion* estacion = malloc(sizeof(Estacion));
  *estacion = (Estacion){
      estacion -> id = id, 
      estacion -> cantidad_andenes = andenes,
      estacion -> andenes= NULL,
  };
  return estacion;
}





Anden* create_anden(int id, Estacion* estacion)
{
    Anden* anden = malloc(sizeof(Anden));
    
    *anden = (Anden){
    anden -> id = id,
    anden ->estacion  =  estacion,
    anden  -> head_normal = NULL,
    anden  -> head_premium = NULL,
    anden -> tren = NULL,
    };
    return anden;
}

Pasajero* create_pasajero(int id, Anden*  anden,Estacion* estacion, Estacion* destino,  int tipo)
{
    Pasajero* pasajero = malloc(sizeof(Pasajero));
    
    *pasajero = (Pasajero){
    pasajero  -> id = id,
    pasajero -> tipo =  tipo,
    pasajero -> destino =  destino,
    pasajero -> estacion =  estacion,
    pasajero -> anden =  anden ,
    pasajero -> next = NULL,
    pasajero -> head = NULL,
    pasajero -> tail = NULL,
    };
    return pasajero;
}

Tren* create_tren(int id, int vagones, Estacion* estacion, Anden* anden){
    
    Tren* tren = malloc(sizeof(Tren));
    
    *tren = (Tren){
    tren-> id = id,
    tren -> total_vagones = vagones,
    tren -> vagones = calloc(vagones, sizeof(Vagon*)),
    tren -> anden =  anden,
    tren -> estacion =  estacion,
    tren -> destino = NULL,
    tren -> next = NULL,
    tren -> prev = NULL,
    tren -> head = NULL,
    };
    return tren;
}

Vagon* create_vagon(int id, int capacidad){
    
    Vagon* vagon = malloc(sizeof(Vagon));
    
    *vagon = (Vagon){
    vagon-> id = id,
    vagon-> n_asientos= capacidad,
    vagon -> asientos = calloc(capacidad, sizeof(Asiento*)),
    };
    return vagon;
}

Asiento* create_asiento(int id){
    
    Asiento* asiento = malloc(sizeof(Asiento));
    
    *asiento = (Asiento){
    asiento-> id = id,
    asiento -> pasajero = NULL,
    };
    return asiento;
}

