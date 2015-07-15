#include "ANDR.h"


ANDR::ANDR() : AND("AND Rising Gate", L"  &↑", PS::blockTypes::ANDR) {
}


ANDR::~ANDR() {
}


bool ANDR::execute() {
	int connectedCount = 0;

	for (Pin *i : inputs) {
		if (i->isConnected()) {
			connectedCount++;
			if (i->getState() == false) {
				if (active != false) {
					active = false;
					output->setState(false);
				}
				return false;
			}
		}
	}

	if (active != true && connectedCount > 0) {
		active = true;
		output->setState(true);
		active = false;
		output->setState(false);
	}
	return false;
}