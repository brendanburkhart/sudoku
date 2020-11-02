#include "super_region.hpp"

namespace solver {

SuperRegion::SuperRegion(std::array<Region*, 3> regions) : regions(regions) {}

void SuperRegion::restrict() {
	for (size_t i = 0; i < 3; i++) {
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
}

}
