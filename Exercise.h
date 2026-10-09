/**
 * @file Exercise.h
 * @brief Базовый абстрактный класс для заданий над матрицей
 */

#pragma once

#include "Matrix.h"
#include <string>

namespace miit::algebra {

    /**
     * @brief Абстрактный базовый класс задания
     *
     * Хранит матрицу и предоставляет методы для решения задачи и получения описания.
     */
    class Exercise {
    protected:
        Matrix<int> matrix; ///< Матрица, над которой выполняется операция

    public:
        /**
         * @brief Параметризованный конструктор
         * @param mat Исходная матрица для выполнения задания
         */
        explicit Exercise(const Matrix<int>& mat);

        /**
         * @brief Виртуальный деструктор
         */
        virtual ~Exercise() = default;

        /**
         * @brief Возвращает текущее состояние матрицы
         * @return Константная ссылка на матрицу
         */
        const Matrix<int>& getMatrix() const;

        /**
         * @brief Возвращает описание формулировки задачи
         * @return Строка с описанием задачи
         */
        virtual std::string getDescription() const = 0;

        /**
         * @brief Выполняет алгоритм преобразования матрицы согласно варианту
         */
        virtual void solve() = 0;
    };

} // namespace miit::algebra
