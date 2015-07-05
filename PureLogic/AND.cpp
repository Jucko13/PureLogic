#include "AND.h"
#include "Block.h"
#include "Pin.h"

using namespace System::Drawing;

AND::AND() {
	pos.X = 50;
	pos.Y = 50;
	simulating = false;
	active = false;

	pinAdd();
	output = new Pin(this,0,6,1);
	output->setNegate(true);
	simulating = true;
}

AND::~AND() {
	//delete output;

	//for (Pin *i : inputs) {
	//	delete i;
	//}
}

void AND::pinAdd() {
	int i = inputs.size();
	if (i < pinsMax)
		inputs.push_back(new Pin(this, 0, i * 9 + 6, 0));
}

void AND::mouseDown(Point p) {
	Point ^relative = gcnew Point(p.X - pos.X, p.Y - pos.Y);

	if (relative->Y > pos.Height - 10 && relative->Y < pos.Height) {
		if (relative->X > 2 && relative->X < 8) {
			pinAdd();
		} else if (relative->X > 8 && relative->X < 14) {
			pinRemove();
		}
	}
}

void AND::mouseUp(Point p) {

}

void AND::mouseMove(Point p) {

}


void AND::pinRemove() {
	int i = inputs.size();
	if (i - 1 >= pinsMin) {
		Pin * p = inputs[i - 1];
		if (p->isConnected()) return;
		inputs.pop_back();
		delete p;
		//
	}
}


bool AND::execute() {
	for (Pin *i : inputs) {
		if (i->getState() == false) {
			if (active != false){
				active = false;
				output->setState(false);
			}
			return false;
		}
	}
	if (active != true) {
		output->setState(true);
		active = true;
	}
	return true;
}

void AND::draw(Graphics ^g) {
	Brush ^b;
	Pen ^p;

	pos.Height = (inputs.size()-1) * 9 + 12;
	if (pos.Height < 21) pos.Height = 21;
	pos.Width = 25;

	output->draw(g);

	for (Pin *i : inputs) {
		i->draw(g);
	}

	//draw background of block
	g->FillRectangle(ColorStyle::brushBack, pos.X, pos.Y, pos.Width, pos.Height); //35

	//draw border of block
	if (simulating) {
		if (active) {
			p = ColorStyle::penActive;
			b = ColorStyle::brushActive;
		} else {
			p = ColorStyle::penInactive;
			b = ColorStyle::brushInactive;
		}
	}else {
		p = ColorStyle::penNormal;
		b = ColorStyle::brushNormal;
	}
	g->DrawRectangle(p, pos.X, pos.Y, pos.Width, pos.Height); //35


	
	int inputsize = inputs.size() - 1;

	if (inputsize >= 0 && inputsize < 9) {
		if (!inputs[inputsize]->isConnected()) {
			g->DrawString("+-", ColorStyle::fontFamily, b, RectangleF(pos.X, pos.Y, pos.Width, pos.Height), ColorStyle::fontFormatFar);
		} else {
			g->DrawString("+", ColorStyle::fontFamily, b, RectangleF(pos.X, pos.Y, pos.Width, pos.Height), ColorStyle::fontFormatFar);
		}
	} else {
		g->DrawString(" -", ColorStyle::fontFamily, b, RectangleF(pos.X, pos.Y, pos.Width, pos.Height), ColorStyle::fontFormatFar);
	}

	g->DrawString("&", ColorStyle::fontFamily, b, RectangleF(pos.X, pos.Y, pos.Width, 12), ColorStyle::fontFormatCenter);
	


}