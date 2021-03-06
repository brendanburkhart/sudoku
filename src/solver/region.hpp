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
    void restrict_to_segment(int segment, const Options& options);
    void exclude_from_segment(int segment, const Options& options);

private:
    std::array<Options*, 9> members;

    Options available;
};

}
