#include "Input.h"
#include "Pin.h"

using namespace System::Windows::Forms;

using namespace System::Drawing;

Input::Input() {
	output = new Pin(this,0,6,1);
	simulating = true;
	active = false;
}


Input::~Input() {

}


void Input::mouseDown(Point p) {
	//MessageBox::Show("input!");
	active = true;
	execute();
}

void Input::mouseUp(Point p) {
	//MessageBox::Show("input!");
	active = false;
	execute();
}

void Input::mouseMove(Point p) {
	//MessageBox::Show("input!");
}

bool Input::execute() {
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

void Input::draw(Graphics ^g) {
	Brush ^b;
	Pen ^p;

	pos.Height = (inputs.size() - 1) * 9 + 12;
	if (pos.Height < 21) pos.Height = 21;
	pos.Width = 25;

	output->draw(g);

	//draw background of block
	g->FillRectangle(ColorStyle::brushBack, pos.X, pos.Y, pos.Width, pos.Height); //35

	if (simulating) {
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

	g->DrawRectangle(p, pos.X, pos.Y, pos.Width, pos.Height); //35


	g->DrawString("I", ColorStyle::fontFamily, b, RectangleF(pos.X, pos.Y, pos.Width, 12), ColorStyle::fontFormatCenter);

}