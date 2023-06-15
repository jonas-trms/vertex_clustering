#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "computations.h"
#include "data_structures.h"
#include "median.h"
#include "output.h"
#include "structure_operations.h"

double algo_1(char *input, char *output, int factor, char method) {
  // reads vertex and face numbers
  int vertex_nb, face_nb;
  FILE *read;
  read = fopen(input, "r");
  fscanf(read, "#%d vertices; %d faces\n\n", &vertex_nb, &face_nb);
  fclose(read);

  // computes max_coords
  read = fopen(input, "r");
  double max_x, max_y, max_z;
  compute_max_coords(read, &max_x, &max_y, &max_z);
  fclose(read);

  // creates and initiates tabs
  int *box_of_vertex = malloc(vertex_nb * sizeof(int));
  Bounding_box *box_tab = create_box_tab(factor * factor * factor);

  // opens file and skips first line
  read = fopen(input, "r");
  fscanf(read, "#%*d vertices; %*d faces\n\n");

  // reads and computes new vertices
  for (int i = 0; i < vertex_nb; i++) {
    // reads coordinates for current vertex
    double x, y, z;
    fscanf(read, "v %lf %lf %lf\n", &x, &y, &z);

    // ties the vertex to its bounding box
    int index = calc_box_of_vertex(factor, max_x, max_y, max_z, x, y, z);
    box_of_vertex[i] = index;
    vertex_append(&box_tab[index], x, y, z);
  }

  // computes bounding_boxes
  int vertex_nb_new = compute_boxes(box_tab, factor * factor * factor, method);

  // writes bounding_boxes
  FILE *write;
  write = fopen(output, "w");
  write_boxes(write, box_tab, factor * factor * factor);

  // skips or writes jump
  fscanf(read, "\n");
  fprintf(write, "\n");

  // writes faces
  int face_nb_new = write_faces(read, write, box_tab, box_of_vertex, face_nb);

  // frees and closes
  free(box_of_vertex);
  free_box_tab(box_tab, factor * factor * factor);
  fclose(write);
  fclose(read);

  // computes reduction ratio
  double ratio = (double)vertex_nb / (double)vertex_nb_new;

  return ratio;
}

int main(int argc, char *argv[]) {
  // Algo1_bis in out method ratio error
  char *input = argv[1];
  char *output = argv[2];
  char method = argv[3][0];
  double ratio = atof(argv[4]);
  double error = atof(argv[5]);

  // reads vertex number
  int vertex_nb;
  FILE *read;
  read = fopen(input, "r");
  fscanf(read, "#%d vertices", &vertex_nb);
  fclose(read);

  clock_t start, end;
  start = clock();

  int factor = (int)floor(cbrt((double)vertex_nb / ratio)) + 1;
  int factor_in = factor;
  double ratio_curr = algo_1(input, output, factor, method);
  double error_curr = fabs(ratio - ratio_curr);
  double error_min = INFINITY;
  double error_prev = INFINITY;

  while (error_curr > error && ratio_curr > ratio - error_min &&
         error_curr != error_prev) {
    factor++;
    error_prev = error_curr;
    ratio_curr = algo_1(input, output, factor, method);
    error_curr = fabs(ratio - ratio_curr);
    if (error_curr < error_min) {
      error_min = error_curr;
    }
  }

  if (error_curr > error_prev) {
    factor--;
    ratio_curr = algo_1(input, output, factor, method);
    error_curr = fabs(ratio - ratio_curr);
  }

  end = clock();

  printf("\nFrom %d vertices to %d\nReduced %lf times\nElapsed time : %lf "
         "s\nNumber of tries : %d\n\n",
         vertex_nb, (int)floor((double)vertex_nb / ratio_curr), ratio_curr,
         (double)(end - start) / (double)CLOCKS_PER_SEC,
         (factor - factor_in + 1));
}