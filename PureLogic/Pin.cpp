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


void Pin::deatachLine(Line *p){
	for (unsigned int i = 0; i < lines.size(); i++) {
		if (lines[i] == p) {
			lines[i] = NULL;
			break;
		}
	}

	lines.erase(std::remove(lines.begin(), lines.end(), static_cast<Line*>(NULL)), lines.end());
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
	blockPos.X += PS::scroll.X;
	blockPos.Y += PS::scroll.Y;

	//g->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias; //turn on antialiasing
	//blockPos.X *= PS::zoom;
	//blockPos.Y *= PS::zoom;
	//blockPos.Width *= PS::zoom;
	//blockPos.Height *= PS::zoom;

	if (output) {
		pos.X = offsetPos.X * PS::zoom + blockPos.X + blockPos.Width;
		pos.Y = offsetPos.Y * PS::zoom + blockPos.Y;
		if (negate) g->FillRectangle(n, pos.X, pos.Y - int(1 * PS::zoom) - 1, int(3 * PS::zoom) + 2, int(3 * PS::zoom) + 2);
	} else {
		pos.X = offsetPos.X * PS::zoom + blockPos.X - 10 * PS::zoom;
		pos.Y = offsetPos.Y * PS::zoom + blockPos.Y;
		if (negate) g->FillRectangle(n, offsetPos.X * PS::zoom + blockPos.X - 5 * PS::zoom, pos.Y - int(1 * PS::zoom) - 1, int(3 * PS::zoom) + 2, int(3 * PS::zoom) + 2);
	}

	

	pos.Width = 10 * PS::zoom;
	pos.Height = 0;

	g->DrawLine(p, pos.X, pos.Y, pos.X + pos.Width, pos.Y);
	


	if (border) {
		//g->DrawRectangle(ColorStyle::penInactive, Rectangle(pos.X - 4.0f * PS::zoom, pos.Y - 3.0f * PS::zoom, 18.0f * PS::zoom, 8.0f * PS::zoom - 1));
		

		g->DrawRectangle(ColorStyle::penInactive, Rectangle(pos.X - 1 - int(2 * PS::zoom), pos.Y - 1 - int(2 * PS::zoom), 2 + (10 + 4) * PS::zoom, 2 + 4 * PS::zoom));
	}

}