#ifndef MEDIAN
#define MEDIAN

#include "data_structures.h"

// sorted linked lists
struct vertex_node {
  Vertex *v;
  struct vertex_node *next;
};

typedef struct vertex_node vertex_node;

struct vertex_chain {
  int len;
  vertex_node *start;
};

typedef struct vertex_chain vertex_chain;

// sort
int compare_fl(float a, float b);
int compare_v(Vertex *v1, Vertex *v2);
int insert_v(Vertex *v, vertex_chain *vchain);
void free_v_chain(vertex_chain *vchain);

#endif