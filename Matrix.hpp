#include "Vector.h"
#include <memory>
#include <iostream>

#ifndef MATRIX_T
#define MATRIX_T
template <unsigned int M, unsigned int N>
class Matrix {
  private:
    Vector<N> rows[M];

  public:

    Matrix(float elements[M][N]) {
      for (int i = 0; i < M; i ++) {
        rows[i] = elements[i];
      }
    }

    Matrix(std::initializer_list<std::initializer_list<float>> elements) {
      int i = 0;
      for (std::initializer_list<float> newRow : elements) {
        rows[i] = newRow;
        i ++;
      }
    }

    Vector<N> operator[](int i) {
      if (i >= M) {
        // Out of bounds. Throw an exception?
      }
      return rows[i];
    }

    Vector<M> operator*(Vector<N> vec) {
      float returnedElements[N];
      for (int i = 0; i < N; i++) {
        returnedElements[i] = rows[i] * vec;
      }
      return returnedElements;
    }

    Vector<M> column(int j) {
      float returnedElements[M];
      for (int i = 0; i < M; i ++) {
        returnedElements[i] = rows[i][j];
      }
      return returnedElements;
    }

    template <unsigned int P>
    Matrix<M, P> operator*(Matrix<N, P> otherMatrix) {
      float returnedMatrix[M][P];
      for (int i = 0; i < M; i ++) {
        for (int j = 0; j < P; j ++) {
          returnedMatrix[i][j] = rows[i] * otherMatrix.column(j);
        }
      }
      return returnedMatrix;
    }

    void printSelf() {
      std::cout << "[\n";
      rows[0].printSelf();
      for (int i = 1; i < M; i ++) {
        rows[i].printSelf();
      }
      std::cout << "]\n";
    }

};
#endif