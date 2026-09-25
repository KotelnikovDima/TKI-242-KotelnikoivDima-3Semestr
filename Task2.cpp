#include "Task2.h"
#include <limits>
#include <vector>

namespace miit::algebra {
    std::string Task2::getDescription() const {
        return "Вставить после всех строк, содержащих минимальный элемент массива, строку 2, 4, 6,…";
    }

    void Task2::solve() {
        if (matrix.getRows() == 0 || matrix.getCols() == 0) return;

        int min_val = std::numeric_limits<int>::max();
        for (size_t i = 0; i < matrix.getRows(); ++i) {
            for (size_t j = 0; j < matrix.getCols(); ++j) {
                if (matrix[i][j] < min_val) {
                    min_val = matrix[i][j];
                }
            }
        }

        std::vector<int> rowToInsert(matrix.getCols());
        for (size_t j = 0; j < matrix.getCols(); ++j) {
            rowToInsert[j] = static_cast<int>((j + 1) * 2);
        }

        for (int i = static_cast<int>(matrix.getRows()) - 1; i >= 0; --i) {
            bool has_min = false;
            for (size_t j = 0; j < matrix.getCols(); ++j) {
                if (matrix[i][j] == min_val) {
                    has_min = true;
                    break;
                }
            }
            if (has_min) {
                matrix.insertRow(i + 1, rowToInsert);
            }
        }
    }
}
