#ifndef DATA_STRUCTURES
#define DATA_STRUCTURES

struct vertex {
  double x;
  double y;
  double z;
  struct vertex *next;
};

typedef struct vertex Vertex;

struct bounding_box {
  double x;
  double y;
  double z;
  int index;
  int vertex_nb;
  Vertex *head;
  Vertex *queue;
};

typedef struct bounding_box Bounding_box;

#endif