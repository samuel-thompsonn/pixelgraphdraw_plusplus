#include "Color.h"
#include "Triangle.h"
#include "PixelMatrix.h"
#include "PointGrid.h"
#include "Vector.h"
#include "GraphMesh.h"
#include <functional>
#include <memory>

class GraphModel {
  public:
    GraphModel(int width, int height, int xVerts, int yVerts, float gridSize, Vector<3> cameraPos, std::function<float(float x, float y)> func);
    void update();
    PixelMatrix* getColorMatrix(); // TODO: maybe use subscriber pattern instead?
    void setGraphRotation(float rotation);
    
  private:
    int myWidth, myHeight;
    std::list<Triangle> myTriangles;
    GraphMesh myMesh;
    Vector<3> myCameraPos;
};