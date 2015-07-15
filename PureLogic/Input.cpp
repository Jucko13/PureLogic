#include "INPUT.h"
#include "Pin.h"

using namespace System::Windows::Forms;

using namespace System::Drawing;

INPUT::INPUT() : Block("INPUT", PS::blockTypes::INPUT) {
	output = new Pin(this,0,10,1);
}


INPUT::~INPUT() {

}


void INPUT::mouseDown(Point p) {
	if (PS::simulating) {
		active = true;
		execute();
	}
}

void INPUT::mouseUp(Point p) {
	if (PS::simulating){
		//MessageBox::Show("input!");
		active = false;
		execute();
	}
}

void INPUT::mouseMove(Point p) {
	//MessageBox::Show("input!");
}

bool INPUT::execute() {
	/*for (Pin *i : inputs) {
		if (i->getState() == false) {
			active = false;
			output->setState(false);
			return false;
		}
	}
	output->setState(true);
	active = true;
	return true;*/

	output->setState(active);

	return true;
}

void INPUT::draw(Graphics ^g) {
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

	//draw background of block
	g->FillRectangle(ColorStyle::brushBack, rect.X, rect.Y, rect.Width, rect.Height); //35

	if (PS::simulating) {
		if (active) {
			p = ColorStyle::penActive;
			b = ColorStyle::brushActive;
		} else {
			p = ColorStyle::penInactive;
			b = ColorStyle::brushInactive;
		}
	} else {
		p = ColorStyle::penNormal;
		b = ColorStyle::brushNormal;
	}

	g->DrawRectangle(p, rect.X, rect.Y, rect.Width, rect.Height); //35


	g->DrawString("I", ColorStyle::fontFamily, b, Rectangle(rect.X, rect.Y, rect.Width, rect.Height), ColorStyle::fontFormatCenter);

	Block::draw(g);
}