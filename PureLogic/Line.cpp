#include "Line.h"

using namespace System::Drawing;

Line::Line() {
	mouseOver = false;
	positive = false;
}

Line::Line(Pin*i, Pin*o) : Input(i), Output(o) {

}


Line::~Line() {
	if(Input != 0){
		Input->deatachLine(this);
		Input = 0;
	}

	if (Output != 0) {
		Output->deatachLine(this);
		Output = 0;
	}
}

int min(int n1, int n2){
	return (n1 < n2 ? n1 : n2);
}

int max(int n1, int n2) {
	return (n1 > n2 ? n1 : n2);
}

bool Line::isPointOnLine(Point p) {
	int x1 = Input->getPos().X;
	int x2 = Output->getPos().X+10;
	int y1 = Input->getPos().Y;
	int y2 = Output->getPos().Y;

	int tmpx;
	int tmpy;

	if (x1 > x2) {
		tmpx = x1;
		x1 = x2;
		x2 = tmpx;

		tmpy = y1;
		y1 = y2;
		y2 = tmpy;
	}

	if (p.X + 2 < x1 || p.X - 2 > x2 || p.Y + 2 < min(y1,y2) || p.Y - 2 > max(y1,y2)) return false;

	double deltaX = x2 - x1;
	double deltaY = y2 - y1;
	if (deltaX == 0 || deltaY == 0) return true;

	double slope = deltaY / deltaX;
	double offset = y1 - x1 * slope;
	double calculatedY = p.X * slope + offset;

	//PS::TooltipMessage = "c:" + c + " b:" + b + " a:" + a;
	//PS::TooltipVisible = true;

	return p.Y >= (calculatedY - 2) && p.Y <= (calculatedY + 2);

	
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

	if(selected){
		g->FillRectangle(ColorStyle::brushSelected, pos1.X - 3, pos1.Y - 3, 6, 6);
		g->DrawRectangle(ColorStyle::penNormal, pos1.X - 3, pos1.Y - 3, 6, 6);

		g->FillRectangle(ColorStyle::brushSelected, pos2.X - 3 + 10, pos2.Y - 3, 6, 6);
		g->DrawRectangle(ColorStyle::penNormal, pos2.X - 3 + 10, pos2.Y - 3, 6, 6);
	}
}

Rectangle Line::getPos() {
	Rectangle r;

	Point pos1 = Input->getPos();
	Point pos2 = Output->getPos();

	r.X = min(pos1.X,pos2.X+10);
	r.Y = min(pos1.Y, pos2.Y);

	r.Width = abs(pos1.X - (pos2.X + 10));
	r.Height = abs(pos1.Y - pos2.Y);
	return r;
}

void Line::setInput(Pin *b) {
	Input = b;
}

void Line::setOutput(Pin *b) {
	Output = b;
}

Pin * Line::getInput() {
	return Input;
}

Pin * Line::getOutput() {
	return Output;
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