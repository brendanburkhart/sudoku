#pragma once

#include <iostream>

namespace solver {

class Options {
public:
    Options(int value = all);

    bool is_solved() const;
    bool overlaps(const Options& values) const;

    int value() const;
    int checksum() const;
    int count() const;

    void remove(const Options& values);
    void add(const Options& values);
    void restrict_to(const Options& values);

    friend std::ostream& operator<<(std::ostream& output, const Options& values);

    static constexpr int all = 1 + 2 + 4 + 8 + 16 + 32 + 64 + 128 + 256;
private:

    int options;
};

}
