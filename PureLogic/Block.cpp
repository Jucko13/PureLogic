#include "Block.h"
using namespace System::Drawing;

Block::~Block() {
	for (Pin *i : inputs) {
		delete i;
	}
}


Block::Block() {
	
}

void Block::setPos(int X, int Y) {
	pos.X = X;
	pos.Y = Y;

}

Rectangle Block::getPos() {
	return pos;
}

void Block::setColors(unsigned long  a, unsigned long  i, unsigned long  n, unsigned long  b) {
	colorActive = a;
	colorInactive = i;
	colorNormal = n;
	colorBack = b;
}



void Block::attachLine(Line *p, int pinNum, int isOutput) {
	if (p == 0) return;
	if (pinNum < 0) {
		if (isOutput) {
			output->attachLine(p);
		} else {
			for (Pin *i : inputs) {
				if (!i->isConnected()) {
					i->attachLine(p);
					return;
				}
			}
		}
	} else {
		if (isOutput) {
			output->attachLine(p);
		}else{
			if (inputs.size() > pinNum) {
				inputs[pinNum]->attachLine(p);
			}
		}
	}
}