#include "Matrix.h"
#include <sstream>
#include <stdexcept>

namespace miit::algebra {
    template <typename T>
    Matrix<T>::Matrix() : rows(0), cols(0) {}

    template <typename T>
    Matrix<T>::Matrix(const size_t rows, const size_t cols) : rows(rows), cols(cols) {
        data.resize(rows, std::vector<T>(cols, T()));
    }

    template <typename T>
    size_t Matrix<T>::getRows() const { return rows; }

    template <typename T>
    size_t Matrix<T>::getCols() const { return cols; }

    template <typename T>
    std::vector<T>& Matrix<T>::operator[](const size_t index) {
        if (index >= rows) {
            throw std::out_of_range("Индекс строки матрицы выходит за пределы диапазона");
        }
        return data[index];
    }

    template <typename T>
    const std::vector<T>& Matrix<T>::operator[](const size_t index) const {
        if (index >= rows) {
            throw std::out_of_range("Индекс строки матрицы выходит за пределы диапазона");
        }
        return data[index];
    }

    template <typename T>
    Matrix<T>& Matrix<T>::operator<<(const size_t shift) {
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

    template <typename T>
    Matrix<T>& Matrix<T>::operator>>(const size_t shift) {
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

    template <typename T>
    void Matrix<T>::fill(const Generator& generator) {
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                data[i][j] = generator.generate();
            }
        }
    }

    template <typename T>
    std::string Matrix<T>::toString() const {
        std::stringstream ss;
        for (const auto& row : data) {
            for (const auto& elem : row) {
                ss << elem << " ";
            }
            ss << "\n";
        }
        return ss.str();
    }

    template <typename T>
    void Matrix<T>::insertRow(const size_t index, const std::vector<T>& row) {
        if (index > rows) {
            throw std::out_of_range("Индекс вставки выходит за границы");
        }
        if (cols > 0 && row.size() != cols) {
            throw std::invalid_argument("Размер вставляемой строки не совпадает с числом столбцов");
        }
        data.insert(data.begin() + index, row);
        rows++;
        if (cols == 0) cols = row.size();
    }

    template <typename T>
    void Matrix<T>::removeRow(const size_t index) {
        if (index >= rows) {
            throw std::out_of_range("Индекс удаляемой строки выходит за границы диапазона");
        }
        data.erase(data.begin() + index);
        rows--;
    }

    template class Matrix<int>;
}
