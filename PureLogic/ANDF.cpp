#include "ANDF.h"


ANDF::ANDF() : AND("AND Rising Gate", L"  &↓", PS::blockTypes::ANDF) {
}


ANDF::~ANDF() {
}

bool ANDF::execute() {
	int connectedCount = 0;

	for (Pin *i : inputs) {
		if (i->isConnected()) {
			connectedCount++;
			if (i->getState() == false) {
				if (active != false) {
					active = true;
					output->setState(true);
					active = false;
					output->setState(false);
				}
				return false;
			}
		}
	}

	if (active != true && connectedCount > 0) {
		active = true;
	//	output->setState(true);
	}
	return false;
}