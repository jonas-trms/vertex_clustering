# A mesh simplification algorithm based on vertex clustering
![initial mesh vs reduced mesh](https://i.imgur.com/6Cei7be.png)

This algorithm is based on the paper [_Multi-resolution 3D approximations for rendering complex scenes_](https://doi.org/10.1007/978-3-642-78114-8_29) by J. Rossignac, P. Borel.

## Principle
The space is divided into cubes of chosen volume, then the vertices of each cube are merged into a single representative, thus reducing the number of vertices of the initial mesh. 

## Implementation
Two methods are implemented for the computation of the representative : the average point and the median point. 

The requiered volume of the cubes for a chosen reduction factor can only be estimated: since the vertices are often not uniformly distributed, some cubes won't contain any vertex, and the reduction factor will therefore be too high. On that account, the algorithm makes several attemps, increasing the volume of the cubes, until the chosen reduction criteria is met, or a minimum is reached.

This implementation is very fast and provides good simplifications for simple meshes, but it may not preserve the details of complex meshes.

## Compilation
You can compile with GCC by running the following command:

```
$ gcc -o vertex_clustering main.c computations.c median.c output.c structure_operations.c -lm
```
## Usage
This implementation expects triangular `.obj` files formatted in a specific way (see [Format](#format)). Here's how to use it:
`./main [args]` reduces the provided mesh using the described algorithm. Arguments:
 * `initial` is the path to the `.obj` file to be reduced.
 * `reduction` is the path to the reduced `.obj` file.
 * `method` is the chosen method for the compuration of the representative. Either `average` or `median`
 * `factor` is a `float` value equal to the desired reduction factor.
 * `error` is a `float` value equal to the acceptable error on the reduction factor (several attemps will often be requiered to get a low error, thus making the execution longer).

Example:

```
$ ./vertex_clustering forest.obj forest_reduced.obj a 4.0 0.1
```
  
## Format
The `.obj` files must be formatted in a specific way. The first line should be the following comment:
```#n vertices; m faces```.

Then, the file should only contain the vertex positions and the faces. Faces must be triplets of integers. For the line breaks, see the example.

Example of a formatted file:
```obj
#8 vertices; 12 faces

v -10.000000 -10.000000 -10.000000
v -10.000000 -10.000000 10.000000
v -10.000000 10.000000 10.000000
v -10.000000 10.000000 -10.000000
v 10.000000 -10.000000 -10.000000
v 10.000000 -10.000000 10.000000
v 10.000000 10.000000 10.000000
v 10.000000 10.000000 -10.000000

f 1 4 3
f 1 2 3
f 1 5 6
f 1 2 6
f 1 5 8
f 1 4 8
f 5 8 7
f 5 6 7
f 3 8 7
f 4 3 8
f 2 6 7
f 2 3 7
```
## Example of usage
![initial mesh](https://i.imgur.com/B2rGz0O.png) ![reduced mesh](https://i.imgur.com/5YGgHsC.png) \
The number of vertices was divided by `4` (the initial mesh is on the left), and the render time therefore divided by `2`, without any noticeable difference on the final image.
