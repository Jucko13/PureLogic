#include "Input.h"
#include "Pin.h"

using namespace System::Windows::Forms;

using namespace System::Drawing;

Input::Input() {
	output = new Pin(this,0,6,1);
	simulating = true;

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
	SolidBrush ^b = gcnew SolidBrush(Color::Black);
	Pen ^p = gcnew Pen(Color::Black);

	pos.Height = (inputs.size() - 1) * 9 + 12;
	if (pos.Height < 21) pos.Height = 21;
	pos.Width = 25;

	output->draw(g);

	//draw background of block
	b->Color = ColorStyle::colorBack;
	g->FillRectangle(b, pos.X, pos.Y, pos.Width, pos.Height); //35


	if (simulating) {
		if (active) {
			p->Color = ColorStyle::colorActive;
			b->Color = p->Color;
		} else {
			p->Color = ColorStyle::colorInactive;
			b->Color = p->Color;
		}
	} else {
		p->Color = ColorStyle::colorNormal;
		b->Color = p->Color;
	}

	g->DrawRectangle(p, pos.X, pos.Y, pos.Width, pos.Height); //35

	Font ^ f = gcnew Font("Courier New", 8.0);
	StringFormat ^ sf = gcnew StringFormat();
	sf->LineAlignment = System::Drawing::StringAlignment::Far;

	sf->Alignment = System::Drawing::StringAlignment::Center;
	sf->LineAlignment = System::Drawing::StringAlignment::Center;
	g->DrawString("I", f, b, RectangleF(pos.X, pos.Y, pos.Width, 12), sf);

}