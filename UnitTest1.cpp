#include <gtest/gtest.h>
#include <sstream>
#include <stdexcept>
#include <memory>
#include <vector>
#include "Matrix.h"
#include "Task1.h"
#include "Task2.h"
#include "ConstantGenerator.h"
#include "IStreamGenerator.h"
#include "RandomGenerator.h"

using namespace miit::algebra;

// ============================================================
// 1. Тесты конструкторов Matrix
// ============================================================
TEST(MatrixConstructorTests, DefaultConstructor_CreatesEmptyMatrix)
{
    Matrix<int> m;
    EXPECT_EQ((size_t)0, m.getRows());
    EXPECT_EQ((size_t)0, m.getCols());
}

TEST(MatrixConstructorTests, ParameterizedConstructor_CreatesCorrectSize)
{
    Matrix<int> m(3, 4);
    EXPECT_EQ((size_t)3, m.getRows());
    EXPECT_EQ((size_t)4, m.getCols());
}

TEST(MatrixConstructorTests, ParameterizedConstructor_InitializesWithZeros)
{
    Matrix<int> m(5, 5);
    for (size_t i = 0; i < m.getRows(); i++) {
        for (size_t j = 0; j < m.getCols(); j++) {
            EXPECT_EQ(0, m[i][j]);
        }
    }
}

TEST(MatrixConstructorTests, ParameterizedConstructor_SingleElement)
{
    Matrix<int> m(1, 1);
    EXPECT_EQ((size_t)1, m.getRows());
    EXPECT_EQ((size_t)1, m.getCols());
    EXPECT_EQ(0, m[0][0]);
}

TEST(MatrixConstructorTests, CopyConstructor_CopiesDimensionsAndData)
{
    Matrix<int> m1(2, 2);
    m1[0][0] = 5; m1[0][1] = 10;
    m1[1][0] = 15; m1[1][1] = 20;
    
    Matrix<int> m2(m1);
    EXPECT_EQ(m1.getRows(), m2.getRows());
    EXPECT_EQ(m1.getCols(), m2.getCols());
    EXPECT_EQ(5, m2[0][0]);
    EXPECT_EQ(20, m2[1][1]);
}

TEST(MatrixConstructorTests, CopyConstructor_DeepCopy)
{
    Matrix<int> m1(2, 2);
    m1[0][0] = 5;
    
    Matrix<int> m2(m1);
    m2[0][0] = 100;
    
    EXPECT_EQ(5, m1[0][0]); // Оригинал не изменился
    EXPECT_EQ(100, m2[0][0]);
}

TEST(MatrixConstructorTests, MoveConstructor_TransfersOwnership)
{
    Matrix<int> m1(2, 2);
    m1[0][0] = 7;
    
    Matrix<int> m2(std::move(m1));
    EXPECT_EQ((size_t)2, m2.getRows());
    EXPECT_EQ(7, m2[0][0]);
}

// ============================================================
// 2. Тесты операторов присваивания и индексации
// ============================================================
TEST(MatrixOperatorsTests, CopyAssignment_SelfAssignment)
{
    Matrix<int> m(2, 2);
    m[0][0] = 42;
    m = m;
    EXPECT_EQ(42, m[0][0]);
}

TEST(MatrixOperatorsTests, CopyAssignment_DeepCopy)
{
    Matrix<int> m1(2, 2);
    m1[1][1] = 42;
    
    Matrix<int> m2;
    m2 = m1;
    
    EXPECT_EQ((size_t)2, m2.getRows());
    EXPECT_EQ(42, m2[1][1]);
    
    m2[1][1] = 99;
    EXPECT_EQ(42, m1[1][1]); 
}

TEST(MatrixOperatorsTests, MoveAssignment_TransfersData)
{
    Matrix<int> m1(3, 3);
    m1[2][2] = 84;
    
    Matrix<int> m2;
    m2 = std::move(m1);
    
    EXPECT_EQ((size_t)3, m2.getRows());
    EXPECT_EQ(84, m2[2][2]);
}

TEST(MatrixOperatorsTests, OperatorBrackets_ValidIndex)
{
    Matrix<int> m(2, 2);
    m[1][0] = 123;
    EXPECT_EQ(123, m[1][0]);
}

TEST(MatrixOperatorsTests, OperatorBrackets_OutOfRange)
{
    Matrix<int> m(2, 2);
    EXPECT_THROW({
        m[5][0] = 1;
    }, std::out_of_range);
}

// ============================================================
// 3. Тесты базовых методов (clone, toString, insert, remove)
// ============================================================
TEST(MatrixMethodsTests, Clone_CreatesExactCopy)
{
    Matrix<int> m1(2, 2);
    m1[0][1] = 77;
    
    auto m2 = m1.clone();
    EXPECT_EQ((size_t)2, m2->getRows());
    EXPECT_EQ(77, (*m2)[0][1]);
    
    (*m2)[0][1] = 88;
    EXPECT_EQ(77, m1[0][1]);
}

TEST(MatrixMethodsTests, ToString_FormatsCorrectly)
{
    Matrix<int> m(2, 2);
    m[0][0] = 1; m[0][1] = 2;
    m[1][0] = 3; m[1][1] = 4;
    
    std::string expected = "1 2 \n3 4 \n";
    EXPECT_EQ(expected, m.toString());
}

TEST(MatrixMethodsTests, ToString_EmptyMatrix)
{
    Matrix<int> m;
    EXPECT_EQ(std::string(""), m.toString());
}

TEST(MatrixMethodsTests, InsertRow_ValidIndex)
{
    Matrix<int> m(1, 2);
    m[0][0] = 1; m[0][1] = 2;
    
    std::vector<int> newRow = {3, 4};
    m.insertRow(1, newRow);
    
    EXPECT_EQ((size_t)2, m.getRows());
    EXPECT_EQ(3, m[1][0]);
    EXPECT_EQ(4, m[1][1]);
}

TEST(MatrixMethodsTests, InsertRow_AtBeginning)
{
    Matrix<int> m(1, 2);
    m[0][0] = 1; m[0][1] = 2;
    
    std::vector<int> newRow = {9, 9};
    m.insertRow(0, newRow);
    
    EXPECT_EQ((size_t)2, m.getRows());
    EXPECT_EQ(9, m[0][0]);
    EXPECT_EQ(1, m[1][0]);
}

TEST(MatrixMethodsTests, InsertRow_InvalidSize)
{
    Matrix<int> m(1, 2);
    std::vector<int> newRow = {1, 2, 3}; // Неверный размер
    
    EXPECT_THROW({
        m.insertRow(1, newRow);
    }, std::invalid_argument);
}

TEST(MatrixMethodsTests, InsertRow_InvalidIndex)
{
    Matrix<int> m(1, 2);
    std::vector<int> newRow = {1, 2};
    
    EXPECT_THROW({
        m.insertRow(5, newRow);
    }, std::invalid_argument);
}

TEST(MatrixMethodsTests, RemoveRow_ValidIndex)
{
    Matrix<int> m(2, 2);
    m[0][0] = 1; m[1][0] = 2;
    
    m.removeRow(0);
    
    EXPECT_EQ((size_t)1, m.getRows());
    EXPECT_EQ(2, m[0][0]);
}

TEST(MatrixMethodsTests, RemoveRow_InvalidIndex)
{
    Matrix<int> m(1, 2);
    EXPECT_THROW({
        m.removeRow(1);
    }, std::out_of_range);
}

// ============================================================
// 4. Тесты операторов циклического сдвига (<< и >>)
// ============================================================
TEST(MatrixShiftTests, ShiftLeft_Basic)
{
    Matrix<int> m(2, 3);
    m[0][0] = 1; m[0][1] = 2; m[0][2] = 3;
    m[1][0] = 4; m[1][1] = 5; m[1][2] = 6;
    
    m << 1;
    
    EXPECT_EQ(2, m[0][0]);
    EXPECT_EQ(3, m[0][1]);
    EXPECT_EQ(1, m[0][2]);
    
    EXPECT_EQ(5, m[1][0]);
    EXPECT_EQ(6, m[1][1]);
    EXPECT_EQ(4, m[1][2]);
}

TEST(MatrixShiftTests, ShiftRight_Basic)
{
    Matrix<int> m(2, 3);
    m[0][0] = 1; m[0][1] = 2; m[0][2] = 3;
    
    m >> 1;
    
    EXPECT_EQ(3, m[0][0]);
    EXPECT_EQ(1, m[0][1]);
    EXPECT_EQ(2, m[0][2]);
}

TEST(MatrixShiftTests, ShiftLeft_ByMultipleOfCols)
{
    Matrix<int> m(1, 3);
    m[0][0] = 1; m[0][1] = 2; m[0][2] = 3;
    
    m << 3; 
    EXPECT_EQ(1, m[0][0]);
    EXPECT_EQ(2, m[0][1]);
    
    m << 6;
    EXPECT_EQ(1, m[0][0]);
}

TEST(MatrixShiftTests, ShiftRight_ByMultipleOfCols)
{
    Matrix<int> m(1, 3);
    m[0][0] = 1; m[0][1] = 2; m[0][2] = 3;
    
    m >> 3; 
    EXPECT_EQ(1, m[0][0]);
    EXPECT_EQ(2, m[0][1]);
}

TEST(MatrixShiftTests, ShiftLeft_ZeroShift)
{
    Matrix<int> m(1, 3);
    m[0][0] = 1; m[0][1] = 2; m[0][2] = 3;
    m << 0;
    EXPECT_EQ(1, m[0][0]);
    EXPECT_EQ(2, m[0][1]);
}

TEST(MatrixShiftTests, ShiftLeft_EmptyMatrix)
{
    Matrix<int> m;
    m << 2;
    EXPECT_EQ((size_t)0, m.getRows());
}

// ============================================================
// 5. Тесты всех генераторов
// ============================================================
TEST(GeneratorsTests, ConstantGenerator_Positive)
{
    ConstantGenerator gen(42);
    EXPECT_EQ(42, gen.generate());
}

TEST(GeneratorsTests, ConstantGenerator_Negative)
{
    ConstantGenerator gen(-100);
    EXPECT_EQ(-100, gen.generate());
}

TEST(GeneratorsTests, ConstantGenerator_Zero)
{
    ConstantGenerator gen(0);
    EXPECT_EQ(0, gen.generate());
}

TEST(GeneratorsTests, ConstantGenerator_ChangeValue)
{
    ConstantGenerator gen(1);
    gen.setValue(99);
    EXPECT_EQ(99, gen.generate());
}

TEST(GeneratorsTests, RandomGenerator_Range)
{
    RandomGenerator gen(10, 20);
    for (int i = 0; i < 100; i++) {
        int val = gen.generate();
        EXPECT_TRUE(val >= 10 && val <= 20);
    }
}

TEST(GeneratorsTests, RandomGenerator_NegativeRange)
{
    RandomGenerator gen(-50, -10);
    for (int i = 0; i < 100; i++) {
        int val = gen.generate();
        EXPECT_TRUE(val >= -50 && val <= -10);
    }
}

TEST(GeneratorsTests, RandomGenerator_MinEqualsMax)
{
    RandomGenerator gen(5, 5);
    EXPECT_EQ(5, gen.generate());
}

TEST(GeneratorsTests, IStreamGenerator_ValidInput)
{
    std::stringstream ss("10 20 30");
    IStreamGenerator gen(ss);
    
    EXPECT_EQ(10, gen.generate());
    EXPECT_EQ(20, gen.generate());
    EXPECT_EQ(30, gen.generate());
}

TEST(GeneratorsTests, IStreamGenerator_NegativeInput)
{
    std::stringstream ss("-5 -15");
    IStreamGenerator gen(ss);
    
    EXPECT_EQ(-5, gen.generate());
    EXPECT_EQ(-15, gen.generate());
}

TEST(GeneratorsTests, MatrixFill_WithConstantGenerator)
{
    Matrix<int> m(3, 3);
    ConstantGenerator gen(7);
    m.fill(gen);
    
    for(size_t i = 0; i < m.getRows(); ++i) {
        for(size_t j = 0; j < m.getCols(); ++j) {
            EXPECT_EQ(7, m[i][j]);
        }
    }
}

// ============================================================
// 6. Тесты Задачи 1: Замена максимального элемента номером столбца
// ============================================================
TEST(Task1Tests, Solve_BasicCase)
{
    Matrix<int> m(2, 3);
    m[0][0] = 1; m[0][1] = 9; m[0][2] = 2; // max 9, col 1
    m[1][0] = 3; m[1][1] = 4; m[1][2] = 8; // max 8, col 2
    
    Task1 t;
    t.setMatrix(m);
    t.solve();
    
    const Matrix<int>& res = t.getMatrix();
    EXPECT_EQ(1, res[0][1]);
    EXPECT_EQ(2, res[1][2]);
}

TEST(Task1Tests, Solve_NegativeNumbers)
{
    Matrix<int> m(2, 2);
    m[0][0] = -5; m[0][1] = -10; // max -5, col 0
    m[1][0] = -100; m[1][1] = -2; // max -2, col 1
    
    Task1 t;
    t.setMatrix(m);
    t.solve();
    
    const Matrix<int>& res = t.getMatrix();
    EXPECT_EQ(0, res[0][0]);
    EXPECT_EQ(1, res[1][1]);
}

TEST(Task1Tests, Solve_DuplicateMaximums)
{
    Matrix<int> m(1, 4);
    m[0][0] = 1; m[0][1] = 5; m[0][2] = 5; m[0][3] = 2; 
    
    Task1 t;
    t.setMatrix(m);
    t.solve();
    
    const Matrix<int>& res = t.getMatrix();
    EXPECT_EQ(1, res[0][1]); // Заменен первый максимум
    EXPECT_EQ(5, res[0][2]); // Второй остался нетронутым
}

TEST(Task1Tests, Solve_SingleElement)
{
    Matrix<int> m(1, 1);
    m[0][0] = 99;
    
    Task1 t;
    t.setMatrix(m);
    t.solve();
    
    EXPECT_EQ(0, t.getMatrix()[0][0]);
}

TEST(Task1Tests, Solve_EmptyMatrix)
{
    Matrix<int> m;
    Task1 t;
    t.setMatrix(m);
    t.solve();
    
    EXPECT_EQ((size_t)0, t.getMatrix().getRows());
}

TEST(Task1Tests, Solve_AllZeros)
{
    Matrix<int> m(2, 2); // все нули
    Task1 t;
    t.setMatrix(m);
    t.solve();
    
    const Matrix<int>& res = t.getMatrix();
    EXPECT_EQ(0, res[0][0]); // Максимум - это 0 на 0-й позиции
    EXPECT_EQ(0, res[1][0]);
}

TEST(Task1Tests, GetDescription_IsNotEmpty)
{
    Task1 t;
    std::string desc = t.getDescription();
    EXPECT_TRUE(desc.length() > 10);
}

// ============================================================
// 7. Тесты Задачи 2: Вставка строки после строк с минимальным элементом
// ============================================================
TEST(Task2Tests, Solve_BasicCase)
{
    Matrix<int> m(2, 3);
    m[0][0] = 5; m[0][1] = 9; m[0][2] = 8;
    m[1][0] = 2; m[1][1] = 1; m[1][2] = 4; // min is 1
    
    Task2 t;
    t.setMatrix(m);
    t.solve();
    
    const Matrix<int>& res = t.getMatrix();
    EXPECT_EQ((size_t)3, res.getRows());
    
    // Проверка вставленной строки
    EXPECT_EQ(2, res[2][0]);
    EXPECT_EQ(4, res[2][1]);
    EXPECT_EQ(6, res[2][2]);
}

TEST(Task2Tests, Solve_MultipleMinima)
{
    Matrix<int> m(3, 2);
    m[0][0] = 1; m[0][1] = 5; // min is 1
    m[1][0] = 3; m[1][1] = 4;
    m[2][0] = 9; m[2][1] = 1; // min is 1
    
    Task2 t;
    t.setMatrix(m);
    t.solve();
    
    const Matrix<int>& res = t.getMatrix();
    EXPECT_EQ((size_t)5, res.getRows());
    
    // Проверка вставок
    EXPECT_EQ(2, res[1][0]);
    EXPECT_EQ(4, res[1][1]);
    EXPECT_EQ(3, res[2][0]); // Исходная строка
    EXPECT_EQ(2, res[4][0]);
    EXPECT_EQ(4, res[4][1]);
}

TEST(Task2Tests, Solve_AllElementsSame)
{
    Matrix<int> m(2, 2);
    m[0][0] = 0; m[0][1] = 0;
    m[1][0] = 0; m[1][1] = 0;
    
    Task2 t;
    t.setMatrix(m);
    t.solve();
    
    const Matrix<int>& res = t.getMatrix();
    EXPECT_EQ((size_t)4, res.getRows());
    EXPECT_EQ(2, res[1][0]); // Вставка после первой
    EXPECT_EQ(2, res[3][0]); // Вставка после второй
}

TEST(Task2Tests, Solve_MinAtStart)
{
    Matrix<int> m(2, 2);
    m[0][0] = -10; m[0][1] = 5;
    m[1][0] = 0; m[1][1] = 0;
    
    Task2 t;
    t.setMatrix(m);
    t.solve();
    
    const Matrix<int>& res = t.getMatrix();
    EXPECT_EQ((size_t)3, res.getRows());
    EXPECT_EQ(2, res[1][0]);
    EXPECT_EQ(4, res[1][1]);
    EXPECT_EQ(0, res[2][0]);
}

TEST(Task2Tests, Solve_EmptyMatrix)
{
    Matrix<int> m;
    Task2 t;
    t.setMatrix(m);
    t.solve();
    
    EXPECT_EQ((size_t)0, t.getMatrix().getRows());
}

TEST(Task2Tests, GetDescription_IsNotEmpty)
{
    Task2 t;
    std::string desc = t.getDescription();
    EXPECT_TRUE(desc.length() > 10);
}

// ============================================================
// 8. Интеграционные и стресс-тесты
// ============================================================
TEST(IntegrationAndStressTests, StressTest_Task1_LargeMatrix)
{
    size_t rows = 500;
    size_t cols = 500;
    Matrix<int> m(rows, cols);
    
    ConstantGenerator gen(1);
    m.fill(gen);
    
    m[250][499] = 999; // Уникальный максимум
    
    Task1 t;
    t.setMatrix(m);
    t.solve();
    
    EXPECT_EQ(499, t.getMatrix()[250][499]);
}

TEST(IntegrationAndStressTests, StressTest_Task2_LargeMatrix)
{
    size_t rows = 100;
    size_t cols = 10;
    Matrix<int> m(rows, cols);
    
    ConstantGenerator gen(5);
    m.fill(gen);
    
    // Делаем все элементы 5, значит минимум в каждой строке.
    // Размер увеличится вдвое.
    Task2 t;
    t.setMatrix(m);
    t.solve();
    
    EXPECT_EQ((size_t)200, t.getMatrix().getRows());
    EXPECT_EQ(2, t.getMatrix()[1][0]);
}

TEST(IntegrationAndStressTests, Integration_MultipleOperations)
{
    Matrix<int> m(3, 3);
    ConstantGenerator gen(2);
    m.fill(gen);
    
    m[0][0] = -1; // Минимум
    m[2][2] = 10; // Максимум
    
    Task1 t1;
    t1.setMatrix(m);
    t1.solve(); // В 2 строке 2 столбце заменит 10 на 2
    
    Task2 t2;
    t2.setMatrix(t1.getMatrix());
    t2.solve(); // После 0 строки (где -1) вставит строку
    
    const Matrix<int>& res = t2.getMatrix();
    EXPECT_EQ((size_t)4, res.getRows());
    EXPECT_EQ(2, res[1][0]); // Вставленная строка
    EXPECT_EQ(2, res[3][2]); // Измененный максимум
}

TEST(IntegrationAndStressTests, Validation_OriginalUnchanged)
{
    Matrix<int> original(2, 2);
    original[0][0] = 5;
    
    Task1 t;
    t.setMatrix(original); 
    t.solve(); 
    
    // Исходная матрица не должна измениться
    EXPECT_EQ(5, original[0][0]);
}
