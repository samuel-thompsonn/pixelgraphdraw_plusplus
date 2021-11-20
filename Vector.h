#ifndef VECTOR_T
#define VECTOR_T

#include <functional>
#include <memory>
#include <math.h>
#include <initializer_list>
#include <iostream>
#include <algorithm>

template <unsigned int N>
class Vector {

  private:
    float myElements[N];

  public:

    Vector() {
      std::fill(std::begin(myElements), std::end(myElements), 0);
    }
    
    Vector(std::initializer_list<float> elements) {
      int i = 0;
      for (float element : elements) {
        myElements[i] = element;
        i ++;
      }
    }

    Vector(float elements[N]) {
      for (int i = 0; i < N; i ++) {
        myElements[i] = elements[i];
      }
    }

    Vector<N> operator+(const Vector<N>& rightVec) const {
      float outVec[N];
      for (int i = 0; i < N; i ++) {
        outVec[i] = myElements[i] + rightVec[i];
      }
      return outVec;
    }

    Vector<N> operator-(const Vector<N>& otherVec) const {
      return *this + (-1 * otherVec);
    }

    float operator[](unsigned int i) const {
      if (i >= N) {
        throw std::out_of_range("Invalid array index for vector.");
      }
      return myElements[i];
    }

    float operator*(struct Vector<N> otherVec) const{
      float dotProduct = 0;
      for (int i = 0; i < N; i ++) {
        dotProduct += myElements[i] * otherVec[i];
      }
      return dotProduct;
    }

    float magnitude() const {
      float magnitude = 0;
      for (int i = 0; i < N; i ++) {
        magnitude += pow(myElements[i], 2);
      }
      return sqrt(magnitude);
    }

    Vector<3> cross(Vector<3> otherVec) const {
      return {
        myElements[1]*otherVec[2] - myElements[2]*otherVec[1],
        myElements[2]*otherVec[0] - myElements[0]*otherVec[2],
        myElements[0]*otherVec[1] - myElements[1]*otherVec[0]
      };
    }

    Vector<N> normalized() const {
      return (1.0f / magnitude()) * *this;
    }

    Vector<N> proj(Vector<N> otherVec) const {
      return ((*this * otherVec) / (*this->magnitude())) * *this;
    }
};

template <unsigned int N>
static std::ostream& operator<<(std::ostream& out, const Vector<N>& vec) {
  out << vec[0];
  for (int i = 1; i < N; i ++) {
    out << ", " << vec[i];
  }
  out << ": N=" << N;
}

template <unsigned int N>
static Vector<N> operator*(float scalar, const Vector<N>& vec) {
  float outVec[N];
  for (int i = 0; i < N; i ++) {
    outVec[i] = scalar * vec[i];
  }
  return outVec;
}

#endif