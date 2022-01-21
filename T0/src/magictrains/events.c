
#include "events.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


void update_tail(Anden* anden, Pasajero* new){ // se agrega alguien a la fila de espera del anden
    Pasajero* actual = NULL; // cabeza inicial
    if(new->tipo == 1){
        actual = anden-> head_normal;
    }
    else{
        actual = anden-> head_premium;
    }

    if  (actual != NULL){
        
         //  si hay  al menos una persona en el  anden
        actual->  tail -> next = new;
        actual -> tail = new;
        new-> head = actual;
        new -> tail = new;
    }
    else{// si hay no hay nadie  en el anden
        if(new-> tipo ==1){
        anden-> head_normal =new;
        anden-> head_normal -> head = new;
        anden-> head_normal -> tail = new;
        }
        else{
        anden-> head_premium =new;
        anden-> head_premium-> head = new;
        anden-> head_premium-> tail = new;
        }
    }
}

void update_head(Anden* anden, int tipo){ // la cabeza sube al tren y deja el anden
    Pasajero* cabeza;
    Pasajero* new_head;
    if(tipo == 1){
        cabeza = anden-> head_normal;
        new_head =  cabeza-> next;
            anden-> head_normal = new_head;
        }
        else{
            cabeza = anden-> head_premium;
            new_head =  cabeza-> next;
            anden-> head_premium = new_head;
        } 
    cabeza-> next = NULL;
    cabeza-> head = NULL;
    if(new_head != NULL){ // si  hay mas de una persona en el anden.
        new_head -> head = new_head;
       }
    else{// si solamente hay en la fila del anden
           if  (tipo == 1){
            anden-> head_normal= NULL;
        }
        else{
            anden-> head_premium= NULL;
        } 
    }
}



void revisar_fila_premium(Tren* tren ,Anden* anden){
    if(anden->head_premium != NULL){
        int encontrado = actualizar_asiento(anden,  anden-> head_premium, tren);
        if(encontrado == 1){
            update_head(anden, 0);
            revisar_fila_premium(tren,  anden);
        }
    }
    else{
    }
}
void revisar_fila_normal(Tren* tren ,Anden* anden){
    if(anden->head_normal != NULL){
        int encontrado = actualizar_asiento(anden,  anden-> head_normal, tren);
        if(encontrado == 1){

            update_head(anden, 1);                            

            revisar_fila_normal(tren,  anden);
        }
    }
}
int actualizar_asiento(Anden* anden, Pasajero* pasajero, Tren* tren){

    for(int numero_vagon = 0; numero_vagon < tren->total_vagones ; numero_vagon++){
        Vagon* actual_vagon = tren -> vagones[numero_vagon];
        int number_asiento = 0;
        while( number_asiento < actual_vagon-> n_asientos ){
            Asiento*  actual_asiento =  actual_vagon-> asientos[number_asiento];
            if(actual_asiento-> pasajero == NULL){
                actual_asiento -> pasajero = pasajero;
                pasajero -> estacion = NULL;
                return 1;
            }
            number_asiento = number_asiento + 1;
        }

    }
    return 0;
}

void descender_pasajeros(Tren* tren, Estacion* llegada, Anden* anden){
    for(int numero_vagon = 0; numero_vagon < tren->total_vagones ; numero_vagon++){
        Vagon* actual_vagon = tren -> vagones[numero_vagon];
        int number_asiento = 0;
        while( number_asiento < actual_vagon-> n_asientos ){
            Asiento*  actual_asiento =  actual_vagon-> asientos[number_asiento];
            if(actual_asiento-> pasajero != NULL && actual_asiento -> pasajero -> destino == llegada ){
                free(actual_asiento -> pasajero);
                actual_asiento -> pasajero = NULL;
            }
            number_asiento = number_asiento + 1;
        }


    }
    tren -> estacion =  llegada;
    anden -> tren = tren;

}



void free_memory(Estacion** estaciones, int N_STATIONS, Tren* actual){
    
  for (int s = 0; s < N_STATIONS; s++)
  {
      Estacion* actual_estacion = estaciones[s];
    for(int id = 0; id < actual_estacion->  cantidad_andenes; id++){
        Anden* anden_actual = actual_estacion-> andenes[id];
        free_type(anden_actual -> head_normal);
        free_type(anden_actual -> head_premium);
        free(anden_actual);
    }        
    free(actual_estacion-> andenes);
    free(actual_estacion);
  }
  free(estaciones);

  if(actual != NULL){
    free_train(actual-> head);
  }
}


void free_type(Pasajero* actual){
    if(actual != NULL){
        free_type(actual -> next);
        free(actual);

    }

}

void free_train(Tren* actual){
    if(actual !=NULL ){
        free_vagones(actual);
        free_train( actual-> next);
        free(actual);
    }
}

void free_vagones(Tren* actual){
    
        for(int n_vagon = 0; n_vagon < actual -> total_vagones; n_vagon++){
            Vagon* actual_vagon = actual -> vagones[n_vagon];
            
            for(int n_asiento = 0; n_asiento < actual_vagon -> n_asientos; n_asiento++){
                Asiento* actual_asiento = actual_vagon -> asientos[n_asiento];
                if(actual_asiento -> pasajero != NULL){
                    free(actual_asiento -> pasajero);
                }
                free(actual_asiento);
            }
            free(actual_vagon-> asientos);
            free(actual_vagon);
        }
        free(actual-> vagones);
}

void print_row(FILE* output_file, Anden* anden){
    Pasajero* actual = anden-> head_premium;
    
    fprintf(output_file,"A%i ",anden->id);
    while(actual != NULL){
        
        fprintf(output_file,"%i-%i-%i ",actual->id,actual->destino->id, actual-> tipo);
        actual = actual -> next;  
        };
     actual = anden-> head_normal;
    while(actual != NULL){
        fprintf(output_file,"%i-%i-%i ",actual->id,actual->destino->id, actual-> tipo);
        actual = actual -> next;  
        };
        fprintf( output_file,"\n");
}

void print_tren(FILE* output_file, Tren* tren,int motivo){
    if(motivo ==0){
    fprintf(output_file,"T%i |", tren->id);
    }
    else{
            fprintf(output_file,"T%i |", tren->id);
   }
    for(int vagon = 0; vagon < tren-> total_vagones; vagon++){  
        Vagon*  actual_vagon = tren ->  vagones[vagon];
        for(int asiento = 0;  asiento < actual_vagon-> n_asientos  ; asiento++){
            
            Asiento* actual_asiento = actual_vagon -> asientos[asiento];
            if(actual_asiento -> pasajero == NULL){
                        fprintf(output_file," X");
            }
            else{
                fprintf(output_file," %i-%i", actual_asiento-> pasajero -> id,  actual_asiento ->  pasajero -> destino -> id);
            }
        }
        
        fprintf(output_file, " |");
    }
        
        fprintf(output_file, "\n");

}

void print_estacion(FILE* output_file, Estacion* estacion){
    fprintf(output_file,"ESTACION %i\n", estacion->id);
    for(int anden=0; anden < estacion->cantidad_andenes; anden++){
        Anden* anden_actual = estacion->andenes[anden];
        print_row( output_file, anden_actual);
        if(anden_actual -> tren != NULL){
            print_tren( output_file, anden_actual -> tren,0);
        }
    }
}