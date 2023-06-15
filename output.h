#ifndef OUTPUT
#define OUTPUT

#include "data_structures.h"
#include "structure_operations.h"

void write_boxes(FILE *write, Bounding_box *box_tab, int size);
int write_faces(FILE *read, FILE *write, Bounding_box *box_tab,
                int *box_of_vertex, int face_nb);
                
#endif