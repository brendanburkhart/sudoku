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

void Region::exclude() {
    bool single = true;
    Cell* candidate = nullptr;

    for (int n = 1; n <= 9; n++) {
        for (auto member : members) {
            if (!member->could_be(n)) {
                continue;
            }

            if (candidate == nullptr) {
                candidate = member;
            } else {
                single = false;
                break;
            }
        }

        if (single && candidate != nullptr) {
            candidate->eliminate(Options(n));
        }

        single = true;
        candidate = nullptr;
    }
}

}
