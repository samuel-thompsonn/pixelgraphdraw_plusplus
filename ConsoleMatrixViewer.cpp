#include "ConsoleMatrixViewer.h"

void ConsoleMatrixViewer::render(std::unique_ptr<PixelMatrix> const& pixels, int width, int height) {
  // system("clear");
  for (int i = 0; i < height; i += PIXEL_HEIGHT) {
    for (int j = 0; j < width; j ++) {
      if (pixels->getPixel(i, j).r == 0.0f) { std::cout << " "; }
      else if (pixels->getPixel(i, j).r <= 0.25f) { std::cout << "\u2591"; }
      else if (pixels->getPixel(i, j).r <= 0.50f) { std::cout << "\u2592"; }
      else if (pixels->getPixel(i, j).r <= 0.75f) { std::cout << "\u2593"; }
      else { std::cout << "\u2588"; }
    }
    std::cout << "\n";
  }
}