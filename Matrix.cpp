#include "Matrix.h"
#include <sstream>
#include <stdexcept>

namespace miit::algebra {
    template <typename T>
    Matrix<T>::Matrix() : rows(0), cols(0) {}

    template <typename T>
    Matrix<T>::Matrix(size_t rows, size_t cols) : rows(rows), cols(cols) {
        data.resize(rows, std::vector<T>(cols, T()));
    }

    template <typename T>
    size_t Matrix<T>::getRows() const { return rows; }

    template <typename T>
    size_t Matrix<T>::getCols() const { return cols; }

    template <typename T>
    std::vector<T>& Matrix<T>::operator[](size_t index) { return data.at(index); }

    template <typename T>
    const std::vector<T>& Matrix<T>::operator[](size_t index) const { return data.at(index); }

    template <typename T>
    Matrix<T>& Matrix<T>::operator<<(size_t shift) {
        if (cols == 0 || shift % cols == 0) return *this;
        shift %= cols;
        for (auto& row : data) {
            std::vector<T> newRow(cols);
            for (size_t i = 0; i < cols; ++i) {
                newRow[i] = row[(i + shift) % cols];
            }
            row = newRow;
        }
        return *this;
    }

    template <typename T>
    Matrix<T>& Matrix<T>::operator>>(size_t shift) {
        if (cols == 0 || shift % cols == 0) return *this;
        shift %= cols;
        for (auto& row : data) {
            std::vector<T> newRow(cols);
            for (size_t i = 0; i < cols; ++i) {
                newRow[(i + shift) % cols] = row[i];
            }
            row = newRow;
        }
        return *this;
    }

    template <typename T>
    void Matrix<T>::fill(Generator& generator) {
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
    std::unique_ptr<Matrix<T>> Matrix<T>::clone() const {
        return std::make_unique<Matrix<T>>(*this);
    }

    template <typename T>
    void Matrix<T>::insertRow(size_t index, const std::vector<T>& row) {
        if (index > rows || (cols > 0 && row.size() != cols)) {
            throw std::invalid_argument("Invalid row insertion");
        }
        data.insert(data.begin() + index, row);
        rows++;
        if (cols == 0) cols = row.size();
    }

    template <typename T>
    void Matrix<T>::removeRow(size_t index) {
        if (index >= rows) {
            throw std::out_of_range("Invalid row removal");
        }
        data.erase(data.begin() + index);
        rows--;
    }

    template class Matrix<int>;
}
