#include "Block.h"
using namespace System::Drawing;

Block::~Block() {
	for (Pin *i : inputs) {
		delete i;
	}
	delete output;
}


Block::Block(std::string n): name(n) {
	selected = false;
	active = false;
}

void Block::setPos(int X, int Y) {
	pos.X = X;
	pos.Y = Y;
}

std::string Block::getName() {
	return name;
}

void Block::draw(Graphics ^g){
	if(!selected) return;

	g->FillRectangle(ColorStyle::brushSelected, pos.X - 3, pos.Y-3,6,6);
	g->DrawRectangle(ColorStyle::penNormal, pos.X - 3, pos.Y - 3, 6, 6);

	g->FillRectangle(ColorStyle::brushSelected, pos.X + pos.Width - 3, pos.Y - 3, 6, 6);
	g->DrawRectangle(ColorStyle::penNormal, pos.X + pos.Width - 3, pos.Y - 3, 6, 6);

	g->FillRectangle(ColorStyle::brushSelected, pos.X - 3, pos.Y + pos.Height - 3, 6, 6);
	g->DrawRectangle(ColorStyle::penNormal, pos.X - 3, pos.Y + pos.Height - 3, 6, 6);

	g->FillRectangle(ColorStyle::brushSelected, pos.X + pos.Width - 3, pos.Y + pos.Height - 3, 6, 6);
	g->DrawRectangle(ColorStyle::penNormal, pos.X + pos.Width - 3, pos.Y + pos.Height - 3, 6, 6);



}

Pin * Block::getSelectedPin(Point p) {
	Point pinpos;

	for (Pin *i : inputs) {
		pinpos = i->getPos();
		if (pinpos.X-4 <= p.X && pinpos.X + 14 >= p.X) {
			if (p.Y <= pinpos.Y + 4 && p.Y >= pinpos.Y - 4) {
				return i;
			}
		}
	}
	if (output) {
		pinpos = output->getPos();
		if (pinpos.X-4 <= p.X && pinpos.X + 14 >= p.X) {
			if (p.Y <= pinpos.Y + 4 && p.Y >= pinpos.Y - 4) {
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