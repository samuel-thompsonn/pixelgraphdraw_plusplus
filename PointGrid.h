#include "Vector.h"
#include <functional>

#ifndef POINT_GRID_T
#define POINT_GRID_T 1
class PointGrid {
  private:
    int myWidth;
    int myHeight;
    Vector<3>* points;

  public:
    PointGrid(int width, int height, float sideLength, std::function<float(float, float)> func);
    ~PointGrid();
    Vector<3> getPoint(int i, int j);
};
#endif