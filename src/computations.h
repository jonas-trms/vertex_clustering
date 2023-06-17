#ifndef COMPUTATIONS
#define COMPUTATIONS

#include "data_structures.h"
#include "median.h"
#include "structure_operations.h"

void compute_max_coords(FILE *read, double *max_x, double *max_y,
                        double *max_z);

int calc_box_of_vertex(int factor, double max_x, double max_y, double max_z,
                       double x, double y, double z);

void compute_representative_avg(Bounding_box *box);
void compute_representative_med(Bounding_box *box);

int compute_boxes(Bounding_box *box_tab, int size, char method);

#endif