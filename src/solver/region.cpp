#include "region.hpp"

namespace solver {

Region::Region(std::array<Cell*, 9> members) : members(members) {}

void Region::eliminate() {
    for (auto member : members) {
        available -= member->get_value();
    }

    for (auto member : members) {
        member->eliminate(available);
    }
}

void Region::update() {
    Cell* candidate = nullptr;

    for (int n = 1; n <= 9; n++) {
        for (auto member : members) {
            if (!member->could_be(n)) {
                continue;
            }

            if (candidate == nullptr) {
                candidate = member;
            } else {
                candidate = nullptr;
                break;
            }
        }

        if (candidate == nullptr) {
            continue;
        }

        candidate->eliminate(Options(n));
        candidate = nullptr;
    }
}

}
