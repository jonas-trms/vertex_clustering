#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "computations.h"

void compute_max_coords(FILE *read, double *max_x, double *max_y,
                        double *max_z) {
  *max_x = 0.;
  *max_y = 0.;
  *max_z = 0.;

  int vertex_nb;
  fscanf(read, "#%d vertices; %*d faces\n\n", &vertex_nb);

  for (int i = 1; i <= vertex_nb; i++) {
    double x, y, z;

    fscanf(read, "v %lf %lf %lf\n", &x, &y, &z);

    if (fabs(x) > *max_x) {
      *max_x = fabs(x);
    }
    if (fabs(y) > *max_y) {
      *max_y = fabs(y);
    }
    if (fabs(z) > *max_z) {
      *max_z = fabs(z);
    }
  }
}

int calc_box_of_vertex(int factor, double max_x, double max_y, double max_z,
                       double x, double y, double z) {
  int x_coord = (int)floor((x + max_x) * (double)factor / (2 * max_x));
  int y_coord = (int)floor((y + max_y) * (double)factor / (2 * max_y));
  int z_coord = (int)floor((z + max_z) * (double)factor / (2 * max_z));

  // overflow correction
  if (x_coord >= factor) {
    x_coord = factor - 1;
  }
  if (y_coord >= factor) {
    y_coord = factor - 1;
  }
  if (z_coord >= factor) {
    z_coord = factor - 1;
  }

  // tridimensionnal tab flattened
  int index = (y_coord * factor + x_coord) * factor + z_coord;

  return index;
}

void compute_representative_avg(Bounding_box *box) {
  double x = 0., y = 0., z = 0.;

  Vertex *v_current = box->head;
  while (v_current != NULL) {
    x += v_current->x;
    y += v_current->y;
    z += v_current->z;

    v_current = v_current->next;
  }

  box->x = x / (double)(box->vertex_nb);
  box->y = y / (double)(box->vertex_nb);
  box->z = z / (double)(box->vertex_nb);
}

void compute_representative_med(Bounding_box *box) {
  vertex_chain *vchain = malloc(sizeof(vertex_chain));
  vchain->start = NULL;
  vchain->len = 0;

  Vertex *v_current = box->head;

  while (v_current != NULL) {
    int i = insert_v(v_current, vchain);
    if (i == -1) {
      printf("Erreur\n");
    }

    else if (i == 1) {
      (vchain->len)++;
    }

    v_current = v_current->next;
  }

  v_current = box->head;
  int i = 1;

  while (i < (vchain->len) / 2) {
    v_current = v_current->next;
    i++;
  }

  if ((vchain->len) % 2 == 1) {
    if (i < (vchain->len)) {
      v_current = v_current->next;
    }
    box->x = v_current->x;
    box->y = v_current->y;
    box->z = v_current->z;
  }

  else {
    box->x = (v_current->x + (v_current->next)->x) / (double)2;
    box->y = (v_current->y + (v_current->next)->y) / (double)2;
    box->z = (v_current->z + (v_current->next)->z) / (double)2;
  }

  free_v_chain(vchain);
}

int compute_boxes(Bounding_box *box_tab, int size, char method) {
  int index = 1;

  for (int i = 0; i < size; i++) {
    // if the bounding box isn't empty
    if (box_tab[i].vertex_nb > 0) {
      if (method == 'a') {
        compute_representative_avg(&box_tab[i]);
      } else {
        compute_representative_med(&box_tab[i]);
      }
      box_tab[i].index = index;
      index++;
    }
  }

  return index - 1;
}