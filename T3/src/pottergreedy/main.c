#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "set.h"
#include "lights.h"
#include "kruskal.h"
#include <time.h>

int main(int argc, char** argv)
{
    char* option;
    // Revisamos los argumentos
    if(argc < 4) {
        printf("Modo de uso: %s <A/B> <input.txt> <output.txt>\n", argv[0]);
        return 1;
    }

    // Abrimos el archivo de input
    FILE* input_stream = fopen(argv[2], "r");

    // Abrimos el archivo de output
    FILE* output_stream = fopen(argv[3], "w");

    // Si alguno de los dos archivos no se pudo abrir
    if(!input_stream)
    {
        printf("El archivo %s no existe o no se puede leer\n", argv[2]);
        return 2;
    }
    if(!output_stream)
    {
        printf("El archivo %s no se pudo crear o no se puede escribir\n", argv[2]);
        printf("Recuerda que \"fopen\" no puede crear carpetas\n");
        fclose(input_stream);
        return 3;
    }



    option = argv[1];
    if(strcmp(option, "A") == 0){
        // Parte 1 de la Tarea

         /* Lectura de input */

        int size; // Dimensiones de la grid
        int N; // N° de nodos
        int MST_cost; // Costo mínimo base
        
        fscanf(input_stream, "%d %d %d", &size, &N, &MST_cost);

        int row;
        int col;


        Punto* puntos =  (Punto*)calloc(N+10000, sizeof(Punto));
        // Obtenemos cada uno de los puntos
        for(int i = 0; i < N; i++) {
            fscanf(input_stream, "%d %d", &row, &col);
            puntos[i].id = i;
            puntos[i].x = col;
            puntos[i].y = row;
            }
        int edges_count = N*(N-1)/2;
        MST* mst1 = make_mst(N, edges_count);
        Arista* aristas1 = (Arista*)malloc(edges_count*sizeof(Arista));;

        create_aristas(mst1,aristas1, puntos);    
        int total = kruskal(mst1, aristas1, output_stream);
        inversePartition(aristas1, 0 , edges_count);
        int change= total*0.0563 ;
        int wenlo = 21;
        int  steps = 7;
        if(total < 40000){
            

        } else if(total < 60000){
            change = total*0.0173;
            wenlo = 512;

        } else{
            change = total*0.001;
            wenlo = 1107;
        }
        int actual_best = total;
        int total_1;
        int total_2;
        int total_3;
        MST* mst;
        Arista* aristas;
        while(total - change < actual_best){
            if((aristas1[wenlo].punto_a->x != aristas1[wenlo].punto_b->x)&& (aristas1[wenlo].punto_a->y != aristas1[wenlo].punto_b->y)){

                puntos[N].id = N;
                puntos[N].x = aristas1[wenlo].punto_a->x;
                puntos[N].y = aristas1[wenlo].punto_b->y;
                edges_count = (N+1)*((N+1)-1)/2;
                mst1 -> V = N+1;
                mst1 -> E = edges_count;
                aristas = (Arista*)malloc(edges_count*sizeof(Arista));
                create_aristas(mst1,aristas, puntos);    
                total_1 = kruskal(mst1,aristas, output_stream);                


                
                puntos[N].x = aristas1[wenlo].punto_b->x;
                puntos[N].y = aristas1[wenlo].punto_a->y;
                create_aristas(mst1,aristas, puntos);    
                total_2 = kruskal(mst1, aristas, output_stream);                

                free(aristas);

                if(total_1 < actual_best && total_1 < total_2){
                        puntos[N].x = aristas1[wenlo].punto_a->x;
                        puntos[N].y = aristas1[wenlo].punto_b->y;
                        actual_best = total_1;
                        N = N+  1;
                    } else if(total_2 < actual_best && total_2 < total_1){
                        actual_best = total_2;
                        N = N+  1;
                    } else if(total_1 < actual_best   && total_2 < actual_best ){
                        actual_best = total_2;
                        N = N+  1;
                        puntos[N].id = N;
                        puntos[N].x = aristas1[wenlo].punto_a->x;
                        puntos[N].y = aristas1[wenlo].punto_b->y;
                        edges_count = (N+1)*((N+1)-1)/2;
                        mst1 -> V = N+1;
                        mst1 -> E = edges_count;
                        aristas = (Arista*)malloc(edges_count*sizeof(Arista));
                        create_aristas(mst1,aristas, puntos);    
                        total_3 = kruskal(mst1,aristas, output_stream);                

                        free(aristas);
                        if(total_3 <  actual_best){
                            actual_best = total_3;
                            N = N +  1;

                        }   
                }
            }
            
        wenlo += steps;
        }    
        edges_count = (N)*((N)-1)/2;
        mst1 -> V = N;
        mst1 -> E = edges_count;
        aristas = (Arista*)malloc(edges_count*sizeof(Arista));
        create_aristas(mst1,aristas, puntos);    
        fprintf(output_stream ,"%d\n", N-1);
        kruskal_finished(mst1,aristas, output_stream);
        // printf(" \n%f, N:%d\n\n", (float)(inicial-total)/inicial,N);

        free(aristas);
        free(mst1);
        free(aristas1);
        free(puntos);

    }

    else if(strcmp(option, "B") == 0){
        // Parte 2 de la Tarea
        int N; // numero de nodos
        
        fscanf(input_stream, "%d", &N);

        int pos;
        char col;
        Luz* luces =  (Luz*)calloc(N, sizeof(Luz));

        // Obtenemos cada uno de los puntos
        for(int i = 0; i < N; i++)
        {
            fscanf(input_stream, "%d %c", &pos, &col);
            // printf("Posicion: %d, Color: %c\n", pos, col);
            luces[i].x = pos;
            luces[i].tipo = col;
            luces[i].id = i;
        }
        int count = 0;
        Luz anterior = luces[0];
        for(int light = 1; light <N;  light++){
            Luz actual = luces[light];
            // printf("%d-%c-%d\n", actual.x,actual.tipo,actual.tipo);
            if(actual.tipo == 98 || actual.tipo == 103){
                // fprintf(output_stream,"%d %c %d %c\n",anterior.x,anterior.tipo, actual.x, actual.tipo);
                count++;
                anterior = actual;
            }
        }
        anterior = luces[0];
        for(int light = 1; light <N;  light++){
            Luz actual = luces[light];
            // printf("%d-%c-%d\n", actual.x,actual.tipo,actual.tipo);
            if(actual.tipo == 114 || actual.tipo == 103){
                // fprintf(output_stream,"%d %c %d %c\n",anterior.x,anterior.tipo, actual.x, actual.tipo);
                count++;
                anterior = actual;
            }
        }

        fprintf(output_stream,"%d\n",count);

        anterior = luces[0];
        for(int light = 1; light <N;  light++){
            Luz actual = luces[light];
            // printf("%d-%c-%d\n", actual.x,actual.tipo,actual.tipo);
            if(actual.tipo == 98 || actual.tipo == 103){
                fprintf(output_stream,"%d %c %d %c\n",anterior.x,anterior.tipo, actual.x, actual.tipo);
                anterior = actual;
            }
        }
        anterior = luces[0];
        for(int light = 1; light <N;  light++){
            Luz actual = luces[light];
            // printf("%d-%c-%d\n", actual.x,actual.tipo,actual.tipo);
            if(actual.tipo == 114 || actual.tipo == 103){
                fprintf(output_stream,"%d %c %d %c\n",anterior.x,anterior.tipo, actual.x, actual.tipo);
                anterior = actual;
            }
        }
    }

    // Cerrar archivo de input
    fclose(input_stream);

    // Cerrar archivo de output
    fclose(output_stream);

    return 0;
}