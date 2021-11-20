#include "GraphMesh.h"

GraphMesh::GraphMesh(int xVerts, int yVerts, float cellSize, std::function<float(float x, float y)> func)
  : myPoints(yVerts, xVerts, cellSize, func) {

  myRotation = (30.0f / 360.0f) * (2 * PI);

  for (int i = 0; i < xVerts - 1; i ++) {
    for (int j = 0; j < yVerts - 1; j ++) {
      Vector<3> v1 = myPoints.getPoint(i, j);
      myTriangles.push_back(*(new Triangle(
        {
          myPoints.getPoint(i, j),
          myPoints.getPoint(i, j+1),
          myPoints.getPoint(i+1, j)
        }
      )));
      myTriangles.push_back(*(new Triangle(
        {
          myPoints.getPoint(i, j+1),
          myPoints.getPoint(i+1, j+1),
          myPoints.getPoint(i+1, j)
        }
      )));
    }
  }
}
  
void GraphMesh::update() {
  // Does nothing for now
}

void GraphMesh::renderSelf(PixelMatrix &pixels, DepthBuffer &zBuffer, Vector<3> cameraPos) {
  for (Triangle triangle : myTriangles) {
    
  Matrix<4, 4> modelMatrix = {{cos(myRotation), -sin(myRotation), 0, 0}, {sin(myRotation), cos(myRotation), 0, 0}, {0, 0, 1, 0}, { 0, 0, 0, 1}};
  Matrix<3, 4> viewMatrix = {
    { 1, 0, 0, -1 * cameraPos[0]},
    { 0, 1, 0, -1 * cameraPos[1]},
    { 0, 0, 1, -1 * cameraPos[2]}
  };
  Matrix<2, 3> projectionMatrix = PROJECTION_MATRIX;

  Matrix<2, 4> matrixMVP = projectionMatrix * viewMatrix * modelMatrix;
    triangle.renderSelf(pixels, zBuffer, matrixMVP, cameraPos);
  }
}