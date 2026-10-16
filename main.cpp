#include <iostream>
#include <string>
#include <windows.h>
#include "Matrix.h"
#include "RandomGenerator.h"
#include "IStreamGenerator.h"
#include "ConstantGenerator.h"
#include "Task1.h"
#include "Task2.h"


using namespace miit::algebra;

// Именованные константы для способов заполнения матрицы
constexpr int FILL_RANDOM = 1;
constexpr int FILL_MANUAL = 2;
constexpr int FILL_CONSTANT = 3;

int main() {
    // Включение кодировки UTF-8 (65001) в консоли Windows
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    std::cout << "=============================================\n";
    std::cout << "  Лабораторная работа 1 (Вариант 15)\n";
    std::cout << "=============================================\n";

    try {
        std::cout << "\nВведите количество строк: ";
        size_t rows; std::cin >> rows;
        std::cout << "Введите количество столбцов: ";
        size_t cols; std::cin >> cols;

        Matrix<int> matrix(rows, cols);

        std::cout << "\nВыберите способ заполнения:\n"
                  << FILL_RANDOM << " - Случайные числа\n"
                  << FILL_MANUAL << " - Ручной ввод\n"
                  << FILL_CONSTANT << " - Константа\n"
                  << "Ваш выбор: ";
        int fillChoice; std::cin >> fillChoice;

        switch (fillChoice) {
            case FILL_RANDOM: {
                int minVal, maxVal;
                std::cout << "Минимум: "; std::cin >> minVal;
                std::cout << "Максимум: "; std::cin >> maxVal;
                RandomGenerator gen(minVal, maxVal);
                matrix.fill(gen);
                break;
            }
            case FILL_MANUAL: {
                std::cout << "Введите элементы матрицы через пробел:\n";
                IStreamGenerator gen(std::cin);
                matrix.fill(gen);
                break;
            }
            case FILL_CONSTANT: {
                int val;
                std::cout << "Введите значение константы: ";
                std::cin >> val;
                ConstantGenerator gen(val);
                matrix.fill(gen);
                break;
            }
            default: {
                std::cout << "Неверный выбор способа заполнения!\n";
                return 1;
            }
        }

        std::cout << "\nИсходная матрица:\n" << matrix.toString() << "\n";

        std::cout << "=== Задача 1 ===\n";
        Task1 task1(matrix);
        std::cout << "Описание: " << task1.getDescription() << "\n\n";
        task1.solve();
        std::cout << "Результат:\n" << task1.getMatrix().toString() << "\n";

        std::cout << "=== Задача 2 ===\n";
        Task2 task2(matrix);
        std::cout << "Описание: " << task2.getDescription() << "\n\n";
        task2.solve();
        std::cout << "Результат:\n" << task2.getMatrix().toString() << "\n";

    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "\nНажмите Enter для выхода...";
    std::cin.ignore();
    std::cin.get();

    return 0;
}
