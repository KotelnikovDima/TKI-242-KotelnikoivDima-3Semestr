#include "ConstantGenerator.h"

namespace miit::algebra {
    ConstantGenerator::ConstantGenerator(int value) : value(value) {}

    int ConstantGenerator::generate() {
        return value;
    }

    void ConstantGenerator::setValue(int val) {
        value = val;
    }
}
