#pragma once

#include <array>

#include "options.hpp"

namespace solver {

class Region {
public:
    Region(std::array<Options*, 9> members);

    Options available_in_segment(int segment) const;

    void eliminate();
    void exclude();

private:
    std::array<Options*, 9> members;

    Options available;
};

}
