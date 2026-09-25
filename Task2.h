/**
 * @file Task2.h
 * @brief Задание 2 (Вариант 15): вставка строки 2, 4, 6... после строк с минимальным элементом
 */

#pragma once

#include "Exercise.h"

namespace miit::algebra {

    /**
     * @brief Класс для реализации Задачи 2 (Вариант 15)
     *
     * Формулировка: Вставить после всех строк, содержащих минимальный элемент массива,
     * строку 2, 4, 6, …
     */
    class Task2 : public Exercise {
    public:
        /**
         * @brief Конструктор по умолчанию
         */
        Task2() = default;

        /**
         * @brief Возвращает описание Задачи 2
         * @return Строка с описанием условия задачи
         */
        std::string getDescription() const override;

        /**
         * @brief Выполняет алгоритм вставки строки четных чисел после строк с минимумом
         */
        void solve() override;
    };

} // namespace miit::algebra
