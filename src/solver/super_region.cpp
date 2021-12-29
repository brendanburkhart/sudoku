#include "super_region.hpp"

namespace solver {

SuperRegion::SuperRegion(std::array<Region*, 3> regions) : regions(regions) {}

void SuperRegion::restrict_between(int i) {
    const Options available0 = regions[0]->available_in_segment(i);
    const Options available1 = regions[1]->available_in_segment(i);
    const Options available2 = regions[2]->available_in_segment(i);

    Options required0 = available0;
    required0.remove(available1);
    required0.remove(available2);

    Options required1 = available1;
    required1.remove(available0);
    required1.remove(available2);

    Options required2 = available2;
    required2.remove(available0);
    required2.remove(available1);

    regions[0]->restrict_to_segment(i, required0);
    regions[1]->restrict_to_segment(i, required1);
    regions[2]->restrict_to_segment(i, required2);
}

void SuperRegion::restrict_within(int i) {
    const Options available0 = regions[i]->available_in_segment(0);
    const Options available1 = regions[i]->available_in_segment(1);
    const Options available2 = regions[i]->available_in_segment(2);

    Options required0 = available0;
    required0.remove(available1);
    required0.remove(available2);

    Options required1 = available1;
    required1.remove(available0);
    required1.remove(available2);

    Options required2 = available2;
    required2.remove(available0);
    required2.remove(available1);

    for (size_t j = 0; j < 3; j++) {
        if (i == j) {
            continue;
        }

        regions[j]->exclude_from_segment(0, required0);
        regions[j]->exclude_from_segment(1, required1);
        regions[j]->exclude_from_segment(2, required2);
    }
}

}  // namespace solver
