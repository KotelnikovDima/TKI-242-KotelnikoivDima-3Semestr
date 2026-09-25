/**
 * @file RandomGenerator.h
 * @brief Генератор случайных чисел в заданном диапазоне
 */

#pragma once

#include "Generator.h"
#include <random>

namespace miit::algebra {

    /**
     * @brief Класс для генерации псевдослучайных целых чисел
     *
     * Использует генератор std::mt19937 (Вихрь Мерсенна) и равномерное распределение
     * std::uniform_int_distribution в заданном диапазоне [min, max].
     */
    class RandomGenerator : public Generator {
    private:
        std::uniform_int_distribution<int> distribution; ///< Равномерное распределение
        std::mt19937 generator;                         ///< Генератор случайных чисел

    public:
        /**
         * @brief Конструктор генератора случайных чисел
         * @param min Минимальная граница диапазона генерации
         * @param max Максимальная граница диапазона генерации
         */
        RandomGenerator(int min, int max);

        /**
         * @brief Генерирует случайное число из заданного диапазона
         * @return Сгенерированное случайное целое число
         */
        int generate() override;
    };

} // namespace miit::algebra
