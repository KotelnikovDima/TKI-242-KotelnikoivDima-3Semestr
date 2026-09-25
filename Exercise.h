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
         * @brief Конструктор по умолчанию
         */
        Exercise() = default;

        /**
         * @brief Виртуальный деструктор
         */
        virtual ~Exercise() = default;

        /**
         * @brief Устанавливает рабочую матрицу
         * @param mat Исходная матрица
         */
        void setMatrix(const Matrix<int>& mat);

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
