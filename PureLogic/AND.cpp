#include "AND.h"
#include "Block.h"
#include "Pin.h"

using namespace System::Drawing;

AND::AND(): Block("AND Gate") {
	pos.X = 50;
	pos.Y = 50;

	pinAdd();
	output = new Pin(this,0,10,1);
	//output->setNegate(true);
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
		inputs.push_back(new Pin(this, 0, i * 10 + 10, 0));
}

void AND::mouseDown(Point p) {
	if (PS::simulating) {
		selected = true;
	}else{
		Point ^relative = gcnew Point(p.X - pos.X, p.Y - pos.Y);

		if (relative->Y > pos.Height - 10 && relative->Y < pos.Height) {
			if (relative->X > 2 && relative->X < 8) {
				pinAdd();
			} else if (relative->X > 8 && relative->X < 14) {
				pinRemove();
			}
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
	}
}


bool AND::execute() {
	int connectedCount = 0;

	for (Pin *i : inputs) {
		if (i->isConnected()) {
			connectedCount++;
			if (i->getState() == false) {
				if (active != false){
					active = false;
					output->setState(false);
				}
				return false;
			}
		}
	}

	if (active != true && connectedCount > 0) {
		active = true;
		output->setState(true);
	}
	return true;
}

void AND::draw(Graphics ^g) {
	Brush ^b;
	Pen ^p;

	pos.Height = (inputs.size()-1) * 10 + 20;
	if (pos.Height < 20) pos.Height = 20;
	pos.Width = 20;

	Rectangle rect = getPos();

	output->draw(g);

	for (Pin *i : inputs) {
		i->draw(g);
	}

	//draw background of block
	g->FillRectangle(ColorStyle::brushBack, rect.X, rect.Y, rect.Width, rect.Height); //35

	//draw border of block
	if (PS::simulating) {
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
	g->DrawRectangle(p, rect.X, rect.Y, rect.Width, rect.Height); //35


	if (!PS::simulating){
		int inputsize = inputs.size() - 1;

		if (inputsize >= 0 && inputsize < 9) {
			if (!inputs[inputsize]->isConnected() && inputsize > 0) {
				g->DrawString("+-", ColorStyle::fontFamily, b, Rectangle(rect.X, rect.Y, rect.Width, rect.Height), ColorStyle::fontFormatFar);
			} else {
				g->DrawString("+", ColorStyle::fontFamily, b, Rectangle(rect.X, rect.Y, rect.Width, rect.Height), ColorStyle::fontFormatFar);
			}
		} else {
			if (!inputs[inputsize]->isConnected()){
				g->DrawString(" -", ColorStyle::fontFamily, b, Rectangle(rect.X, rect.Y, rect.Width, rect.Height), ColorStyle::fontFormatFar);
			}
		}
	}

	g->DrawString("&", ColorStyle::fontFamily, b, Rectangle(rect.X, rect.Y, rect.Width, 12), ColorStyle::fontFormatCenter);


	Block::draw(g);
}