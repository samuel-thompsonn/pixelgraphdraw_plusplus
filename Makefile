all: main
main: main.cpp ConsoleMatrixViewer.cpp Vector.h GraphModel.cpp DepthBuffer.cpp Triangle.cpp settings.h Matrix.hpp PointGrid.cpp GraphMesh.cpp ConsoleMatrixViewer.h PixelMatrix.h Vector.h
	g++ -std=c++14 -g -o main main.cpp ConsoleMatrixViewer.cpp GraphModel.cpp DepthBuffer.cpp Triangle.cpp PointGrid.cpp GraphMesh.cpp
