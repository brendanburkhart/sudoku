#include "region.hpp"

#include <vector>

namespace solver {

Region::Region(std::array<Options*, 9> members) : members(members) {}

void Region::eliminate() {
    for (auto member : members) {
        available.remove(member->value());
    }

    for (auto member : members) {
        if (!member->is_solved()) {
            member->restrict_to(available);
        }
    }
}

void Region::exclude() {
    std::vector<Options*> candidates;
    std::vector<Options*> noncandidates;
    candidates.reserve(9);
    noncandidates.reserve(9);

    Options available;

    for (int n = 1; n <= 9; n++) {
        for (auto member : members) {
            if (!member->overlaps(n)) {
                available.remove(*member);
                noncandidates.push_back(member);
            } else {
                available.restrict_to(*member);
                candidates.push_back(member);
            }
        }

        if (candidates.size() == available.count()) {
            for (auto& candidate : candidates) {
                candidate->restrict_to(available);
            }

            for (auto& noncandidate : noncandidates) {
                noncandidate->remove(available);
            }
        }

        candidates.clear();
        noncandidates.clear();
        available = Options();
    }
}

}
