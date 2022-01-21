#pragma once



struct estacion{
    int id;
    int cantidad_andenes;
    struct anden** andenes;
};
typedef struct estacion Estacion;

struct anden{
    int id;
    struct estacion* estacion;
    struct  pasajero* head_premium;
    struct  pasajero* head_normal;
    struct tren* tren;
};
typedef struct anden Anden;

struct pasajero{
    int  id;
    int tipo;
    struct estacion* destino;
    struct estacion* estacion;
    struct anden* anden;
    struct pasajero* head;
    struct pasajero* tail;
    struct pasajero* next;
};

typedef struct pasajero Pasajero;

struct  asiento{
    int  id;
    struct pasajero* pasajero;
};
typedef struct asiento Asiento;

struct vagon{
    int id;
    int n_asientos;
    Asiento** asientos;
};
typedef struct vagon Vagon;

struct tren{
    int id;
    int  total_vagones;
    Vagon** vagones;
    struct estacion* destino;
    struct estacion* estacion;
    struct anden* anden;
    struct tren* next;
    struct tren* prev;
    struct tren* head;
};
typedef struct tren Tren;


Estacion* create_estacion(int id, int andenes);
Anden* create_anden(int id, Estacion* estacion);
Pasajero* create_pasajero(int  id, Anden*  anden,Estacion* estacion, Estacion* destino,  int tipo);
Tren* create_tren(int id, int vagones,  Estacion* estacion, Anden* anden);
Vagon* create_vagon(int id, int capacidad);
Asiento* create_asiento(int id);