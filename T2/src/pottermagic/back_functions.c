
#include "back_functions.h"


void printGrid(int grid[8][8], int sum_row[8], int sum_column[8])
{
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++){
            printf(" %2d ", grid[x][y]+1);
            if(y != 7){
                printf("-");
            }
        }
        printf("\n");
    }
    
}
void writeSolution(FILE *output_file, int sol[8][8]){
        for(int i = 0; i < 8; i++){
            for(int j = 0; j<8; j++){
                if(j == 7){
                    fprintf(output_file ,"%d\n", sol[i][j]+1);
                } else{
                    fprintf(output_file ,"%d ", sol[i][j]+1);
                }
            }  
        }
}



void solveProblem(FILE* output_file, int grid[8][8]){


// seteamos los posibles movimientos del caballo
        int xMove[8] = { -1, -2, 1, 2, -2,-1,  1, 2 };
         int yMove[8] = { -2,  1, 2,-1, -1, 2, -2, 1 };
        
        int values_column[64];
        int values_row[64];
        for(int i = 0; i<64; i++){
            values_column[i] = -1;
            values_row[i] = -1;
        }
        
        int sum_column[8] = {0};
        int sum_row[8] = {0};
        
        int sol[8][8] = {{ -1, -1, -1, -1, -1, -1, -1, -1},{ -1, -1, -1, -1, -1, -1, -1, -1},{ -1, -1, -1, -1, -1, -1, -1, -1},{ -1, -1, -1, -1, -1, -1, -1, -1},{ -1, -1, -1, -1, -1, -1, -1, -1},{ -1, -1, -1, -1, -1, -1, -1, -1},{ -1, -1, -1, -1, -1, -1, -1, -1},{ -1, -1, -1, -1, -1, -1, -1, -1}};
        for(int i = 0; i < 8; i++){
            for(int j = 0; j<8; j++){
                
                // leemos cada parte del tablero inicial
                int number = grid[i][j];

                if(number == 0){
                    sol[i][j] = 0;
                } 

                // seteamos el valor de la columna y fila de las posiciones iniciales
                if(number >= 0){
                    values_column[number] = j;
                    values_row[number] = i;
                    // sumamos los valores de suma de columnas y filas ddesde un principio
                    sum_column[j] += 1 + number;
                    sum_row[i] += 1 +  number;
                }
                // hacemos la suma inicial de la fila respectiva
            }  
        }
        doIt(1, values_column[0], values_row[0], values_column , values_row, xMove, yMove, sum_row, sum_column, sol, grid);

        writeSolution(output_file, sol);
}


int isInRange(int x, int y, int grid[8][8], int sol[8][8], int actual, int sum_row, int sum_column)
{
    return (x >= 0 && x < 8 && y >= 0 && y < 8
            && grid[y][x] == -1 && (sol[y][x] == -1 || sol[y][x] == actual )  && sum_row <=260 && sum_column <= 260   );
    
}


int doIt(int actual, int x_actual, int y_actual,int values_x[64], int values_y[64],
         int xMove[8], int yMove[8],int sum_row[8],int sum_column[8], int sol[8][8],int grid[8][8]){
    if (actual == 64){
        return 1;
    }
    if(values_x[actual] != -1){
        
        for(int option_actual = 0; option_actual < 8; option_actual++){
            // verificamos si las posiciones anteriores con algun posible movimientoe siguiente calzan
            if(x_actual + xMove[option_actual] == values_x[actual] &&  y_actual +yMove[option_actual] == values_y[actual]){
                sol[values_y[actual]][values_x[actual]] = actual;

                if (doIt( actual+1, values_x[actual], values_y[actual], values_x, values_y, xMove,  yMove, sum_row, sum_column,  sol, grid)){
                    return 1;
                    } 
                sol[values_y[actual]][values_x[actual]] = -1;

                return 0;
                
                } 
            } 
                 
             
            return 0;
        
    } else{
        
        for(int option_actual = 0; option_actual < 8; option_actual++){
            
            // registramos las nuevas posiciones
            int next_x = xMove[option_actual] + x_actual;
            int next_y = yMove[option_actual] + y_actual;


            if(isInRange(next_x, next_y, sol, grid, actual, sum_row[next_y] +1 +actual, sum_column[next_x]+ 1+actual )){
                sum_column[next_x] += (1 + actual);
                sum_row[next_y] += (1 + actual);
                 
                sol[next_y][next_x] = actual;
                if (doIt( actual+1,  next_x,  next_y, values_x, values_y, xMove,  yMove, sum_row, sum_column,  sol, grid)){
                    return 1;
                    } 
                sol[next_y][next_x] = -1;
                sum_column[next_x] -= (1 + actual);
                sum_row[next_y] -= (1 + actual);
                    
                }
            } 
        return 0;
    }

}