#pragma once

#include "../imagelib/image.h"

#include "structs.h"


Pixel** populate_pixels(Image* image, int* base_colour) ;
Neighborhood* create_tree(Image* image, Image* marker);
void dowhill(Neighborhood* neight, Image* marker);
int neighs_count_create(int colour_neight, Pixel* initial_pixel, int pixels_neighs);
void connect_parent(Neighborhood* parent, Neighborhood* actual);

void poblar_img(Pixel** pixeles, Image* nueva, int R);
