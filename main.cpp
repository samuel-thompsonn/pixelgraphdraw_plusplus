#include <iostream>
#include "Vector.h"
#include "MatrixViewer.h"
#include "ConsoleMatrixViewer.h"
#include "PixelMatrix.h"
#include "GraphModel.h"
#include <memory>
#include "settings.h"
#include <fstream>
#include <iostream>
#include <math.h>
#include <map>

using namespace std;

void init_pixels(unique_ptr<PixelMatrix> const& pixels) {
    for (int i = 0; i < pixels->getHeight(); i ++) {
        for (int j = 0; j < pixels->getWidth(); j ++) {
            pixels->setPixel(i, j, { 0.5, 0.5, 0.5 });
        }
    }
}

int main() {

    std::ifstream settingsFile("settings.txt");
    int screenSize = 20;
    int verticesX = 3, verticesY = 3;
    float gridSize = 10.0f;
    float cameraX, cameraY, cameraZ;
    unsigned int functionId = 0;
    float rotation;

    if (settingsFile.is_open()) {
        char buffer[100];

        settingsFile >> buffer >> screenSize;

        settingsFile >> buffer >> verticesX;
        settingsFile >> buffer >> verticesY;
        std::cout << "Vertices: X=" << verticesX << ", Y=" << verticesY << "\n";

        settingsFile >> buffer >> gridSize;

        settingsFile >> buffer >> cameraX >> cameraY >> cameraZ;

        settingsFile >> buffer >> functionId;

        settingsFile >> buffer >> rotation;

        settingsFile.close();
    }

    std::map<int, std::function<float(float, float)>> funcs {
        {0, [functionId](float x, float y) {FLAT_FUNC}},
        {1, [functionId](float x, float y) {X_FUNC}},
        {2, [functionId](float x, float y) {XY_FUNC}},
        {3, [functionId](float x, float y) {COS_X_FUNC}},
        {4, [functionId](float x, float y) {COS_Y_FUNC}},
        {5, [functionId](float x, float y) {SADDLE_FUNC}}
    };

    std::function<float(float, float)> func = funcs[0];
    if (functionId <= 5) {
        func = funcs[functionId];
    }

    Vector<3> cameraPos = { cameraX, cameraY, cameraZ };
    auto model = std::make_unique<GraphModel>(screenSize, screenSize, verticesX, verticesY, gridSize, cameraPos, func);
    model->setGraphRotation((rotation / 360) * 2 * PI);
    unique_ptr<PixelMatrix> pixels(model->getColorMatrix());

    unique_ptr<ConsoleMatrixViewer> viewer(new ConsoleMatrixViewer());
    viewer->render(pixels, screenSize, screenSize);


    return EXIT_SUCCESS;
}