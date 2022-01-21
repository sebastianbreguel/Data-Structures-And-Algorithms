#pragma once

#include "../imagelib/image.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <png.h>
#include <math.h>


struct pixel
{
    int id; 
    int colour;
    int check;
    int include;
    struct pixel*  up;
    struct pixel* down;
    struct pixel* left;
    struct pixel* right;
    struct neighborhood* neigh_node;
};
typedef struct pixel Pixel;

struct neighborhood
{
    float ps ;
    float  n ;
    float cost ;
    int neighborhood_size;
    int include ;
    int colour;
    struct pixel** pixels;
    struct neighborhood* head;
    struct neighborhood* tail;
    struct neighborhood* next;
    struct neighborhood* parent; 
};


typedef struct neighborhood Neighborhood;


Pixel* create_pixel(int number, int colour);
Neighborhood* create_neighborhood(int neighborhood_size, int colour, Neighborhood* parent, Pixel** pixel, Image* marker);