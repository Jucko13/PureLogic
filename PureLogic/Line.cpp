#include "Line.h"

using namespace System::Drawing;

Line::Line() {
	mouseOver = false;
	positive = false;
}

Line::Line(Pin*i, Pin*o) : Input(i), Output(o) {

}


Line::~Line() {

}

bool Line::isPointOnLine(Point p) {
	int x1 = Input->getPos().X;
	int x2 = Output->getPos().X+10;
	int tmpx;
	if (x1 > x2) {
		tmpx = x1;
		x1 = x2;
		x2 = tmpx;
	}

	int y1 = Input->getPos().Y;
	int y2 = Output->getPos().Y;
	int tmpy;
	if (y1 > y2) {
		tmpy = y1;
		y1 = y2;
		y2 = tmpy;
	}

	if (p.X < x1-1 || p.X > x2+1 || p.Y < y1-1 || p.Y > y2+1) return false;
	
	
	float a = 0.0;

	float difX = x2 - x1;
	float difY = y2 - y1;

	if (difX != 0){
		a = difY / difX;
	}

	float b = y1 - a * x1;
	float c = p.Y - a * p.X;
	
	return fabs(c - b) < 1;

	
}


void Line::draw(Graphics ^g) {
	Pen ^p;
	//Brush ^n;

	if (Input == 0 || Output == 0) return;

	Point pos1 = Input->getPos();
	Point pos2 = Output->getPos();

	if (PS::simulating) {
		if (positive) {
			p = ColorStyle::penActive;
			//n = gcnew SolidBrush(ColorTranslator::FromOle(connectedBlock->colorInactive));
		} else {
			p = ColorStyle::penInactive;
			//n = gcnew SolidBrush(ColorTranslator::FromOle(connectedBlock->colorActive));
		}
	} else {
		if (mouseOver) {
			p = ColorStyle::penMouseOver;
		} else {
			p = ColorStyle::penNormal;
		}
		
	}

	g->DrawLine(p, pos1.X, pos1.Y, pos2.X + 10, pos2.Y);
}

void Line::setInput(Pin *b) {
	Input = b;
}

void Line::setOutput(Pin *b) {
	Output = b;
}

void Line::setState(bool newState) {
	positive = newState;
	if (Input == 0) return;
	Input->setState(newState);
}

bool Line::getState() {
	return positive;

}

void Line::setMouseOver(bool newState) {
	mouseOver = newState;
}