/**
 * @file IStreamGenerator.h
 * @brief Генератор значений из потока ввода (std::istream)
 */

#pragma once

#include "Generator.h"
#include <iostream>

namespace miit::algebra {

    /**
     * @brief Класс для генерации значений путем чтения из потока ввода
     *
     * Наследник класса Generator, считывающий числа из стандартного
     * или любого переданного потока ввода (например, клавиатура или файл).
     */
    class IStreamGenerator : public Generator {
    private:
        std::istream& in; ///< Ссылка на поток ввода

    public:
        /**
         * @brief Конструктор генератора потока ввода
         * @param in Поток ввода для чтения значений (по умолчанию std::cin)
         */
        IStreamGenerator(std::istream& in = std::cin);

        /**
         * @brief Считывает очередное значение из потока ввода
         * @return Считанное целое число
         * @throws std::runtime_error если поток ввода находится в состоянии ошибки
         */
        int generate() override;
    };

} // namespace miit::algebra
