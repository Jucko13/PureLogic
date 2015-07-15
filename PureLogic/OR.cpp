#include "OR.h"


OR::OR() : AND("OR Gate", L">=1", PS::blockTypes::OR) {

}


OR::~OR() {

}

bool OR::execute(){
	int connectedCount = 0;

	for (Pin *i : inputs) {
		if (i->isConnected()) {
			connectedCount++;
			if (i->getState() == true) {
				if (active != true) {
					active = true;
					output->setState(true);
				}
				return true;
			}
		}
	}

	if (active != false && connectedCount > 0) {
		active = false;
		output->setState(false);
	}
	return false;
}