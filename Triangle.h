#include "PixelMatrix.h"
#include "DepthBuffer.h"
#include "Vector.h"
#include "Matrix.hpp"
#include <math.h>
#include <algorithm>

#ifndef TRIANGLE_T
#define TRIANGLE_T 1
class Triangle {
  public:
    Triangle(Vector<3> vector1, Vector<3> vector2, Vector<3> vector3) {
      v1 = vector1;
      v2 = vector2;
      v3 = vector3;
    };

    Vector<3> vert1() { return v1; }
    Vector<3> vert2() { return v2; }
    Vector<3> vert3() { return v3; }

    void renderSelf(PixelMatrix &pixels, DepthBuffer &zBuffer, Matrix<2, 4> matrixMVP, Vector<3> cameraPos);

  private:
    Vector<3> v1, v2, v3;
    bool pointInBounds(int x, int y, Vector<2> v1, Vector<2> v2, Vector<2> v3);
};
#endif