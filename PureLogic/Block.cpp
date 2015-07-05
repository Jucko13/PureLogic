#include "Block.h"
using namespace System::Drawing;

Block::~Block() {
	for (Pin *i : inputs) {
		delete i;
	}
	delete output;
}


Block::Block() {
	
}

void Block::setPos(int X, int Y) {
	pos.X = X;
	pos.Y = Y;
}

Pin * Block::getSelectedPin(Point p) {
	Point pinpos;

	for (Pin *i : inputs) {
		pinpos = i->getPos();
		if (pinpos.X <= p.X && pinpos.X + 10 >= p.X) {
			if (p.Y <= pinpos.Y + 2 && p.Y >= pinpos.Y - 2) {
				return i;
			}
		}
	}
	if (output) {
		pinpos = output->getPos();
		if (pinpos.X <= p.X && pinpos.X + 10 >= p.X) {
			if (p.Y <= pinpos.Y + 2 && p.Y >= pinpos.Y - 2) {
				return output;
			}
		}
	}

	return 0;
}

bool Block::pointInside(Point p) {
	return pos.Contains(p);
}

void Block::pinAdd() {
	
}

void Block::pinRemove() {
	
}

Rectangle Block::getPos() {
	return pos;
}

//void Block::setColors(unsigned long  a, unsigned long  i, unsigned long  n, unsigned long  b) {
//	colorActive = a;
//	colorInactive = i;
//	colorNormal = n;
//	colorBack = b;
//}



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