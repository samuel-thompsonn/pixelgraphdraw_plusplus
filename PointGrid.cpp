#include "PointGrid.h"
#include <iostream>

PointGrid::PointGrid(Vector<2> start, Vector<2> end, int numXVerts, int numYVerts, std::function<float(float, float)> func) {
  std::cout << "Initializing point grid with width " << numXVerts << "\n";
  myXSize = numXVerts;
  myYSize = numYVerts;
  float xSideLength = (end[0] - start[0]) / numXVerts;
  float ySideLength = (end[1] - start[1]) / numYVerts;
  points = new Vector<3>[myXSize * myYSize];
  for (int i = 0; i < myYSize; i ++) {
    for (int j = 0; j < myXSize; j ++) {
      float x = start[0] + (i * xSideLength); // Should these be switched?
      float y = start[1] + (j * ySideLength);
      points[(i * myXSize) + j] = { x, y, func(x, y) };
    }
  }
}

PointGrid::~PointGrid() {
  delete points;
}

Vector<3> PointGrid::getPoint(int i, int j) {
  if (i >= myYSize || j >= myXSize) {
    std::cout << "Out of bounds access to PointGrid.getPoint()\n";
    std::cout << "\ti = " << i << ", j = " << j << "\n";
    std::cout << "\tmyWidth = " << myYSize << ", myYSize = " << myXSize << "\n";
  }
  return points[(i * myXSize) + j];
}