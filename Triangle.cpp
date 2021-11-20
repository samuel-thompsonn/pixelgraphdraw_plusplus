#include "Triangle.h"
#include <iostream>
#include "settings.h"

Vector<2> proj(Vector<2> onto, Vector<2> projected) {
  return ((projected * onto) / pow(onto.magnitude(), 2)) * onto;
}

bool pointInShadow(Vector<2> target, Vector<2> v1, Vector<2> v2, Vector<2> v3, Vector<2> side) {
  Vector<2> sideNormal = { side[1], -side[0]};
  float v1Dot = sideNormal * v1;
  float v2Dot = sideNormal * v2;
  float v3Dot = sideNormal * v3;
  float targetDot = sideNormal * target;
  float minPoint = std::min({ v1Dot, v2Dot, v3Dot });
  float maxPoint = std::max({ v1Dot, v2Dot, v3Dot });
  return (targetDot >= minPoint && targetDot <= maxPoint);
}

float calcPixelDepth(Vector<2> target, Vector<3> v1, Vector<3> v2, Vector<3> v3, Vector<2> v1Proj, Vector<2> v2Proj, Vector<2> v3Proj) {
  
  // std::cout << "target: ";
  // target.printSelf();

  // std::cout << "v1: ";
  // v1.printSelf();

  // std::cout << "v2: ";
  // v2.printSelf();

  // std::cout << "v3: ";
  // v3.printSelf();

  Vector<2> u = v2Proj - v1Proj;
  Vector<2> v = v3Proj - v1Proj;
  Vector<2> x = target - (v1Proj);
  float u_scalar = (x * u) / (u.magnitude());
  float v_scalar = (x * v) / (v.magnitude());

  Vector<3> projNormal = { 1.0, 1.0, 1.0 };

  float v1_depth = v1 * projNormal;
  float v2_depth = v2 * projNormal;
  float v3_depth = v3 * projNormal;

  // std:: cout << "v1 depth: " << v1_depth;
  // std:: cout << "v2 depth: " << v2_depth;
  // std:: cout << "v3 depth: " << v3_depth;

  float u_depth = v1_depth + (u_scalar * (v2_depth - v1_depth));
  float uv_depth = u_depth + (v_scalar * (v3_depth - v1_depth));

  // std::cout << "uv_depth: " << uv_depth << "\n";

  return uv_depth;
}

bool Triangle::pointInBounds(int x, int y, Vector<2> v1, Vector<2> v2, Vector<2> v3) {
  Vector<2> targetPoint = { (float)x, (float)y };
  Vector<2> sides[] = { (v2 - v1), (v3 - v2), (v1 - v3) };
  for (Vector<2> side : sides) {
    if (!pointInShadow(targetPoint, v1, v2, v3, side)) {
      return false;
    }
  }
  return true;
}

void Triangle::renderSelf(PixelMatrix &pixels, DepthBuffer &zBuffer, Matrix<2, 4> matrixMVP, Vector<3> cameraPos) {

  // Matrix<4, 4> modelMatrix = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, { 0, 0, 0, 1}};
  // Matrix<3, 4> viewMatrix = {
  //   { 1, 0, 0, -1 * cameraPos[0]},
  //   { 0, 1, 0, -1 * cameraPos[1]},
  //   { 0, 0, 1, -1 * cameraPos[2]}
  // };
  // Matrix<2, 3> projectionMatrix = PROJECTION_MATRIX;

  // Matrix<2, 4> matrixMVP = projectionMatrix * viewMatrix * modelMatrix;

  Vector<4> v1z = { v1[0], v1[1], v1[2], 1 };
  Vector<2> v1Proj = matrixMVP * v1z;
  Vector<4> v2z = { v2[0], v2[1], v2[2], 1 };
  Vector<2> v2Proj = matrixMVP * v2z;

  Vector<4> v3z = { v3[0], v3[1], v3[2], 1 };
  Vector<2> v3Proj = matrixMVP * v3z;
  float minX = std::max(std::min(std::min(v1Proj[0], v2Proj[0]), v3Proj[0]), 0.f);
  float minY = std::max(std::min(std::min(v1Proj[1], v2Proj[1]), v3Proj[1]), 0.f);
  float maxX = std::min(std::max(std::max(v1Proj[0], v2Proj[0]), v3Proj[0]), (float)pixels.getWidth());
  float maxY = std::min(std::max(std::max(v1Proj[1], v2Proj[1]), v3Proj[1]), (float)pixels.getWidth());

  // Vector<3> projNormal = { 1.0, 1.0, 1.0 };
  // for (int i = (int)minY; i < (int)std::ceil(maxY); i ++) {
  //   for (int j = (int)minX; j < (int)std::ceil(maxX); j ++) {
  //     float depth = calcPixelDepth({(float)i, (float)j}, v1, v2, v3, projectionMatrix);
  //     if (zBuffer.getDepth(i, j) > depth) { 
  //       std::cout << "Found lesser depth.\n";
  //       std::cout << "zBuffer(" << i << ", " << j << "): " << zBuffer.getDepth(i,j) << "\n";
  //       std::cout << "depth: " << depth << "\n";
  //       continue; 
  //     }    
  //     zBuffer.setDepth(i, j, depth);
  //   }
  // }
  
  for (int i = (int)minY; i < (int)std::ceil(maxY); i ++) {
    for (int j = (int)minX; j < (int)std::ceil(maxX); j ++) {
      if (!pointInBounds(j, i, v1Proj, v2Proj, v3Proj)) {
        continue;
      }
      float depth = calcPixelDepth({(float)i, (float)j}, v1, v2, v3, v1Proj, v2Proj, v3Proj);
      if (zBuffer.getDepth(i, j) > depth) { continue; }
      // std::cout << "\tIn bounds.\n";
      Vector<3> normal = ((v2 - v1).cross(v3 - v1)).normalized();     
      Vector<3> lightDirection = { 1.0, 1.0, -1.0 };
      float lightAmount = lightDirection.normalized() * normal;

      // Vector<3> basis_0 = { -1.0, 1.0, 0.0 }; // Represents right

      // Vector<3> basis_1 = { -1.0, -1.0, 2.0 }; // Represents up
      // d = ((v1 - l_0) * n) / (projNormal * normal)

      pixels.setPixel(i, j, { lightAmount, lightAmount, lightAmount });
    }
  }
}