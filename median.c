#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "median.h"

// sort
int compare_fl(float a, float b) {
  if (a > b) {
    return 1;
  } else if (a < b) {
    return -1;
  } else {
    return 0;
  }
}

int compare_v(Vertex *v1, Vertex *v2) {
  if (compare_fl(v1->x, v2->x) != 0) {
    return compare_fl(v1->x, v2->x);
  }

  else {
    if (compare_fl(v1->y, v2->y) != 0) {
      return compare_fl(v1->y, v2->y);
    }

    else {
      return compare_fl(v1->z, v2->z);
    }
  }
}

int insert_v(Vertex *v, vertex_chain *vchain) {
  vertex_node *new = malloc(sizeof(vertex_node));
  new->v = v;

  vertex_node *curr = vchain->start;

  if (curr == NULL) {
    new->next = NULL;
    vchain->start = new;
    return 1;
  }

  if (compare_v(v, curr->v) == 0) {
    free(new);
    return 0;
  }

  else if (compare_v(v, curr->v) == -1) {
    new->next = curr;
    vchain->start = new;
    return 1;
  }

  while (curr->next != NULL) {
    if (compare_v(v, (curr->next)->v) == 0) {
      free(new);
      return 0;
    }

    else if (compare_v(v, (curr->next)->v) == -1) {
      new->next = curr->next;
      curr->next = new;
      return 1;
    }

    else {
      curr = curr->next;
    }
  }

  if (compare_v(v, curr->v) == 0) {
    free(new);
    return 0;
  }

  else if (compare_v(v, curr->v) == 1) {
    new->next = NULL;
    curr->next = new;
    return 1;
  }

  return -1;
}

void free_v_chain(vertex_chain *vchain) {
  vertex_node *curr = vchain->start;

  while (curr != NULL && curr->next != NULL) {
    vertex_node *tmp = curr;
    curr = curr->next;
    free(tmp);
  }

  if (curr != NULL) {
    free(curr);
  }

  free(vchain);
}