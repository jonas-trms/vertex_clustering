#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "structure_operations.h"

Bounding_box *create_box_tab(int size) {
  Bounding_box *box_tab = malloc(size * sizeof(Bounding_box));
  for (int i = 0; i < size; i++) {
    box_tab[i].x = 0.;
    box_tab[i].y = 0.;
    box_tab[i].z = 0.;

    box_tab[i].vertex_nb = 0;
    box_tab[i].index = -1;

    box_tab[i].head = NULL;
    box_tab[i].queue = NULL;
  }

  return box_tab;
}

void vertex_append(Bounding_box *box, double x, double y, double z) {
  // creates and initializes new vertex
  Vertex *v = malloc(sizeof(Vertex));
  v->x = x;
  v->y = y;
  v->z = z;
  v->next = NULL;

  // adds this vertex to the bounding box
  if (box->head == NULL) {
    box->head = v;
    box->queue = v;
  }

  else {
    (box->queue)->next = v;
    box->queue = v;
  }

  box->vertex_nb++;
}

void free_vertices_in_box(Bounding_box *box) {
  Vertex *v_current = box->head;
  while (v_current != NULL) {
    Vertex *tmp = v_current;
    v_current = v_current->next;
    free(tmp);
  }
}

void free_box_tab(Bounding_box *box_tab, int size) {
  for (int i = 0; i < size; i++) {
    free_vertices_in_box(&box_tab[i]);
  }

  free(box_tab);
}