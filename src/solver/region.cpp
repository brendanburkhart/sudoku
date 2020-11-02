#include "region.hpp"

#include <vector>

namespace solver {

Region::Region(std::array<Options*, 9> members) : members(members) {}

Options Region::available_in_segment(int segment) const {
    Options segment_options(0);

    size_t start = size_t{ 3 } * segment;

    for (size_t i = start; i < 3 + start; i++) {
        if (!members[i]->is_solved()) {
            segment_options.add(*members[i]);
        }
    }

    return segment_options;
}

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

    Options together;

    for (int n = 1; n <= 9; n++) {
        for (auto member : members) {
            if (!member->overlaps(n)) {
                together.remove(*member);
                noncandidates.push_back(member);
            } else {
                together.restrict_to(*member);
                candidates.push_back(member);
            }
        }

        if (candidates.size() == together.count()) {
            for (auto& candidate : candidates) {
                candidate->restrict_to(together);
            }

            for (auto& noncandidate : noncandidates) {
                noncandidate->remove(together);
            }
        }

        candidates.clear();
        noncandidates.clear();
        together = Options();
    }
}

void Region::restrict_to_segment(int segment, const Options& options) {
    size_t start = size_t{ 3 } *segment;

    for (size_t i = 0; i < 9; i++) {
        if (i < start || i >= start + 3) {
            members[i]->remove(options);
        }
    }
}

void Region::exclude_from_segment(int segment, const Options& options) {
    size_t start = size_t{ 3 } *segment;

    for (size_t i = start; i < start + 3; i++) {
        members[i]->remove(options);
    }
}

}
