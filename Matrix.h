/**
 * @file Matrix.h
 * @brief Шаблонный класс динамической двумерной матрицы
 */

#pragma once

#include <vector>
#include <string>
#include <memory>
#include "Generator.h"

namespace miit::algebra {

    /**
     * @brief Шаблонный класс двумерного динамического массива (матрицы)
     * @tparam T Тип элементов матрицы (по умолчанию int)
     */
    template <typename T>
    class Matrix {
    private:
        size_t rows;                       ///< Количество строк
        size_t cols;                       ///< Количество столбцов
        std::vector<std::vector<T>> data;  ///< Двумерный контейнер данных

    public:
        /**
         * @brief Конструктор по умолчанию (создает пустую матрицу 0x0)
         */
        Matrix();

        /**
         * @brief Параметризованный конструктор
         * @param rows Количество строк матрицы
         * @param cols Количество столбцов матрицы
         */
        Matrix(size_t rows, size_t cols);

        /**
         * @brief Виртуальный деструктор по умолчанию
         */
        virtual ~Matrix() = default;

        /**
         * @brief Конструктор копирования
         * @param other Копируемая матрица
         */
        Matrix(const Matrix& other) = default;

        /**
         * @brief Конструктор перемещения
         * @param other Перемещаемая матрица
         */
        Matrix(Matrix&& other) noexcept = default;

        /**
         * @brief Оператор копирующего присваивания
         * @param other Копируемая матрица
         * @return Ссылка на текущий объект
         */
        Matrix& operator=(const Matrix& other) = default;

        /**
         * @brief Оператор перемещающего присваивания
         * @param other Перемещаемая матрица
         * @return Ссылка на текущий объект
         */
        Matrix& operator=(Matrix&& other) noexcept = default;

        /**
         * @brief Получить количество строк матрицы
         * @return Количество строк
         */
        size_t getRows() const;

        /**
         * @brief Получить количество столбцов матрицы
         * @return Количество столбцов
         */
        size_t getCols() const;

        /**
         * @brief Оператор индексации строки (неконстантный)
         * @param index Индекс строки
         * @return Ссылка на вектор строки
         * @throws std::out_of_range если индекс строки вне диапазона
         */
        std::vector<T>& operator[](size_t index);

        /**
         * @brief Оператор индексации строки (константный)
         * @param index Индекс строки
         * @return Константная ссылка на вектор строки
         * @throws std::out_of_range если индекс строки вне диапазона
         */
        const std::vector<T>& operator[](size_t index) const;

        /**
         * @brief Циклический сдвиг элементов строк матрицы влево
         * @param shift Величина сдвига
         * @return Ссылка на текущую матрицу
         */
        Matrix& operator<<(size_t shift);

        /**
         * @brief Циклический сдвиг элементов строк матрицы вправо
         * @param shift Величина сдвига
         * @return Ссылка на текущую матрицу
         */
        Matrix& operator>>(size_t shift);

        /**
         * @brief Заполнение матрицы с помощью переданного генератора
         * @param generator Ссылка на объект Generator
         */
        void fill(Generator& generator);

        /**
         * @brief Преобразование содержимого матрицы в форматированную строку
         * @return Строковое представление матрицы
         */
        std::string toString() const;

        /**
         * @brief Создает глубокую копию матрицы в динамической памяти
         * @return Умный указатель std::unique_ptr на новую копию матрицы
         */
        std::unique_ptr<Matrix<T>> clone() const;

        /**
         * @brief Вставляет новую строку по указанному индексу
         * @param index Позиция для вставки новой строки
         * @param row Вектор вставляемых элементов (длина должна совпадать с количеством столбцов)
         * @throws std::invalid_argument если размер вставляемой строки не совпадает с числом столбцов
         * @throws std::out_of_range если индекс вставки выходит за границы
         */
        void insertRow(size_t index, const std::vector<T>& row);

        /**
         * @brief Удаляет строку матрицы по указанному индексу
         * @param index Индекс удаляемой строки
         * @throws std::out_of_range если индекс выходит за границы диапазона строк
         */
        void removeRow(size_t index);
    };

} // namespace miit::algebra
