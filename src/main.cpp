#include <iostream>

#include "solver/options.hpp"

int main() {
    Options options(3);

    std::cout << options.contains(3) << std::endl;
}
