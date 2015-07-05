#include "Line.h"

using namespace System::Drawing;

Line::Line() {

}

Line::Line(Pin*i, Pin*o) : Input(i), Output(o) {

}


Line::~Line() {

}


void Line::draw(Graphics ^g) {
	Pen ^p;
	//Brush ^n;

	if (Input == 0 || Output == 0) return;

	Point pos1 = Input->getPos();
	Point pos2 = Output->getPos();

	if (positive) {
		p = gcnew Pen(ColorStyle::colorActive);
		//n = gcnew SolidBrush(ColorTranslator::FromOle(connectedBlock->colorInactive));
	} else {
		p = gcnew Pen(ColorStyle::colorInactive);
		//n = gcnew SolidBrush(ColorTranslator::FromOle(connectedBlock->colorActive));
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
	if (Output == 0) return;
	Input->setState(newState);
}

bool Line::getState() {
	return positive;

}