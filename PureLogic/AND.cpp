#include "AND.h"
#include "Block.h"
#include "Pin.h"

using namespace System::Drawing;

AND::AND(): Block("AND Gate") {
	pos.X = 50;
	pos.Y = 50;

	pinAdd();
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
	if(PS::simulating) return;
	if (PS::keys->Control || PS::keys->Shift) return;
	Rectangle rect = getPos();
	Point ^relative = gcnew Point(p.X - rect.X, p.Y - rect.Y);

	//PS::TooltipMessage = "X: " + relative->X + " Y:" + relative->Y;
	//PS::TooltipVisible = true;
	//return;
	if (posPlus.Contains(p) ) {
		pinAdd();
	} else if (posMin.Contains(p)){
		pinRemove();
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

	pos.Height = (inputs.size() - 1) * 10 + 20;
	if (pos.Height < 20) pos.Height = 20;
	pos.Width = 20;

	Rectangle rect = getPos();
	rect.X += PS::scroll.X;
	rect.Y += PS::scroll.Y;


	//rect.X *= PS::zoom;
	//rect.Y *= PS::zoom;
	//rect.Width *= PS::zoom;
	//rect.Height *= PS::zoom;

	


	output->draw(g);

	for (Pin *i : inputs) {
		i->draw(g);
	}

	//draw background of block
	g->FillRectangle(ColorStyle::brushBack, rect); //35

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
	g->DrawRectangle(p, rect); //35

	posPlus.Width = 10 * PS::zoom - 3;
	posPlus.Height = posPlus.Width;
	posPlus.X = rect.X + 2;
	posPlus.Y = rect.Y + rect.Height - 10 * PS::zoom - posPlus.Width / 2;
	
	posMin.Height = posPlus.Height;
	posMin.Width = posPlus.Height;
	posMin.X = rect.X + rect.Width - 2 - posPlus.Width;
	posMin.Y = posPlus.Y;

	if (!PS::simulating){
		int inputsize = inputs.size();

		if (inputsize >= pinsMin && inputsize < pinsMax) {
			if (!inputs[inputsize-1]->isConnected() && inputsize > pinsMin) {
				g->DrawLine(ColorStyle::penNormal, posPlus.X, posPlus.Y + posPlus.Height / 2, posPlus.X + posPlus.Width - 1, posPlus.Y + posPlus.Height / 2);
				g->DrawLine(ColorStyle::penNormal, posPlus.X + posPlus.Width / 2, posPlus.Y, posPlus.X + posPlus.Width / 2, posPlus.Y + posPlus.Height - 1);

				g->DrawLine(ColorStyle::penNormal, posMin.X, posMin.Y + posMin.Height / 2, posMin.X + posMin.Width - 1, posMin.Y + posMin.Height / 2);
			} else {
				g->DrawLine(ColorStyle::penNormal, posPlus.X, posPlus.Y + posPlus.Height / 2, posPlus.X + posPlus.Width - 1, posPlus.Y + posPlus.Height / 2);
				g->DrawLine(ColorStyle::penNormal, posPlus.X + posPlus.Width / 2, posPlus.Y, posPlus.X + posPlus.Width / 2, posPlus.Y + posPlus.Height - 1);
			}
		} else {
			if (!inputs[inputsize-1]->isConnected()){
				g->DrawLine(ColorStyle::penNormal, posMin.X, posMin.Y + posMin.Height / 2, posMin.X + posMin.Width - 1, posMin.Y + posMin.Height / 2);
			}
		}
	}

	g->DrawString("&", ColorStyle::fontFamily, b, Rectangle(rect.X, rect.Y, rect.Width, ColorStyle::fontFamily->Size), ColorStyle::fontFormatCenter);

	Block::draw(g);
}