#include "Color.h"
#include <functional>
#include <iostream>

#ifndef PIXEL_MATRIX_T
#define PIXEL_MATRIX_T 1
class PixelMatrix {
  public:
    PixelMatrix(int width, int height) {
      myWidth = width;
      myHeight = height;
      myPixels = new Color*[myHeight];
      for (int i = 0; i < myHeight; i ++) {
          myPixels[i] = new Color[myWidth];
          for (int j = 0; j < myWidth; j ++) {
            myPixels[i][j] = { 0, 0, 0 };
          }
      }
    }

    ~PixelMatrix() {
      for (int i = 0; i < myHeight; i ++) {
        delete myPixels[i];
      }
      delete myPixels;
    }

    Color getPixel(int i, int j) { return myPixels[i][j]; }

    // TODO: Throw an error if i and j are out of bounds
    void setPixel(int i, int j, Color newColor) { 
      if (i == 0 & j == 0) {
        std::cout << "setting pixel 0,0 to a color!\n";
      }
      myPixels[i][j] = newColor; 
    }

    void setEachPixel(std::function<Color(int i, int j)> colorFunc) {
      for (int i = 0; i < myHeight; i ++) {
        for (int j = 0; j < myWidth; j ++) {
          setPixel(i, j, colorFunc(i, j));
        }
      }
    }

    int getWidth() { return myWidth; }

    int getHeight() { return myHeight; }

  private:
    Color** myPixels;
    int myWidth;
    int myHeight;
};
#endif