#include "GraphModel.h"

GraphModel::GraphModel(int width, int height, int xVerts, int yVerts, float gridSize, Vector<3> cameraPos, std::function<float(float x, float y)> func)
  : myMesh(xVerts, yVerts, gridSize, func) {
  myWidth = width;
  myHeight = height;
  myCameraPos = cameraPos;

  float yOffset = 0;
  float sideLength = 10;

}

PixelMatrix* GraphModel::getColorMatrix() {

  std::unique_ptr<DepthBuffer> zBuffer(new DepthBuffer(myWidth, myHeight));
  PixelMatrix* pixels = new PixelMatrix(myWidth, myHeight);

  myMesh.renderSelf(*pixels, *zBuffer, myCameraPos);

  
  return pixels;
}

void GraphModel::update() {
  // Does nothing for now
}

void GraphModel::setGraphRotation(float rotation) {
  myMesh.setRotation(rotation);
}