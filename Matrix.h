/**
 * @file Matrix.h
 * @brief Шаблонный класс динамической двумерной матрицы
 */

#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
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
        Matrix() : rows(0), cols(0) {}

        /**
         * @brief Параметризованный конструктор
         * @param rows Количество строк матрицы
         * @param cols Количество столбцов матрицы
         */
        Matrix(const size_t rows, const size_t cols) : rows(rows), cols(cols) {
            data.resize(rows, std::vector<T>(cols, T()));
        }

        /**
         * @brief Деструктор по умолчанию
         */
        ~Matrix() = default;

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
        size_t getRows() const {
            return data.size();
        }

        /**
         * @brief Получить количество столбцов матрицы
         * @return Количество столбцов
         */
        size_t getCols() const {
            return cols;
        }

        /**
         * @brief Оператор индексации строки (неконстантный)
         * @param index Индекс строки
         * @return Ссылка на вектор строки
         * @throws std::out_of_range если индекс строки вне диапазона
         */
        std::vector<T>& operator[](const size_t index) {
            if (index >= data.size()) {
                throw std::out_of_range("Индекс строки матрицы выходит за пределы диапазона");
            }
            return data[index];
        }

        /**
         * @brief Оператор индексации строки (константный)
         * @param index Индекс строки
         * @return Константная ссылка на вектор строки
         * @throws std::out_of_range если индекс строки вне диапазона
         */
        const std::vector<T>& operator[](const size_t index) const {
            if (index >= data.size()) {
                throw std::out_of_range("Индекс строки матрицы выходит за пределы диапазона");
            }
            return data[index];
        }

        /**
         * @brief Циклический сдвиг элементов строк матрицы влево
         * @param shift Величина сдвига
         * @return Ссылка на текущую матрицу
         */
        Matrix& operator<<(const size_t shift) {
            if (cols == 0 || shift % cols == 0) return *this;
            size_t actualShift = shift % cols;
            for (auto& row : data) {
                std::vector<T> newRow(cols);
                for (size_t i = 0; i < cols; ++i) {
                    newRow[i] = row[(i + actualShift) % cols];
                }
                row = newRow;
            }
            return *this;
        }

        /**
         * @brief Циклический сдвиг элементов строк матрицы вправо
         * @param shift Величина сдвига
         * @return Ссылка на текущую матрицу
         */
        Matrix& operator>>(const size_t shift) {
            if (cols == 0 || shift % cols == 0) return *this;
            size_t actualShift = shift % cols;
            for (auto& row : data) {
                std::vector<T> newRow(cols);
                for (size_t i = 0; i < cols; ++i) {
                    newRow[(i + actualShift) % cols] = row[i];
                }
                row = newRow;
            }
            return *this;
        }

        /**
         * @brief Заполнение матрицы с помощью переданного генератора
         * @param generator Ссылка на объект Generator
         */
        void fill(const Generator& generator) {
            for (size_t i = 0; i < data.size(); ++i) {
                for (size_t j = 0; j < cols; ++j) {
                    data[i][j] = generator.generate();
                }
            }
        }

        /**
         * @brief Преобразование содержимого матрицы в форматированную строку
         * @return Строковое представление матрицы
         */
        std::string toString() const {
            std::stringstream ss;
            for (const auto& row : data) {
                for (const auto& elem : row) {
                    ss << elem << " ";
                }
                ss << "\n";
            }
            return ss.str();
        }

        /**
         * @brief Вставляет новую строку по указанному индексу
         * @param index Позиция для вставки новой строки
         * @param row Вектор вставляемых элементов (длина должна совпадать с количеством столбцов)
         * @throws std::invalid_argument если размер вставляемой строки не совпадает с числом столбцов
         * @throws std::out_of_range если индекс вставки выходит за границы
         */
        void insertRow(const size_t index, const std::vector<T>& row) {
            if (index > data.size()) {
                throw std::out_of_range("Индекс вставки выходит за границы");
            }
            if (cols > 0 && row.size() != cols) {
                throw std::invalid_argument("Размер вставляемой строки не совпадает с числом столбцов");
            }
            data.insert(data.begin() + index, row);
            rows = data.size();
            if (cols == 0) cols = row.size();
        }

        /**
         * @brief Удаляет строку матрицы по указанному индексу
         * @param index Индекс удаляемой строки
         * @throws std::out_of_range если индекс выходит за границы диапазона строк
         */
        void removeRow(const size_t index) {
            if (index >= data.size()) {
                throw std::out_of_range("Индекс удаляемой строки выходит за границы диапазона");
            }
            data.erase(data.begin() + index);
            rows = data.size();
        }
    };

} // namespace miit::algebra
