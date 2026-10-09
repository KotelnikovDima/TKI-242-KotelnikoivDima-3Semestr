#include "Exercise.h"

namespace miit::algebra {
    Exercise::Exercise(const Matrix<int>& mat) : matrix(mat) {}

    const Matrix<int>& Exercise::getMatrix() const {
        return matrix;
    }
}
