#include "Block.h"
using namespace System::Drawing;

Block::~Block() {
	for (Pin *i : inputs) {
		delete i;
	}
	delete output;
}


Block::Block(std::string n) : name(n) {
	selected = false;
	active = false;

}

void Block::setPos(int X, int Y) {
	pos.X = X;
	pos.Y = Y;
	posOffset.X = 0;
	posOffset.Y = 0;
}

std::string Block::getName() {
	return name;
}

void Block::draw(Graphics ^g) {
	
	Rectangle rect = getPos();
	rect.X += PS::scroll.X;
	rect.Y += PS::scroll.Y;


	if (PS::keys->Alt) {
		g->DrawString(gcnew System::String(name.c_str()), ColorStyle::fontFamily, ColorStyle::brushNormal, rect.X + rect.Width / 2, rect.Y - ColorStyle::fontFamily->Size, ColorStyle::fontFormatCenter);
	}

	if (!selected) return;
	if (PS::dragMode == PS::dragType::moving) return;

	

	g->FillRectangle(ColorStyle::brushSelected, rect.X - 3 , rect.Y - 3 , 6, 6);
	g->DrawRectangle(ColorStyle::penNormal, rect.X - 3 , rect.Y - 3, 6, 6);

	g->FillRectangle(ColorStyle::brushSelected, rect.X + rect.Width - 3 , rect.Y - 3, 6, 6);
	g->DrawRectangle(ColorStyle::penNormal, rect.X + rect.Width - 3 , rect.Y - 3, 6, 6);

	g->FillRectangle(ColorStyle::brushSelected, rect.X - 3 , rect.Y + rect.Height - 3 , 6, 6);
	g->DrawRectangle(ColorStyle::penNormal, rect.X - 3, rect.Y + rect.Height - 3 , 6, 6);

	g->FillRectangle(ColorStyle::brushSelected, rect.X + rect.Width - 3 , rect.Y + rect.Height - 3, 6, 6);
	g->DrawRectangle(ColorStyle::penNormal, rect.X + rect.Width - 3, rect.Y + rect.Height - 3, 6, 6);

}

void Block::setPosOffset(Point p) {
	posOffset = p;
}

void Block::setPosCalculateOffset() {
	pos.X += posOffset.X / PS::zoom;
	pos.Y += posOffset.Y / PS::zoom;

	//pos.X -= pos.X % 10;
	//pos.Y -= pos.Y % 10;

	posOffset.X = 0;
	posOffset.Y = 0;
}


Pin * Block::getSelectedPin(Point p) {
	Point pinpos;

	for (Pin *i : inputs) {
		pinpos = i->getPos();
		if (pinpos.X - 4 * PS::zoom <= p.X && pinpos.X + 14 * PS::zoom >= p.X) {
			if (p.Y <= pinpos.Y + 4 * PS::zoom && p.Y >= pinpos.Y - 4 * PS::zoom) {
				return i;
			}
		}
	}
	if (output) {
		pinpos = output->getPos();
		if (pinpos.X - 4 * PS::zoom <= p.X && pinpos.X + 14 * PS::zoom >= p.X) {
			if (p.Y <= pinpos.Y + 4 * PS::zoom && p.Y >= pinpos.Y - 4 * PS::zoom) {
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
	return Rectangle(pos.X * PS::zoom + posOffset.X, pos.Y* PS::zoom + posOffset.Y, pos.Width * PS::zoom, pos.Height * PS::zoom);
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
		} else {
			if (inputs.size() > (unsigned)pinNum) {
				inputs[pinNum]->attachLine(p);
			}
		}
	}
}