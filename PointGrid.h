#include "Vector.h"
#include <functional>

#ifndef POINT_GRID_T
#define POINT_GRID_T 1
class PointGrid {
  private:
    int myXSize;
    int myYSize;
    Vector<3>* points;

  public:
    PointGrid(Vector<2> start, Vector<2> end, int numXVerts, int numYVerts, std::function<float(float, float)> func);
    ~PointGrid();
    Vector<3> getPoint(int i, int j);
};
#endif