#include "GraphModel.h"

GraphModel::GraphModel(Vector<2> screenDims, Vector<2> start, Vector<2> end, int xVerts, int yVerts, Vector<3> cameraPos, std::function<float(float x, float y)> func)
  : myMesh(start, end, xVerts, yVerts, func) {
  myWidth = screenDims[0];
  myHeight = screenDims[1];
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