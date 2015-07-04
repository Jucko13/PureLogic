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
	output = new Pin(this,0,0,1);
	simulating = true;
}

void AND::pinAdd() {
	int i = inputs.size();
	if (i < pinsMax)
		inputs.push_back(new Pin(this, 0, i * 9 + 6, 0));
}

void AND::pinRemove() {
	int i = inputs.size();
	if (i - 1 >= pinsMin) {
		Pin * p = inputs[i - 1];
		inputs.pop_back();
		delete p;
		//
	}
}


bool AND::execute() {
	for (Pin *i : inputs) {
		if (i->isPositive() == false) {
			active = false;
			output->setState(false);
			return false;
		}
	}
	output->setState(true);
	active = true;
	return true;
}

void AND::draw(Graphics ^g) {
	SolidBrush ^b = gcnew SolidBrush(Color::Black);
	Pen ^p = gcnew Pen(Color::Black);


	pos.Height = (inputs.size()-1) * 9 + 12;
	if (pos.Height < 21) pos.Height = 21;
	pos.Width = 25;

	output->draw(g);

	for (Pin *i : inputs) {
		i->draw(g);
	}


	//draw background of block
	b->Color = ColorTranslator::FromOle(colorBack);
	g->FillRectangle(b, pos.X, pos.Y, pos.Width, pos.Height); //35

	//draw border of block
	if (simulating) {
		if (active) {
			p->Color = ColorTranslator::FromOle(colorActive);
			b->Color = p->Color;
		} else {
			p->Color = ColorTranslator::FromOle(colorInactive);
			b->Color = p->Color;
		}
	}else {
		p->Color = ColorTranslator::FromOle(colorNormal);
		b->Color = p->Color;
	}
	g->DrawRectangle(p, pos.X, pos.Y, pos.Width, pos.Height); //35


	Font ^ f = gcnew Font("Courier New",8.0);
	StringFormat ^ sf = gcnew StringFormat();
	sf->LineAlignment = System::Drawing::StringAlignment::Far;

	//draw the Add button to add a pin on the input
	if (inputs.size() > 1 && inputs.size() < 10) {
		g->DrawString("+-", f, b, RectangleF(pos.X, pos.Y, pos.Width, pos.Height), sf);
	} else if (inputs.size() > 1) {
		g->DrawString(" -", f, b, RectangleF(pos.X, pos.Y, pos.Width, pos.Height), sf);
	} else {
		g->DrawString("+", f, b, RectangleF(pos.X, pos.Y, pos.Width, pos.Height), sf);
	}

	sf->Alignment = System::Drawing::StringAlignment::Center;
	sf->LineAlignment = System::Drawing::StringAlignment::Center;
	g->DrawString("&", f, b, RectangleF(pos.X, pos.Y, pos.Width, 12), sf);
	


}