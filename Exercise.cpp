#include "Exercise.h"

namespace miit::algebra {
    void Exercise::setMatrix(const Matrix<int>& mat) {
        matrix = mat;
    }

    const Matrix<int>& Exercise::getMatrix() const {
        return matrix;
    }
}
