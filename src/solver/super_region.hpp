#pragma once

#include <array>

#include "region.hpp"

namespace solver {

class SuperRegion {
public:
    SuperRegion(std::array<Region*, 3> members);

    void restrict();

private:
    std::array<Region*, 3> regions;
};

}
