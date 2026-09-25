#include "IStreamGenerator.h"

namespace miit::algebra {
    IStreamGenerator::IStreamGenerator(std::istream& in) : in(in) {}

    int IStreamGenerator::generate() {
        int val = 0;
        in >> val;
        return val;
    }
}
