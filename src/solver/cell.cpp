#include "cell.hpp"

namespace solver {

Cell::Cell(int initial) : value(initial) {
	if (initial != 0) {
		options = Options(value);
	}
}

std::ostream& operator<<(std::ostream& output, const Cell& cell) {
	if (cell.value == 0) {
		output << " ";
	} else {
		output << cell.value;
	}

	return output;
}

int Cell::get_value() const {
	return value;
}

void Cell::eliminate(Options available) {
	options &= available;
}

void Cell::update() {
	if (value == 0 && options.solved()) {
		value = options.value();
	}
}

bool Cell::could_be(int value) const {
	return options.contains(value);
}

}
