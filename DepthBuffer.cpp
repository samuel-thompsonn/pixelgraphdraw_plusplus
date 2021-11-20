#include "DepthBuffer.h"

DepthBuffer::DepthBuffer(int width, int height) {
  myDepths = new float[width * height];
  myWidth = width;
  myHeight = height;
  for (int i = 0; i < height; i ++) {
    for (int j = 0; j < width; j ++) {
      setDepth(i, j, -1000000); // TODO: Replace with best practice -inf
    }
  }
}

DepthBuffer::~DepthBuffer() {
  delete myDepths;
}

float DepthBuffer::getDepth(int i, int j) {
  return myDepths[(i * myWidth) + j];
}

void DepthBuffer::setDepth(int i, int j, float depth) {
  myDepths[(i * myWidth) + j] = depth;
}
