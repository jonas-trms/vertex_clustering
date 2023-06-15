# A mesh simplification algorithm based on vertex clustering
This algorithm is based on the paper [_Multi-resolution 3D approximations for rendering complex scenes_](https://doi.org/10.1007/978-3-642-78114-8_29) by Jarek ROSSIGNAC, Paul BORREL.

The space is divided into cubes of chosen volume, then the vertices of each cube are merged into a single representative, thus reducing the number of vertices of the initial mesh. 

Two methods are implemented for the computation of the representative : the average point, or the median point. The algorithm makes several attemps, changing the cubes volume, until the reduction criteria is met, or a minimum is reached.

This implementation is very fast and provides good simplifications for simple meshes, but it may not preserve the details of complex meshes.

# Compilation
You can compile with GCC by running the following command:

```
$ gcc -o vertex_clustering main.c computations.c median.c output.c structure_operations.c -lm
```
# Execution
Meshes must be in OBJ format.

Arguments: input path, output path, method (`a` for average, `m` for median), desired reduction factor, acceptable error on the reduction factor.

# Example
```
$ ./vertex_clustering forest.obj forest_reduced.obj a 4.0 0.1
```

![initial mesh](https://i.imgur.com/B2rGz0O.png) ![reduced mesh](https://i.imgur.com/5YGgHsC.png) \
The number of vertices was divided by 4 (the initial mesh is on the left).
