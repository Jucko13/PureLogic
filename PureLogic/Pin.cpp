#include "Pin.h"
#include "Block.h"
#include "Line.h"


using namespace System::Drawing;

Pin::Pin(Block *b, int X, int Y, bool o) {
	offsetPos.X = X;
	offsetPos.Y = Y;
	connectedBlock = b;
	isOutput = o;
	positive = true;
	negate = true;
}

Pin::~Pin() {
	
}

bool Pin::isConnected() {
	return lines.size() > 0;
}

void Pin::setState(bool newState) {
	positive = newState ^ negate;
	if (isOutput) {
		if (isConnected()) {
			for (Line *i : lines) {
				i->setState(positive);
			}
		}
	} else {
		connectedBlock->execute();
	}
}

void Pin::setNegate(bool newState) {
	negate = newState;
}

void Pin::setPos(int X, int Y) {
	offsetPos.X = X;
	offsetPos.Y = Y;
}

Point Pin::getPos() {
	return Point(pos.X,pos.Y);
}

bool Pin::isPositive() {
	return positive ^ negate;
}

void Pin::attachLine(Line *p) {
	if (p == 0) return;
	lines.push_back(p);
	if (isOutput) {
		p->setOutput(this);
	} else {
		p->setInput(this);
	}
}

Block* Pin::getBlock() {
	return connectedBlock;
}

void Pin::draw(Graphics ^g) {
	Pen ^p;
	Brush ^n;

	if (connectedBlock->simulating && (isConnected() || isOutput)) {
		if (positive ^ negate) {
			p = gcnew Pen(ColorTranslator::FromOle(connectedBlock->colorActive));
			n = gcnew SolidBrush(ColorTranslator::FromOle(connectedBlock->colorInactive));
		} else {
			p = gcnew Pen(ColorTranslator::FromOle(connectedBlock->colorInactive));
			n = gcnew SolidBrush(ColorTranslator::FromOle(connectedBlock->colorActive));
		}
	}else{
		p = gcnew Pen(ColorTranslator::FromOle(connectedBlock->colorNormal));
		n = gcnew SolidBrush(ColorTranslator::FromOle(connectedBlock->colorNormal));
	}

	Rectangle blockPos = (*connectedBlock).getPos();
	//g->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias; //turn on antialiasing

	if (isOutput) {
		pos.X = offsetPos.X + blockPos.X + blockPos.Width + 10;
		pos.Y = offsetPos.Y + blockPos.Y + blockPos.Height / 2;
		pos.Width = 10;
		pos.Height = 0;

		g->DrawLine(p, pos.X, pos.Y, pos.X - pos.Width, pos.Y);
		if (negate) g->FillRectangle(n, pos.X - pos.Width, pos.Y - 2, 5, 5);
	} else {
		
		pos.X = offsetPos.X + blockPos.X - 10;
		pos.Y = offsetPos.Y + blockPos.Y;
		pos.Width = 10;
		pos.Height = 0;

		g->DrawLine(p, pos.X, pos.Y, pos.X + pos.Width, pos.Y);
		if (negate) g->FillRectangle(n, pos.X - 4 + pos.Width, pos.Y - 2, 4, 5);
	}


}