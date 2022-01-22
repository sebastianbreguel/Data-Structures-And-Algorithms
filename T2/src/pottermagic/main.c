#include "functions.h"
#include "back_functions.h"

int main(int argc, char** argv)
{
    char* option;
    // Revisamos los argumentos
    if(argc < 4) {
        printf("Modo de uso: %s <A/B> <input.txt> <output.txt>\n", argv[0]);
        return 1;
    }
    option = argv[1];
    if(strcmp(option, "A") == 0){
        // Parte 1 de la Tarea

        /* Abrimos el archivo de input */
        FILE *input_file = fopen(argv[2], "r");

        /* Abrimos el archivo de output */
        FILE *output_file = fopen(argv[3], "w");
        
        all(input_file, output_file);
        fclose(input_file);
        fclose(output_file);
    
    }

    else if(strcmp(option, "B") == 0){
        // Parte 2 de la Tarea
        
        /* Abrimos el archivo de input */
        FILE *input_file = fopen(argv[2], "r");

        /* Abrimos el archivo de output */
        FILE *output_file = fopen(argv[3], "w");


        int grid[8][8];

        for(int i = 0; i < 8; i++){
            for(int j = 0; j<8; j++){
                
                // leemos cada parte del tablero inicial
                int number;
                if(fscanf(input_file, "%d", &number)){
                    grid[i][j] = number - 1;
                }

            }  
        }


        solveProblem(output_file, grid);
        // findSolution(grid ,forming);
        // for(int i = 0 ; i<  64; i++){
        //     printf("%d-> x:%d y:%d\n",i+1, values_column[i], values_row[i]);
        // }

        fclose(input_file);
        fclose(output_file);
    }

    return 0;
}