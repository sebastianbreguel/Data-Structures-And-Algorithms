#pragma once

#include "../imagelib/image.h"

#include "component_tree.h"

void not_free(Neighborhood* neighborhood, int parent_include);
void frees(Neighborhood* neighborhood);

float cost_neighborhood_notLeaf(Neighborhood* neighborhood, float alpha);