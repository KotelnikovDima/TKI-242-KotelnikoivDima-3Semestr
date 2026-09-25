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

void demonstrateExercise(Exercise& exercise, const Matrix<int>& original, const std::string& taskName) {
    std::cout << "\n=== " << taskName << " ===\n";
    std::cout << "Описание: " << exercise.getDescription() << "\n\n";

    std::cout << "Исходная матрица:\n";
    std::cout << original.toString() << "\n";

    exercise.setMatrix(original);
    exercise.solve();

    std::cout << "Результат:\n";
    std::cout << exercise.getMatrix().toString() << "\n";
}

int main() {
    // Включение кодировки UTF-8 (65001) в консоли Windows
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    std::cout << "=============================================\n";
    std::cout << "  Лабораторная работа 1 (Вариант 15)\n";
    std::cout << "=============================================\n";
    std::cout << "";
    
    

    

    try {
        std::cout << "\nВведите количество строк: ";
        size_t rows; std::cin >> rows;
        std::cout << "Введите количество столбцов: ";
        size_t cols; std::cin >> cols;

        Matrix<int> matrix(rows, cols);

        std::cout << "\nВыберите способ заполнения:\n"
                  << "1 - Случайные числа\n"
                  << "2 - Ручной ввод\n"
                  << "3 - Константа\n"
                  << "Ваш выбор: ";
        int fillChoice; std::cin >> fillChoice;

        if (fillChoice == 1) {
            int minVal, maxVal;
            std::cout << "Минимум: "; std::cin >> minVal;
            std::cout << "Максимум: "; std::cin >> maxVal;
            RandomGenerator gen(minVal, maxVal);
            matrix.fill(gen);
        } else if (fillChoice == 2) {
            std::cout << "Введите элементы матрицы через пробел:\n";
            IStreamGenerator gen(std::cin);
            matrix.fill(gen);
        } else {
            std::cout << "Введите значение константы: ";
            int val; std::cin >> val;
            ConstantGenerator gen(val);
            matrix.fill(gen);
        }

        std::cout << "\nСозданная матрица:\n" << matrix.toString() << "\n";

        Task1 task1;
        demonstrateExercise(task1, matrix, "Задача 1");

        Task2 task2;
        demonstrateExercise(task2, matrix, "Задача 2");

    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "\nНажмите Enter для выхода...";
    std::cin.ignore();
    std::cin.get();

    return 0;
}
