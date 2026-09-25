/**
 * @file ConstantGenerator.h
 * @brief Генератор константного значения
 */

#pragma once

#include "Generator.h"

namespace miit::algebra {

    /**
     * @brief Класс для генерации одинаковых (константных) значений
     *
     * Наследник класса Generator, возвращающий заданное фиксированное число.
     */
    class ConstantGenerator : public Generator {
    private:
        int value; ///< Фиксированное значение

    public:
        /**
         * @brief Конструктор генератора констант
         * @param value Фиксированное значение для генерации (по умолчанию 0)
         */
        ConstantGenerator(int value = 0);

        /**
         * @brief Возвращает заданное константное значение
         * @return Фиксированное число
         */
        int generate() override;

        /**
         * @brief Устанавливает новое константное значение
         * @param val Новое значение
         */
        void setValue(int val);
    };

} // namespace miit::algebra
