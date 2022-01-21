#include "component_tree.h"


void poblar_img(Pixel** pixeles, Image* nueva, int R){
    int size = nueva->pixel_count;
    if(R !=1){
        for(int i=0; i< size; i++){
            if(pixeles[i]-> neigh_node-> include && pixeles[i]->colour ){
            nueva->pixels[i] = pixeles[i]->colour;        
            }
        } 
    }else {
        for(int i=0; i< size; i++){
            if(pixeles[i]-> neigh_node-> include && pixeles[i]->colour ){
            nueva->pixels[i]  =  127 -pixeles[i]->colour;
            }
        } 
    }
}

Pixel** populate_pixels(Image* image, int* base_colour) {
    int min_colour = 128;

    int width = image->width;
    int total_size = image->pixel_count;
    Pixel** new_pixels = calloc(total_size , sizeof(Pixel*));
    for (int id=0; id < total_size; id++){
        new_pixels[id] = create_pixel( id,image->pixels[id]);
            if ( image->pixels[id] < min_colour){
                min_colour = image->pixels[id];
        }
    }
    base_colour[0] = min_colour;
    for (int id = 0; id < total_size; id++) {
        int id_pixel = new_pixels[id]-> id; 
        // No estoy a al izquierda 
        if (id_pixel % width != 0) {
            new_pixels[id]->left = new_pixels[id - 1];
        }
        // No estoy a la derecha
        if ((id_pixel + 1) % width != 0) {
            new_pixels[id]->right = new_pixels[id + 1];
        }
        // No estoy en la primera fila
        if (id_pixel - width >= 0) {
            new_pixels[id]->up = new_pixels[id - width];
        }
        // No estoy abajo 
        if ((id + width )< total_size) {
            new_pixels[id]->down = new_pixels[id + width];
        }
    }
    return new_pixels;
}




Neighborhood* create_tree(Image* image, Image* marker){
    
    int* base_colour = malloc(sizeof(int));
    Pixel** pixels = populate_pixels(image, base_colour);
    int total_pixels = image-> pixel_count;
    int base = base_colour[0];
    Neighborhood* neighborhood_base = create_neighborhood(total_pixels, base, NULL, pixels, marker);
    free(base_colour);
    dowhill(neighborhood_base, marker);
    return neighborhood_base;
}



void connect_parent(Neighborhood* parent, Neighborhood* actual){

    if (parent->head == NULL) {
        parent->head = actual;
        parent->tail = actual;
    }
    else {
        (parent->tail)->next = actual;
    }

    parent->tail = actual;
    
}

void dowhill(Neighborhood* neight, Image* marker){
    int size_neight = neight -> neighborhood_size;
    int base_colour = neight -> colour;
    for (int id = 0; id < size_neight; id++){
        Pixel* pixel = neight->pixels[id];

        if (pixel -> colour > base_colour && pixel-> neigh_node == neight){
            int size_neight = neight -> neighborhood_size;
            int pixels_neighs = 0;

            pixels_neighs = neighs_count_create(base_colour, pixel, pixels_neighs);

            Pixel** neighborhood_pixels = calloc(pixels_neighs, sizeof(Pixel*));


            pixels_neighs = 0;
            int min_colour = 128;

            for(int id2 = 0; id2 <size_neight ; id2++){

                Pixel* pixel = neight -> pixels[id2];

                if(pixel -> check == 1){
                    neighborhood_pixels[pixels_neighs] = pixel;
                    pixel-> check = 0;
                    pixels_neighs +=1;

                    if(pixel-> colour < min_colour ){
                        min_colour = pixel-> colour;
                    }
                }
            }  

            Neighborhood* son =  create_neighborhood(pixels_neighs, min_colour, neight, neighborhood_pixels, marker);
            connect_parent(neight, son);
            dowhill(son, marker);
            }
        }
    }

    



int neighs_count_create(int colour_neight, Pixel* initial_pixel, int pixels_neighs) {

    initial_pixel->check = 1;
    pixels_neighs +=1;


    Pixel* right = initial_pixel->right;
    if (right &&  right-> colour > colour_neight &&!right->check) { //first
        right->check = 1;
        pixels_neighs +=1;

        if( right->right){//second
            Pixel* right_right = right->right;
            if( right_right-> colour > colour_neight && !right_right->check) { 
                    right_right->check = 1;
                    pixels_neighs +=1; 
                    if( right_right->right){//third
                        Pixel* right_right_right = right_right->right;
                        if( right_right_right-> colour > colour_neight && !right_right_right->check) {
                            pixels_neighs = neighs_count_create(colour_neight, right_right_right, pixels_neighs);
                        }
                    }  
                    if( right_right->up){//third
                        Pixel* right_right_up = right_right->up;
                        if( right_right_up-> colour > colour_neight && !right_right_up->check) {         
                            right_right_up->check = 1;
                            pixels_neighs +=1; 
                            if( right_right_up->right){//four
                                Pixel* right_right_up_right =right_right_up->right;
                                if( right_right_up_right-> colour > colour_neight && !right_right_up_right->check) {                            
                                    pixels_neighs = neighs_count_create(colour_neight, right_right_up_right, pixels_neighs);

                                }
                            }  
                            if( right_right_up->up){//four
                                Pixel* right_right_up_up = right_right_up->up;
                                if( right_right_up_up-> colour > colour_neight && !right_right_up_up->check) {
                                    pixels_neighs = neighs_count_create(colour_neight, right_right_up_up, pixels_neighs);
                                }
                            }    
                            if( right_right_up->left){//four
                                Pixel* right_right_up_left = right_right_up->left;
                                if( right_right_up_left-> colour > colour_neight && !right_right_up_left->check) {
                                    pixels_neighs = neighs_count_create(colour_neight, right_right_up_left, pixels_neighs);
                                }
                            }         
                        }
                    }      
                    if( right_right->down){//third
                        Pixel* right_right_down = right_right->down;
                        if( right_right_down-> colour > colour_neight && !right_right_down->check) {    
                            right_right_down->check = 1;
                            pixels_neighs +=1; 
                            if( right_right_down->right){//four
                                Pixel* right_right_down_right =right_right_down->right;
                                if( right_right_down_right-> colour > colour_neight && !right_right_down_right->check) {                            
                                    pixels_neighs = neighs_count_create(colour_neight, right_right_down_right, pixels_neighs);
                                }
                            }    
                            if( right_right_down->left){//four
                                Pixel* right_right_down_left = right_right_down->left;
                                if( right_right_down_left-> colour > colour_neight && !right_right_down_left->check) {
                                    pixels_neighs = neighs_count_create(colour_neight, right_right_down_left, pixels_neighs);
                                }
                            }    
                            if( right_right_down->down){//four
                                Pixel* right_right_down_down = right_right_down->down;
                                if( right_right_down_down-> colour > colour_neight && !right_right_down_down->check) {
                                    pixels_neighs = neighs_count_create(colour_neight,right_right_down_down, pixels_neighs);
                                }
                            }      
                        }
                    }                            

            }
        }
        
        if( right->up){//second
            Pixel* right_up = right->up;
            if( right_up-> colour > colour_neight && !right_up->check) {
                    right_up->check = 1;
                    pixels_neighs +=1; 
                    if( right_up->right){//third
                        Pixel* right_up_right = right_up->right;
                        if( right_up_right -> colour > colour_neight && !right_up_right ->check) {           
                            right_up_right->check = 1;
                            pixels_neighs +=1; 
                            if( right_up_right->right){//four
                                Pixel* right_up_right_right =right_up_right->right;
                                if( right_up_right_right-> colour > colour_neight && !right_up_right_right->check) {                            
                                    pixels_neighs = neighs_count_create(colour_neight, right_up_right_right, pixels_neighs);

                                }
                            }  
                            if( right_up_right->up){//four
                                Pixel* right_up_right_up = right_up_right->up;
                                if( right_up_right_up-> colour > colour_neight && !right_up_right_up->check) {
                                    pixels_neighs = neighs_count_create(colour_neight, right_up_right_up, pixels_neighs);
                                }
                            }    
                            if( right_up_right->down){//four
                                Pixel* right_up_right_down = right_up_right->down;
                                if( right_up_right_down-> colour > colour_neight && !right_up_right_down->check) {
                                    pixels_neighs = neighs_count_create(colour_neight, right_up_right_down, pixels_neighs);
                                }
                            }         

                        }
                    }  
                    if( right_up->up){//third
                        Pixel* right_up_up = right_up->up;
                        if( right_up_up-> colour > colour_neight && !right_up_up->check) {   
                            right_up_up->check = 1;
                            pixels_neighs +=1; 
                            if( right_up_up->right){//four
                                Pixel* right_up_up_right =right_up_up->right;
                                if( right_up_up_right-> colour > colour_neight && !right_up_up_right->check) {                            
                                    pixels_neighs = neighs_count_create(colour_neight, right_up_up_right, pixels_neighs);

                                }
                            }  
                            if( right_up_up->up){//four
                                Pixel* right_up_up_up = right_up_up->up;
                                if( right_up_up_up-> colour > colour_neight && !right_up_up_up->check) {
                                    pixels_neighs = neighs_count_create(colour_neight, right_up_up_up, pixels_neighs);
                                }
                            }    
                            if( right_up_up->left){//four
                                Pixel* right_up_up_left = right_up_up->left;
                                if( right_up_up_left-> colour > colour_neight && !right_up_up_left->check) {
                                    pixels_neighs = neighs_count_create(colour_neight, right_up_up_left, pixels_neighs);
                                }
                            }         
                        }
                    }    
                    if( right_up->left){//third
                        Pixel* right_up_left = right_up->left;
                        if( right_up_left-> colour > colour_neight && !right_up_left->check) {
                            right_up_left->check = 1;
                            pixels_neighs +=1; 
                            if( right_up_left->up){//four
                                Pixel* right_up_left_up = right_up_left->up;
                                if( right_up_left_up-> colour > colour_neight && !right_up_left_up->check) {
                                    pixels_neighs = neighs_count_create(colour_neight, right_up_left_up, pixels_neighs);
                                }
                            }    
                            if( right_up_left->left){//four
                                Pixel* right_up_left_left = right_up_left->left;
                                if( right_up_left_left-> colour > colour_neight && !right_up_left_left->check) {
                                    pixels_neighs = neighs_count_create(colour_neight, right_up_left_left, pixels_neighs);
                                }
                            } 
                        }
                    }                               
            }
        }

        if( right->down){//second
            Pixel* right_down = right->down;
            if( right_down-> colour > colour_neight && !right_down->check) {
                    right_down->check = 1;
                    pixels_neighs +=1; 
                    if( right_down->right){//third
                        Pixel* right_down_right = right_down->right;
                        if( right_down_right-> colour > colour_neight && !right_down_right->check) {      
                            right_down_right->check = 1;
                            pixels_neighs +=1; 
                            if( right_down_right->right){//four
                                Pixel* right_down_right_right =right_down_right->right;
                                if( right_down_right_right-> colour > colour_neight && !right_down_right_right->check) {                            
                                    pixels_neighs = neighs_count_create(colour_neight, right_down_right_right, pixels_neighs);

                                }
                            }  
                            if( right_down_right->up){//four
                                Pixel* right_down_right_up = right_down_right->up;
                                if( right_down_right_up-> colour > colour_neight && !right_down_right_up->check) {
                                    pixels_neighs = neighs_count_create(colour_neight, right_down_right_up, pixels_neighs);
                                }
                            }    
                            if( right_down_right->down){//four
                                Pixel* right_down_right_down =right_down_right->down;
                                if( right_down_right_down-> colour > colour_neight && !right_down_right_down->check) {
                                    pixels_neighs = neighs_count_create(colour_neight,right_down_right_down, pixels_neighs);
                                }
                            }      

                        }
                    }  
                    if( right_down->left){//third
                        Pixel* right_down_left = right_down->left;
                        if( right_down_left-> colour > colour_neight && !right_down_left->check) {  
                            right_down_left->check = 1;
                            pixels_neighs +=1; 
                            if( right_down_left->left){//four
                                Pixel* right_down_left_left = right_down_left->left;
                                if( right_down_left_left-> colour > colour_neight && !right_down_left_left->check) {
                                    pixels_neighs = neighs_count_create(colour_neight, right_down_left_left, pixels_neighs);
                                }
                            }    
                            if( right_down_left->down){//four
                                Pixel* right_down_left_down =right_down_left->down;
                                if( right_down_left_down-> colour > colour_neight && !right_down_left_down->check) {
                                    pixels_neighs = neighs_count_create(colour_neight,right_down_left_down, pixels_neighs);
                                }
                            }      
                        }
                    }    
                    if( right_down->down){//third
                        Pixel* right_down_down = right_down->down;
                        if( right_down_down-> colour > colour_neight && !right_down_down->check) {  
                            right_down_down->check = 1;
                            pixels_neighs +=1; 
                            if( right_down_down->right){//four
                                Pixel* right_down_down_right =right_down_down->right;
                                if( right_down_down_right-> colour > colour_neight && !right_down_down_right->check) {                            
                                    pixels_neighs = neighs_count_create(colour_neight, right_down_down_right, pixels_neighs);

                                }
                            }  
                            if( right_down_down->left){//four
                                Pixel* right_down_down_left = right_down_down->left;
                                if( right_down_down_left-> colour > colour_neight && !right_down_down_left->check) {
                                    pixels_neighs = neighs_count_create(colour_neight, right_down_down_left, pixels_neighs);
                                }
                            }    
                            if( right_down_down->down){//four
                                Pixel* right_down_down_down =right_down_down->down;
                                if( right_down_down_down-> colour > colour_neight && !right_down_down_down->check) {
                                    pixels_neighs = neighs_count_create(colour_neight,right_down_down_down, pixels_neighs);
                                }
                            }      
                        }
                    }   
                
            }
        }

    }


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    Pixel* left = initial_pixel->left;
    if (left && left-> colour > colour_neight && !left->check) {//first
        left->check = 1;
        pixels_neighs +=1;

      
        
        if( left->up){//second
        Pixel* left_up = left->up;
            if( left_up-> colour > colour_neight && !left_up->check) {
                    left_up->check = 1;
                    pixels_neighs +=1; 
                    if( left_up->right){//third
                        Pixel*  left_up_right = left_up->right;
                        if(  left_up_right-> colour > colour_neight && ! left_up_right->check) {              
                            left_up_right->check = 1;
                            pixels_neighs +=1; 
                            if( left_up_right->right){//four
                                Pixel* left_up_right_right =left_up_right->right;
                                if( left_up_right_right-> colour > colour_neight && !left_up_right_right->check) {                            
                                    pixels_neighs = neighs_count_create(colour_neight, left_up_right_right, pixels_neighs);

                                }
                            }  

                            if( left_up_right->up){//four
                                Pixel* left_up_right_up = left_up_right->up;
                                if( left_up_right_up-> colour > colour_neight && !left_up_right_up->check) {
                                    pixels_neighs = neighs_count_create(colour_neight, left_up_right_up, pixels_neighs);
                                }
                            }    
   
                        }
                    }  
                    if( left_up->up){//third
                        Pixel*  left_up_up = left_up->up;
                        if(  left_up_up-> colour > colour_neight && !left_up_up->check) {           
                            left_up_up->check = 1;
                            pixels_neighs +=1; 
                            if( left_up_up->right){//four
                                Pixel* left_up_up_right =left_up_up->right;
                                if( left_up_up_right-> colour > colour_neight && !left_up_up_right->check) {                            
                                    pixels_neighs = neighs_count_create(colour_neight, left_up_up_right, pixels_neighs);

                                }
                            }  

                            if( left_up_up->up){//four
                                Pixel* left_up_up_up = left_up_up->up;
                                if( left_up_up_up-> colour > colour_neight && !left_up_up_up->check) {
                                    pixels_neighs = neighs_count_create(colour_neight, left_up_up_up, pixels_neighs);
                                }
                            }    
                            if( left_up_up->left){//four
                                Pixel* left_up_up_left = left_up_up->left;
                                if( left_up_up_left-> colour > colour_neight && !left_up_up_left->check) {
                                    pixels_neighs = neighs_count_create(colour_neight,left_up_up_left, pixels_neighs);
                                }
                            }      
                        }
                    }    
                    if( left_up->left){//third
                        Pixel*  left_up_left = left_up->left;
                        if(  left_up_left-> colour > colour_neight && !left_up_left->check) {      
                            left_up_left->check = 1;
                            pixels_neighs +=1; 
                            if( left_up_left->left){//four
                                Pixel* left_up_left_left =left_up_left->left;
                                if( left_up_left_left-> colour > colour_neight && !left_up_left_left->check) {                            
                                    pixels_neighs = neighs_count_create(colour_neight, left_up_left_left, pixels_neighs);

                                }
                            }  

                            if( left_up_left->up){//four
                                Pixel* left_up_left_up = left_up_left->up;
                                if( left_up_left_up-> colour > colour_neight && !left_up_left_up->check) {
                                    pixels_neighs = neighs_count_create(colour_neight, left_up_left_up, pixels_neighs);
                                }
                            }    
                            if( left_up_left->down){//four
                                Pixel* left_up_left_down = left_up_left->down;
                                if( left_up_left_down-> colour > colour_neight && !left_up_left_down->check) {
                                    pixels_neighs = neighs_count_create(colour_neight,left_up_left_down, pixels_neighs);
                                }
                            }      


                        }
                    }       
            }
        }

        if( left->down){//second
        Pixel* left_down = left->down;
            if( left_down-> colour > colour_neight && !left_down->check) {
                    left_down ->check = 1;
                    pixels_neighs +=1; 
                    if( left_down->right){//third
                        Pixel*  left_down_right = left_down->right;
                        if(  left_down_right-> colour > colour_neight && ! left_down_right->check) {         
                            left_down_right->check = 1;
                            pixels_neighs +=1; 
                            if( left_down_right->right){//four
                                Pixel* left_down_right_right =left_down_right->right;
                                if( left_down_right_right-> colour > colour_neight && !left_down_right_right->check) {                            
                                    pixels_neighs = neighs_count_create(colour_neight, left_down_right_right, pixels_neighs);

                                }
                            }  
                            if( left_down_right->down){//four
                                Pixel* left_down_right_down = left_down_right->down;
                                if( left_down_right_down-> colour > colour_neight && !left_down_right_down->check) {
                                    pixels_neighs = neighs_count_create(colour_neight,left_down_right_down, pixels_neighs);
                                }
                            }      

                        }
                    }  
                    if( left_down->left){ //third
                        Pixel*  left_down_left = left_down->left;
                        if(  left_down_left-> colour > colour_neight && ! left_down_left->check) {          
                            left_down_left->check = 1;
                            pixels_neighs +=1; 
                            if( left_down_left->down){//four
                                Pixel* left_down_left_down =left_down_left->down;
                                if( left_down_left_down-> colour > colour_neight && !left_down_left_down->check) {                            
                                    pixels_neighs = neighs_count_create(colour_neight, left_down_left_down, pixels_neighs);

                                }
                            }  
                            if( left_down_left->up){//four
                                Pixel* left_down_left_up = left_down_left->up;
                                if( left_down_left_up-> colour > colour_neight && !left_down_left_up->check) {
                                    pixels_neighs = neighs_count_create(colour_neight, left_down_left_up, pixels_neighs);
                                }
                            }    
                            if( left_down_left->left){//four
                                Pixel* left_down_left_left = left_down_left->left;
                                if( left_down_left_left-> colour > colour_neight && !left_down_left_left->check) {
                                    pixels_neighs = neighs_count_create(colour_neight,left_down_left_left, pixels_neighs);
                                }
                            }
                        }
                    }    
                    if( left_down->down){ //third
                        Pixel*  left_down_down = left_down ->down;
                        if(  left_down_down-> colour > colour_neight && ! left_down_down->check) {
                            pixels_neighs = neighs_count_create(colour_neight,  left_down_down, pixels_neighs);
                        }
                    }       
            }
        }

        if( left->left){//second
        Pixel* left_left= left->left;
            if( left_left-> colour > colour_neight && !left_left->check) {
                    left_left ->check = 1;
                    pixels_neighs +=1; 
                    if( left_left->up){//third
                        Pixel*  left_left_up = left_left->up;
                        if(  left_left_up-> colour > colour_neight && ! left_left_up->check) {
                            pixels_neighs = neighs_count_create(colour_neight,  left_left_up, pixels_neighs);
                        }
                    }    
                    if( left_left ->left){//third
                        Pixel*  left_left_left = left_left ->left;
                        if(  left_left_left-> colour > colour_neight && ! left_left_left->check) {
                            pixels_neighs = neighs_count_create(colour_neight,  left_left_left, pixels_neighs);
                        }
                    }    
                    if( left_left->down){ //third
                        Pixel*  left_left_down = left_left ->down;
                        if(  left_left_down-> colour > colour_neight && ! left_left_down->check) {
                            pixels_neighs = neighs_count_create(colour_neight,  left_left_down, pixels_neighs);
                        }
                    }  
            }
        }
    }  
        
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Pixel* up = initial_pixel->up;

    if(up && up-> colour > colour_neight && !up->check) {//first
        up->check = 1;
        pixels_neighs +=1;
                
        if( up->right){//second
            Pixel* up_right = up->right;
            if( up_right-> colour > colour_neight &&  !up_right->check) {



                    up_right->check = 1;
                    pixels_neighs +=1; 
                    if( up_right->right){ //third
                        Pixel* up_right_right = up_right->right;
                        if( up_right_right-> colour > colour_neight && !up_right_right->check) {                            
                            pixels_neighs = neighs_count_create(colour_neight, up_right_right, pixels_neighs);

                        }
                    }  
                    if( up_right->up){//third
                        Pixel* up_right_up = up_right->up;
                        if( up_right_up-> colour > colour_neight && !up_right_up->check) {
                            pixels_neighs = neighs_count_create(colour_neight, up_right_up, pixels_neighs);
                        }
                    }      
                    if( up_right->down){//third
                        Pixel* up_right_down = up_right->down;
                        if( up_right_down-> colour > colour_neight && !up_right_down->check) {
                            pixels_neighs = neighs_count_create(colour_neight, up_right_down, pixels_neighs);
                        }
                    }       

            }
        }

        if( up->up){//second
            Pixel* up_up = up->up;
            if( up_up-> colour > colour_neight &&  !up_up->check) {

                up_up->check = 1;
                pixels_neighs +=1; 
                if( up_up->right){//third
                    Pixel* up_up_right = up_up->right;
                    if( up_up_right-> colour > colour_neight && !up_up_right->check) {                            
                        pixels_neighs = neighs_count_create(colour_neight, up_up_right, pixels_neighs);

                    }
                }  
                if( up_up->up){//third
                    Pixel* up_up_up = up_up->up;
                    if( up_up_up-> colour > colour_neight && !up_up_up->check) {
                        pixels_neighs = neighs_count_create(colour_neight, up_up_up, pixels_neighs);
                    }
                }    
                if( up_up->left){//third
                    Pixel* up_up_left = up_up->left;
                    if( up_up_left-> colour > colour_neight && !up_up_left->check) {
                        pixels_neighs = neighs_count_create(colour_neight, up_up_left, pixels_neighs);
                    }
                }    
            }
        }
        if( up->left){//second
            Pixel* up_left= up->left;
            if( up_left-> colour > colour_neight && !up_left->check) {
                    up_left->check = 1;
                    pixels_neighs +=1; 
                    if( up_left->up){//third
                        Pixel* up_left_up = up_left->up;
                        if( up_left_up-> colour > colour_neight && !up_left_up->check) {
                            pixels_neighs = neighs_count_create(colour_neight, up_left_up, pixels_neighs);
                        }
                    }    
                    if( up_left->left){//third
                        Pixel* up_left_left = up_left->left;
                        if( up_left_left-> colour > colour_neight && !up_left_left->check) {
                            pixels_neighs = neighs_count_create(colour_neight, up_left_left, pixels_neighs);
                        }
                    }    
                    if( up_left->down){//third
                        Pixel* up_left_down = up_left->down;
                        if( up_left_down-> colour > colour_neight && !up_left_down->check) {
                            pixels_neighs = neighs_count_create(colour_neight, up_left_down, pixels_neighs);
                        }
                    }  
            }
        }
    }
        


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Pixel* down = initial_pixel->down;
    if (down && down-> colour> colour_neight && !down->check) {//first
        down->check = 1;
        pixels_neighs +=1;
            if( down->right){//second
            Pixel* down_right = down->right;
                if( down_right-> colour > colour_neight && !down_right->check) {
                    down_right->check = 1;
                    pixels_neighs +=1; 
                    if(down_right->right){//third
                        Pixel*  down_right_right = down_right->right;
                        if(  down_right_right -> colour > colour_neight && ! down_right_right ->check) {     
                            down_right_right->check = 1;
                            pixels_neighs +=1; 
                            if( down_right_right->right){//four
                                Pixel* down_right_right_right =down_right_right->right;
                                if( down_right_right_right -> colour > colour_neight && !down_right_right_right->check) {                            
                                    pixels_neighs = neighs_count_create(colour_neight, down_right_right_right, pixels_neighs);

                                }
                            }  

                            if( down_right_right->up){//four
                                Pixel* down_right_right_up = down_right_right->up;
                                if( down_right_right_up-> colour > colour_neight && !down_right_right_up->check) {
                                    pixels_neighs = neighs_count_create(colour_neight, down_right_right_up, pixels_neighs);
                                }
                            }    
                            if( down_right_right->down){//four
                                Pixel* down_right_right_down =down_right_right->down;
                                if( down_right_right_down-> colour > colour_neight && !down_right_right_down->check) {
                                    pixels_neighs = neighs_count_create(colour_neight,down_right_right_down, pixels_neighs);
                                }
                            }      

                        }
                    }  
                    if( down_right->up){//third
                        Pixel*  down_right_up = down_right->up;
                        if(  down_right_up -> colour > colour_neight && ! down_right_up ->check) {
                            pixels_neighs = neighs_count_create(colour_neight,  down_right_up , pixels_neighs);
                        }
                    }    
                    if(down_right->down){//third
                        Pixel*  down_right_down = down_right->down;
                        if(  down_right_down-> colour > colour_neight && ! down_right_down->check) {
                            pixels_neighs = neighs_count_create(colour_neight,  down_right_down, pixels_neighs);
                        }
                    }  
                }
            }
            if( down->down){//second
            Pixel* down_down = down->down;
                if( down_down-> colour > colour_neight &&!down_down->check) {
                    down_down->check = 1;
                    pixels_neighs +=1; 
                    if(down_down->right){//third
                        Pixel*  down_down_right = down_down->right;
                        if(  down_down_right -> colour > colour_neight && !down_down_right ->check) {                            
                            pixels_neighs = neighs_count_create(colour_neight,  down_down_right , pixels_neighs);
                        }
                    }  
                    if( down_down->left){//third
                        Pixel*  down_down_left = down_down->left;
                        if(  down_down_left-> colour > colour_neight && ! down_down_left->check) {
                            pixels_neighs = neighs_count_create(colour_neight,  down_down_left, pixels_neighs);
                        }
                    }    
                    if(down_down->down){//third
                        Pixel*  down_down_down = down_down->down;
                        if( down_down_down-> colour > colour_neight &&  !down_down_down->check) {
                            pixels_neighs = neighs_count_create(colour_neight,  down_down_down, pixels_neighs);
                        }
                    }  
                }
            }
            if( down->left){//second
            Pixel* down_left= down->left;
                if( down_left-> colour > colour_neight && !down_left->check) {
                    down_left->check = 1;
                    pixels_neighs +=1; 
                    if( down_left->up){//third
                        Pixel* down_left_up = down_left->up;
                        if( down_left_up -> colour > colour_neight && !down_left_up ->check) {
                            pixels_neighs = neighs_count_create(colour_neight, down_left_up , pixels_neighs);
                        }
                    }    
                    if( down_left->left){//third
                        Pixel* down_left_left = down_left->left;
                        if( down_left_left-> colour > colour_neight && !down_left_left->check) {
                            pixels_neighs = neighs_count_create(colour_neight, down_left_left, pixels_neighs);
                        }
                    }    
                    if(down_left->down){//third
                        Pixel* down_left_down = down_left->down;
                        if( down_left_down-> colour > colour_neight && !down_left_down->check) {
                            pixels_neighs = neighs_count_create(colour_neight, down_left_down, pixels_neighs);
                        }
                    }  
                }
            }
            
            
        }
    
        return pixels_neighs;
} 

