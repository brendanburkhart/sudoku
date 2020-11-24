#pragma once

#include <iostream>

namespace solver {

class Options {
public:
    constexpr Options::Options() : options((1 << 9) - 1) {}

    constexpr Options::Options(const Options& options) : options(options.options) {}

    constexpr static Options Options::from_value(int value) {
        return Options(1 << (value - 1));
    }

    constexpr static Options Options::all() {
        return Options();
    }

    constexpr static Options Options::none() {
        return Options(0);
    }

    bool is_solved() const;
    bool overlaps(const Options& values) const;

    int value() const;

    constexpr int checksum() const {
        return options;
    }

    int count() const;

    void remove(const Options& values);
    void add(const Options& values);
    void restrict_to(const Options& values);

    friend std::ostream& operator<<(std::ostream& output, const Options& values);

private:
    constexpr Options::Options(int value) : options(value) {}

    int options;
};

}
