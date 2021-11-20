#ifndef MATRIX_VIEWER_T
#define MATRIX_VIEWER_T 1
#include "Color.h"
#include <iostream>

class MatrixViewer {
  public:
    MatrixViewer() {};
    virtual ~MatrixViewer() {};
    virtual void render(Color** pixels, int width, int height) = 0;
};
#endif