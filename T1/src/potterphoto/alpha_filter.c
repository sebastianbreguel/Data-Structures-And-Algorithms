#include "alpha_filter.h"


void not_free(Neighborhood* neighborhood, int parent_include){
    Neighborhood* actual = neighborhood->head;
    if(parent_include == 1 && !neighborhood -> include){
        neighborhood -> include = parent_include;
    }
    
        while (actual != NULL){
            Neighborhood* next_neighborhood = actual->next;
            not_free(actual, neighborhood -> include);
            actual = next_neighborhood;
        }
    
}

void frees(Neighborhood* neighborhood) {
    Neighborhood* actual = neighborhood->head;

    while (actual != NULL)
    {
        Neighborhood* next_neighborhood = actual->next;
        frees(actual);
        actual = next_neighborhood;
    }    

    free(neighborhood->pixels);
    free(neighborhood);
}


float cost_neighborhood_notLeaf(Neighborhood* neighborhood, float alpha){
    

    Neighborhood* actual = neighborhood->head;
    if(!actual){
        if(alpha*(neighborhood -> n) < (1-alpha)*(neighborhood -> ps)){
            neighborhood-> cost = alpha*(neighborhood -> n);
            neighborhood -> include = 1;
        }
        else{
            neighborhood -> cost = ((1-alpha)*(neighborhood -> ps));

        }                

    } else{
        float value = 0;
        while (actual != NULL){
            Neighborhood* next_neighborhood = actual->next;

            value += cost_neighborhood_notLeaf(actual, alpha);
            actual = next_neighborhood;
        }
        
        if(alpha*( neighborhood -> n) < (1-alpha)*( neighborhood -> ps) + value ){
             neighborhood-> cost = alpha*( neighborhood -> n);
             neighborhood -> include = 1;
        } else{
            neighborhood -> cost = ((1-alpha)*( neighborhood-> ps)) + value ;
        }   
            
    }            

    return  neighborhood -> cost;
}