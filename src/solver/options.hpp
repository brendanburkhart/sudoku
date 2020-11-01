#pragma once

namespace solver {

class Options {
public:
    Options(int value = 0);

    bool solved() const;
    bool contains(int value) const;

    int value() const;
    int checksum() const;

    void operator-=(int value);
    void operator&=(const Options& available);

    static constexpr int all = 1 + 2 + 4 + 8 + 16 + 32 + 64 + 128 + 256;

private:
    int options;
};

}
