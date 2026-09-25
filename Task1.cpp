#include "Task1.h"

namespace miit::algebra {
    std::string Task1::getDescription() const {
        return "Заменить максимальный элемент каждой строки номером столбца, в котором он находится.";
    }

    void Task1::solve() {
        for (size_t i = 0; i < matrix.getRows(); ++i) {
            if (matrix.getCols() == 0) continue;
            
            int max_val = matrix[i][0];
            size_t max_idx = 0;
            
            for (size_t j = 1; j < matrix.getCols(); ++j) {
                if (matrix[i][j] > max_val) {
                    max_val = matrix[i][j];
                    max_idx = j;
                }
            }
            
            matrix[i][max_idx] = static_cast<int>(max_idx);
        }
    }
}
