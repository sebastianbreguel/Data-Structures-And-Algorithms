#pragma once
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>




void printGrid(int grid[8][8], int sum_row[8], int sum_column[8]);

void writeSolution(FILE* outpu_file, int grid[8][8]);


void solveProblem(FILE* output_file,int grid[8][8]);


int doIt(int actual, int x_actual, int y_actual,int values_x[64], int values_y[64],
         int xMove[8], int yMove[8],int sum_row[8],int sum_column[8], int sol[8][8],int grid[8][8]);

int isInRange(int x, int y, int grid[8][8], int sol[8][8], int actual, int sum_row, int sum_column);