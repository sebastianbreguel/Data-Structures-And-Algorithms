#include "structs.h"


Pixel* create_pixel(int id, int colour){
    Pixel* pixel = malloc(sizeof(Pixel));
    
    *pixel = (Pixel){
    pixel -> id = id, 
    pixel -> colour = colour,
    pixel -> check = 0,
    pixel -> include = 0,
    pixel -> up = NULL,
    pixel -> down = NULL,
    pixel -> left = NULL,
    pixel -> right = NULL,
    pixel -> neigh_node = NULL,
    };
    return pixel;
}



Neighborhood* create_neighborhood(int neighborhood_size, int colour, Neighborhood* parent, Pixel** pixels, Image* marker) {
    Neighborhood* neighborhood = malloc(sizeof(Neighborhood));

   *neighborhood = (Neighborhood) {
        neighborhood -> ps = 0,
        neighborhood -> n = 0,
        neighborhood -> cost = 0,
        neighborhood -> neighborhood_size = neighborhood_size,
        neighborhood -> include = 0,
        neighborhood -> colour = colour,
        neighborhood -> pixels = pixels,
        neighborhood -> head = NULL,
        neighborhood -> tail = NULL,
        neighborhood -> next = NULL,
        neighborhood -> parent = parent,
   };
    for(int id = 0; id < neighborhood_size;id++){
        Pixel* pixel = neighborhood->pixels[id];
        pixel -> neigh_node = neighborhood;
        int marker_pixel = marker-> pixels[pixel->id];
        if(pixel -> colour == colour){
            if((marker_pixel)){
                neighborhood -> ps +=1;
            }
        }
        if((!marker_pixel)){
            neighborhood -> n +=1;

        }
    }

   return neighborhood;
}

