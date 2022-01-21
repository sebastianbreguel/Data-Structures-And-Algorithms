#pragma once
#include <stdio.h>
#include "structs.h"

void update_tail(Anden* anden, Pasajero* new);
void update_head(Anden* anden, int tipo);
void print_row(FILE* output_file,Anden* anden);
void print_estacion(FILE* output_file, Estacion* estacion);
void free_memory(Estacion** estaciones, int N_STATIONS, Tren* head_train);
void free_type(Pasajero* actual);
void revisar_fila_premium(Tren* tren, Anden* anden);
int actualizar_asiento(Anden* anden, Pasajero* pasajero, Tren* tren);
void print_tren(FILE* output_file,Tren* tren,int motivo);
void revisar_fila_normal(Tren* tren ,Anden* anden);
void descender_pasajeros(Tren* tren, Estacion* llegada, Anden* anden);