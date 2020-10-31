#pragma once

#include <array>

#include "cell.hpp"

namespace solver {

class Region {
public:
    Region(std::array<Cell*, 9> members);

    void eliminate();
    void update();
    
private:
    std::array<Cell*, 9> members;

    Options available;
};

}
