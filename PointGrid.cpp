#include "PointGrid.h"
#include <iostream>

PointGrid::PointGrid(int width, int height, float sideLength, std::function<float(float, float)> func) {
  std::cout << "Initializing point grid with width " << width << "\n";
  myWidth = width;
  myHeight = height;
  points = new Vector<3>[width * height];
  for (int i = 0; i < height; i ++) {
    for (int j = 0; j < width; j ++) {
      float x = i * sideLength;
      float y = j * sideLength;
      points[(i * width) + j] = { x, y, func(x, y) };
    }
  }
}

PointGrid::~PointGrid() {
  delete points;
}

Vector<3> PointGrid::getPoint(int i, int j) {
  if (i >= myHeight || j >= myWidth) {
    std::cout << "Out of bounds access to PointGrid.getPoint()\n";
    std::cout << "\ti = " << i << ", j = " << j << "\n";
    std::cout << "\tmyWidth = " << myHeight << ", myHeight = " << myWidth << "\n";
  }
  return points[(i * myWidth) + j];
}