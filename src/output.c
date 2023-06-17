#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "output.h"

void write_boxes(FILE *write, Bounding_box *box_tab, int size) {
  for (int i = 0; i < size; i++) {
    if (box_tab[i].index != -1) {
      fprintf(write, "v %lf %lf %lf\n", box_tab[i].x, box_tab[i].y,
              box_tab[i].z);
    }
  }
}

int write_faces(FILE *read, FILE *write, Bounding_box *box_tab,
                int *box_of_vertex, int face_nb) {
  int face_nb_new = 0;

  for (int i = 0; i < face_nb; i++) {
    // reads current face
    int f1, f2, f3;
    fscanf(read, "f %d %d %d\n", &f1, &f2, &f3);
    f1--;
    f2--;
    f3--;

    // if the computed face isn't flat
    if (box_of_vertex[f1] != box_of_vertex[f2] &&
        box_of_vertex[f2] != box_of_vertex[f3] &&
        box_of_vertex[f1] != box_of_vertex[f3]) {
      fprintf(write, "f %d %d %d\n", box_tab[box_of_vertex[f1]].index,
              box_tab[box_of_vertex[f2]].index,
              box_tab[box_of_vertex[f3]].index);
      face_nb_new++;
    }
  }

  return face_nb_new;
}