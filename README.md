# A mesh simplification algorithm based on _vertex clustering_
This algorithm is based on the paper _Multi-resolution 3D approximations for rendering complex scenes_ by JAREK ROSSIGNAC, PAUL BORREL

The space is divided into cubes of chosen volume, then the vertices of each cube are merged into a single representative, thus reducing the number of vertices of the initial mesh. 

Two methods are implemented for the computation of the representative : the average point, or the median point. The algorithm makes several attemps changing the cubes volume, until the reduction criteria is met, or a minimum is reached

This implementation is very fast and provides good simplifications for simple meshes, but it may not preserve the details of complex meshes.

# Execution
Meshes must be in obj format

Arguments : input path, output path, method (a for average, m for median), desired reduction factor, acceptable error on the reduction factor

# Example
![](https://i.imgur.com/B2rGz0O.png) ![](https://i.imgur.com/5YGgHsC.png) \
The number of vertices was divided by 4
