#include "options.hpp"

namespace solver {

Options::Options(int value) {
    options = (value == 0) ? all : 1 << (value - 1);
}

bool Options::solved() const {
    // Only contains a single value if it is a power of two
    return (options & (options - 1)) == 0;
}

bool Options::contains(int value) const {
    // Bit representing 2^(n-1) is 1 iff option contains n
    int mask = 1 << (value - 1);
    return (options & mask) != 0;
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
    if (solved()) {
        return convert_to_value(options);
    }

    return 0;
}

int Options::checksum() const {
    return options;
}

void Options::operator-=(int value) {
    options &= ~(1 << (value - 1));
}

void Options::operator&=(const Options& available) {
    options &= available.options;
}

}
