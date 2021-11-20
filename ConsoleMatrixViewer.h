#include "MatrixViewer.h"
#include "PixelMatrix.h"
#include <iostream>
#include <memory>

#define PIXEL_HEIGHT 2

class ConsoleMatrixViewer {
  public:
    ConsoleMatrixViewer() {};
    virtual ~ConsoleMatrixViewer() {};
    
    void render(std::unique_ptr<PixelMatrix> const& pixels, int width, int height);
};