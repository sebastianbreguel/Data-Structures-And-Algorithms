#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "events.h"

/* Retorna true si ambos strings son iguales */
bool string_equals(char *string1, char *string2)
{
  return !strcmp(string1, string2);
}

/* Revisa que los parametros del programa sean válidos */
bool check_arguments(int argc, char **argv)
{
  if (argc != 3)
  {
    printf("Modo de uso: %s INPUT OUTPUT\n", argv[0]);
    printf("Donde:\n");
    printf("\tINPUT es la ruta del archivo de input\n");
    printf("\tOUTPUT es la ruta del archivo de output\n");
    return false;
  }

  return true;
}

int main(int argc, char **argv)
{
/* Si los parámetros del programa son inválidos */
  if (!check_arguments(argc, argv))
  {
    /* Salimos del programa indicando que no terminó correctamente */
    return 1;
  }

  /* Abrimos el archivo de input */
  FILE *input_file = fopen(argv[1], "r");

  /* Abrimos el archivo de output */
  FILE *output_file = fopen(argv[2], "w");


  /* Leemos la cantidad de estaciones y andenes por estación*/
  int N_STATIONS;
  fscanf(input_file, "%d", &N_STATIONS);
  Estacion** Estaciones =  calloc(N_STATIONS, sizeof(Estacion*));
  int N_PLATFORMS;
  for (int s = 0; s < N_STATIONS; s++)
  {
    fscanf(input_file, "%d", &N_PLATFORMS);
    Estaciones[s] = create_estacion(s, N_PLATFORMS);

    Anden** andenes = calloc(N_PLATFORMS,  sizeof(Anden*));
    for(int id = 0; id < N_PLATFORMS; id++){
      andenes[id] = create_anden(id, Estaciones[s]);

    }
    Estaciones[s] -> andenes =  andenes;
   // print_estacion(Estaciones[s]);
    /*  [Por implementar] Creamos los andenes con la cantidad de andenes dada */
  }

  /* String para guardar la instrucción actual*/
  char command[32];

  /* Leemos la primera instrucción */
  fscanf(input_file, "%s", command);
  Tren* last_tren;
  Tren* last_created_tren;
  last_tren = NULL;
  int id_tren = 0;
  int id_pasajero = 0;
  /* Mientras la instrucción sea distinta a END */
  while(!string_equals(command, "END"))
  {
      int station_id, platform_id;
    /* [Por implementar] A continuación debes implementar cada evento */
    if (string_equals(command, "NUEVO-TREN"))
    {
      int station_id, platform_id, length, seats;
      fscanf(input_file, "%d %d %d", &station_id, &platform_id, &length);


      Estacion*  estacion =  Estaciones[station_id];
      Anden* anden =  (estacion-> andenes)[platform_id];
      Tren* actual_tren = create_tren(id_tren, length, estacion, anden);
      anden-> tren = actual_tren;
      Vagon** vagones = actual_tren -> vagones;

      for (int i = 0; i < length; i++)
      {
        fscanf(input_file, "%d", &seats);
        Vagon* actual_vagon = create_vagon(i, seats);
        vagones[i] = actual_vagon;
        Asiento** asientos  =  actual_vagon -> asientos;

        for (int id = 0; id < seats; id++){

        Asiento* asiento = create_asiento(id);

        asientos[id] = asiento;
        }
      }
      if (id_tren == 0){
        actual_tren -> head  = actual_tren;
        last_tren = actual_tren;
        last_created_tren = actual_tren;
      }
      else{
      actual_tren -> prev = last_created_tren;
      last_created_tren ->  next = actual_tren;
      actual_tren -> head = last_created_tren -> head;
      last_tren = actual_tren;
      last_created_tren = actual_tren;
      }
      
      id_tren = id_tren +1;
    revisar_fila_premium(last_tren, anden);
    }

    else if (string_equals(command, "PASAJERO"))
    {
      int station_id, platform_id, destination, category;
      fscanf(input_file, "%d %d %d %d", &station_id, &platform_id, &destination, &category);
      
      Estacion* estacion_pasajero = Estaciones[station_id];
      Estacion* destino_pasajero = Estaciones[destination];
      Anden* anden_pasajero = (estacion_pasajero->andenes)[platform_id];
      Pasajero* pasajero_actual =  create_pasajero(id_pasajero, anden_pasajero, estacion_pasajero, destino_pasajero, category);
      
      update_tail(anden_pasajero, pasajero_actual);
      id_pasajero = id_pasajero +1;
    if(anden_pasajero->tren !=NULL  && category == 0){
      revisar_fila_premium(anden_pasajero->tren, anden_pasajero);
    }
    }
    else if (string_equals(command, "REMOVER"))
    {
      int station_id, platform_id, car, seat;
      fscanf(input_file, "%d %d %d %d", &station_id, &platform_id, &car, &seat);
      Estacion* actual_estacion = Estaciones[station_id];
      Anden* actual_anden = actual_estacion -> andenes[platform_id];
      Vagon* actual_vagon = actual_anden->tren  -> vagones[car];
      Asiento* actual_asiento = actual_vagon -> asientos[seat] ;
      if(actual_asiento -> pasajero != NULL){
        Pasajero* removed_pasajero = actual_asiento -> pasajero;
        actual_asiento ->  pasajero = NULL;

            fprintf(output_file,"REMOVER %i %i\n", removed_pasajero->id, removed_pasajero->destino->id);

        free(removed_pasajero);
        revisar_fila_premium(actual_anden->tren, actual_anden);

      }
    }
    else if (string_equals(command, "SALIR"))
    {
      fscanf(input_file, "%d %d", &station_id, &platform_id);

    Estacion* actual_estacion = Estaciones[station_id];
    Anden* actual_anden = actual_estacion ->  andenes[platform_id];
    Tren* tren_anden = actual_anden -> tren;
    revisar_fila_normal(tren_anden, actual_anden);
    actual_anden -> tren = NULL;
    last_tren = tren_anden;

    }
    else if (string_equals(command, "LLEGAR"))
    {
      int station_id, platform_id;
      fscanf(input_file, "%d %d", &station_id, &platform_id);
Estacion* actual_estacion = Estaciones[station_id];
    Anden* actual_anden = actual_estacion ->  andenes[platform_id];
    
    fprintf(output_file,"LLEGAR ");
      print_tren(output_file, last_tren,1);
  descender_pasajeros(last_tren, actual_estacion, actual_anden);
    revisar_fila_premium(last_tren, actual_anden);


    }
    else if (string_equals(command, "DESAPARECER"))
    {     fprintf(output_file,"DESAPARECER ");

      print_tren(output_file, last_tren,1);



    }
    else if (string_equals(command, "SEPARAR"))
    {
      int station_id_1, platform_id_1, station_id_2, platform_id_2;
      fscanf(input_file, "%d %d %d %d", &station_id_1, &platform_id_1, &station_id_2, &platform_id_2);

      Estacion* estacion_1 = Estaciones[station_id_1];
      Estacion* estacion_2 = Estaciones[station_id_2];
      Anden* Anden_1 = estacion_1 -> andenes[platform_id_1];
      Anden* Anden_2 = estacion_2 -> andenes[platform_id_2];
      int total_andenes = last_tren  -> total_vagones  ;      
      double mitad_float = (float) total_andenes/2;
      double mitad_entera =  total_andenes/2;
      int anden_1 =  total_andenes/2;
      int anden_2 =  total_andenes/2;
      if(mitad_float > mitad_entera){
        anden_1 =  anden_1 + 1;
      }
      Tren* new_tren = create_tren(id_tren, anden_2, NULL, NULL);
      int iteracion = 0;
      Vagon** vagones_1 = calloc(anden_1,  sizeof(Vagon*));
      int num_1 = 0;
      int num_2 = 0;
      for(int numero = 0; numero <  last_tren-> total_vagones; numero++){
        Vagon* actual_vagon  = last_tren -> vagones[numero];
        if (iteracion ==0){
          iteracion =1;
          vagones_1[num_1] = actual_vagon;
          actual_vagon -> id = num_1;
          num_1 = num_1 + 1;
        } 
        else{
          iteracion =0;
          new_tren -> vagones[num_2] = actual_vagon;
          actual_vagon -> id = num_2;
          num_2 = num_2 + 1;
        }
      }
      Vagon**  borrar = last_tren -> vagones;    
      last_tren -> vagones = vagones_1;
      last_tren -> total_vagones = anden_1;
      free(borrar);
      id_tren = id_tren +1;
      fprintf(output_file,"LLEGAR ");
      print_tren(output_file, last_tren,1);
      descender_pasajeros(last_tren, estacion_1, Anden_1);
      revisar_fila_premium(last_tren, Anden_1);

      fprintf(output_file,"LLEGAR ");
      print_tren(output_file, new_tren ,1);
      descender_pasajeros( new_tren, estacion_2, Anden_2);
      revisar_fila_premium( new_tren, Anden_2);

      new_tren -> prev = last_created_tren;
      last_created_tren ->  next = new_tren;
      new_tren -> head = last_created_tren -> head;
      last_tren = new_tren;
      last_created_tren = new_tren;
    }
    else if (string_equals(command, "ESTACION"))
    {
      int station_id;
      fscanf(input_file, "%d", &station_id);
    print_estacion(output_file, Estaciones[station_id]);

    }

    /* Leemos la siguiente instrucción */
    fscanf(input_file, "%s", command);
    
  }

  for (int s = 0; s < N_STATIONS; s++)
  {
    print_estacion(output_file, Estaciones[s]);
    /*  [Por implementar] Creamos los andenes con la cantidad de andenes dada */


  }
    free_memory(Estaciones, N_STATIONS, last_tren);
  /*  [Por implementar] Liberamos nuestras estructuras */
  fclose(input_file);
  fclose(output_file);
  return 0;
  
}