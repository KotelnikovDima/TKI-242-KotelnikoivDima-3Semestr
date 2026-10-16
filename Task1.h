/**
 * @file Task1.h
 * @brief Задание 1 (Вариант 15): замена максимального элемента строки номером столбца
 */

#pragma once

#include "Exercise.h"

namespace miit::algebra {

    /**
     * @brief Класс для реализации Задачи 1 (Вариант 15)
     *
     * Формулировка: Заменить максимальный элемент каждой строки номером столбца,
     * в которой он находится.
     */
    class Task1 : public Exercise {
    public:
        /**
         * @brief Конструктор с параметром матрица
         * @param mat Исходная матрица
         */
        explicit Task1(const Matrix<int>& mat);

        /**
         * @brief Возвращает описание Задачи 1
         * @return Строка с описанием условия задачи
         */
        std::string getDescription() const override;

        /**
         * @brief Выполняет алгоритм замены максимального элемента строки номером столбца
         */
        void solve() override;
    };

} // namespace miit::algebra
