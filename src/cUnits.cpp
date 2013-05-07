#include "cUnits.h"

cUnits::cUnits() {
	pc = 30856802500000000;
	ly = 9460730472580800;
}

long cUnits::getLy() {
	return ly;
}

long cUnits::getPc() {
	return pc;
}
