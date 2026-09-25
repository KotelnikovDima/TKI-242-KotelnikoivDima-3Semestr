/**
 * @file Generator.h
 * @brief Базовый абстрактный класс для генераторов значений матрицы
 */

#pragma once

namespace miit::algebra {

    /**
     * @brief Абстрактный базовый класс генератора данных
     *
     * Определяет интерфейс для генерации целочисленных значений,
     * используемых при заполнении матрицы.
     */
    class Generator {
    public:
        /**
         * @brief Виртуальный деструктор по умолчанию
         */
        virtual ~Generator() = default;

        /**
         * @brief Генерирует очередное целочисленное значение
         * @return Сгенерированное целое число
         */
        virtual int generate() = 0;
    };

} // namespace miit::algebra
