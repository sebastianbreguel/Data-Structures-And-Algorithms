
#include "functions.h"



void all(FILE* input, FILE* output){

        /* Leemos primer largo */
        int initial_large;
        fscanf(input, "%d", &initial_large);

        /* Leemos primer ADN */
        char original_ADN[initial_large+1];
        fscanf(input, "%s", original_ADN);

        /* Leemos cantidad de querys */
        int querys ;
        fscanf(input, "%d", &querys);

        for(int query = 0; query < querys; query++){
                
                /* Leemos largo de query */
                int actual_large;
                fscanf(input, "%d", &actual_large);

                
                /* Leemos ADN de query */
                char sub[actual_large+1];
                fscanf(input, "%s", sub);

                for(int first =0 ; first< initial_large-actual_large+1; first++){
                        int* dic1 = malloc(26 * sizeof(int));
                        int* dic2 = malloc(26 * sizeof(int));
                        for(int i=0; i < 26; i++){
                                dic1[i] = 0;
                                dic2[i] = 0;
                        }
                        int exist =  1;
                        int number = 1;
                        for(int second = first; second <first+actual_large; ){          
                                if( dic1[sub[second-first]-65] == 0 && dic2[original_ADN[second]-65] == 0 ){
                                        dic1[sub[second-first]-65] = number;
                                        dic2[original_ADN[second]-65] = number; 
                                        number += 1;
                                }    
                                if(dic2[original_ADN[second]-65] != dic1[sub[second-first]-65]){
                                        exist = 0;
                                        break;
                                }
                                second ++;

                        }
                        free(dic1);
                        free(dic2);
                        if(exist){
                                // printf("position :%d termina en:%d %s\n", first, first + actual_large, sub);
                                fprintf(output,"%d %d\n", first, first + actual_large-1);
                                break;
                        }
                }
        
        }


}