#pragma once

#include <array>

#include "region.hpp"

namespace solver {

class SuperRegion {
public:
    SuperRegion(std::array<Region*, 3> members);

    void restrict_between(int i);
    void restrict_within(int i);

private:
    std::array<Region*, 3> regions;
};

}
