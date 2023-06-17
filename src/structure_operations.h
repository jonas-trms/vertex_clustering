#ifndef STRUCTURE_OPERATIONS
#define STRUCTURE_OPERATIONS

#include "data_structures.h"

Bounding_box *create_box_tab(int size);
void vertex_append(Bounding_box *box, double x, double y, double z);
void free_vertices_in_box(Bounding_box *box);
void free_box_tab(Bounding_box *box_tab, int size);

#endif