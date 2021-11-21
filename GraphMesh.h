#include "PixelMatrix.h"
#include "DepthBuffer.h"
#include "Triangle.h"
#include "PointGrid.h"
#include "settings.h"
#include <functional>
#include <memory>
#include <list>

class GraphMesh {
  public:
    GraphMesh(Vector<2> start, Vector<2> end, int numXVerts, int numYVerts, std::function<float(float x, float y)> func);
    void renderSelf(PixelMatrix &pixels, DepthBuffer &zBuffer, Vector<3> cameraPos);
    void setRotation(float rotation) { myRotation = rotation; }
    void update();

  private:
    int myWidth, myHeight;
    float myRotation;
    std::list<Triangle> myTriangles;
    PointGrid myPoints;
};