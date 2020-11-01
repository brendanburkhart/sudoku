#include "options.hpp"

namespace solver {

Options::Options(int value) {
    options = (value == all || value == 0) ? value : 1 << (value - 1);
}

bool Options::is_solved() const {
    // Only contains a single value if it is a power of two
    return (options & (options - 1)) == 0;
}

bool Options::overlaps(const Options& values) const {
    return (options & values.options) != 0;
}

int convert_to_value(int options) {
    int n = 1;

    while (options > 1) {
        options = options >> 1;
        n++;
    }

    return n;
}

int Options::value() const {
    if (is_solved()) {
        return convert_to_value(options);
    }

    return 0;
}

int Options::checksum() const {
    return options;
}

void Options::remove(const Options& values) {
    options &= ~values.options;
}

void Options::restrict_to(const Options& values) {
    options &= values.options;
}

std::ostream& operator<<(std::ostream& output, const Options& values) {
    return output << values.value();;
}

}
