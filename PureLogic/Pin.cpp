#include "Pin.h"
#include "Block.h"
#include "Line.h"


using namespace System::Drawing;

Pin::Pin(Block *b, int X, int Y, bool o) {
	offsetPos.X = X;
	offsetPos.Y = Y;
	connectedBlock = b;
	output = o;
	positive = false;
	negate = false;
	border = false;
}

Pin::~Pin() {
	
}

void Pin::setBorder(bool newState) {
	border = newState;
}

bool Pin::isConnected() {
	return lines.size() > 0;
}

bool Pin::isOutput() {
	return output;
}

void Pin::setState(bool newState) {
	positive = newState;
	if (output) {
		if (isConnected()) {
			for (Line *i : lines) {
				i->setState(getState());
			}
		}
	} else {
		connectedBlock->execute();
	}
}

void Pin::setNegate(bool newState) {
	if (negate != newState) {
		negate = newState;
		if (output) {
			for (Line *i : lines) {
				i->setState(getState());
			}
		} else {
			connectedBlock->execute();
		}
	}
}

bool Pin::isNegated() {
	return negate;
}

void Pin::setPos(int X, int Y) {
	offsetPos.X = X;
	offsetPos.Y = Y;
}

Point Pin::getPos() {
	return pos.Location;
}

bool Pin::getState() {
	return positive ^ negate;
}

void Pin::attachLine(Line *p) {
	if (p == 0) return;
	lines.push_back(p);
	if (output) {
		p->setOutput(this);
		p->setState(getState());
	} else {
		p->setInput(this);
		setState(p->getState());
	}
}

Block* Pin::getBlock() {
	return connectedBlock;
}

void Pin::draw(Graphics ^g) {
	Pen ^p;
	Brush ^n;

	if (PS::simulating && (isConnected() || output)) {
		if ((!output && positive) || (output && positive ^ negate)) {
			p = gcnew Pen(ColorStyle::colorActive);
			n = gcnew SolidBrush(ColorStyle::colorInactive);
		} else {
			p = gcnew Pen(ColorStyle::colorInactive);
			n = gcnew SolidBrush(ColorStyle::colorActive);
		}
	}else{
		p = gcnew Pen(ColorStyle::colorNormal);
		n = gcnew SolidBrush(ColorStyle::colorNormal);
	}

	Rectangle blockPos = (*connectedBlock).getPos();
	//g->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias; //turn on antialiasing

	if (output) {
		pos.X = offsetPos.X + blockPos.X + blockPos.Width;
		pos.Y = offsetPos.Y + blockPos.Y;
		//pos.Y = offsetPos.Y + blockPos.Y + blockPos.Height / 2;

		pos.Width = 10;
		pos.Height = 0;

		g->DrawLine(p, pos.X, pos.Y, pos.X + pos.Width, pos.Y);
		if (negate) g->FillRectangle(n, pos.X, pos.Y - 2, 5, 5);
	} else {
		
		pos.X = offsetPos.X + blockPos.X - 10;
		pos.Y = offsetPos.Y + blockPos.Y;
		pos.Width = 10;
		pos.Height = 0;

		g->DrawLine(p, pos.X, pos.Y, pos.X + pos.Width, pos.Y);
		if (negate) g->FillRectangle(n, pos.X - 4 + pos.Width, pos.Y - 2, 4, 5);
	}

	if (border) {
		g->DrawRectangle(ColorStyle::penInactive,pos.X-4,pos.Y-4,18,8);
	}

}