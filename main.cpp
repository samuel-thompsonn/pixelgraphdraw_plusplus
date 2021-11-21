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

void renderGraph(Vector<3> cameraPos, Vector<2> graphStart, Vector<2> graphEnd, int screenSize, int verticesX, int verticesY, float rotation, int functionId) {
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

    Vector<2> screenDims = { (float)screenSize, (float)screenSize };
    auto model = std::make_unique<GraphModel>(screenDims, graphStart, graphEnd, verticesX, verticesY, cameraPos, func);
    model->setGraphRotation((rotation / 360) * 2 * PI);
    unique_ptr<PixelMatrix> pixels(model->getColorMatrix());

    unique_ptr<ConsoleMatrixViewer> viewer(new ConsoleMatrixViewer());
    viewer->render(pixels, screenSize, screenSize);
}

int main() {

    std::ifstream settingsFile("settings.txt");
    int screenSize = 20;
    float startX, startY, endX, endY;
    int verticesX = 3, verticesY = 3;
    float cameraX, cameraY, cameraZ;
    unsigned int functionId = 0;
    float rotation;
    float rotationDelta;

    if (settingsFile.is_open()) {
        char buffer[100];

        settingsFile >> buffer >> screenSize;

        settingsFile >> buffer >> startX;
        settingsFile >> buffer >> startY;
        settingsFile >> buffer >> endX;
        settingsFile >> buffer >> endY;

        settingsFile >> buffer >> verticesX;
        settingsFile >> buffer >> verticesY;
        std::cout << "Vertices: X=" << verticesX << ", Y=" << verticesY << "\n";

        settingsFile >> buffer >> cameraX >> cameraY >> cameraZ;

        settingsFile >> buffer >> functionId;

        settingsFile >> buffer >> rotation;

        settingsFile >> buffer >> rotationDelta;

        settingsFile.close();
    }

    Vector<3> cameraPos = { cameraX, cameraY, cameraZ };
    Vector<2> graphStart = { startX, startY };
    Vector<2> graphEnd = { endX, endY };
    Vector<2> screenDims = { (float)screenSize, (float)screenSize };
    
    while (true) {
        system("clear");
        renderGraph(cameraPos, graphStart, graphEnd, screenSize, verticesX, verticesY, rotation, functionId);
        rotation += rotationDelta;
        char a = cin.get();
    }


    return EXIT_SUCCESS;
}