#include "RS.h"


RS::RS() : Block("Set Reset", PS::blockTypes::RS) {
	inputs.push_back(new Pin(this, 0, 10, 0));
	inputs.push_back(new Pin(this, 0, 20, 0));

	output = new Pin(this, 0, 10, 1);
}


RS::~RS() {
}



bool RS::execute(){
	
	if (inputs[1]->isConnected()) {
		if (inputs[1]->getState()) {
			if (active){
				active = false;
				output->setState(false);
				return false;
			}
		}
	}

	if (inputs[0]->isConnected()) {
		if(inputs[0]->getState()){
			if (!inputs[1]->getState()) {
				if (!active) {
					active = true;
					output->setState(true);
					return true;
				}
			}
		}
	}
	
	return active;
}

void RS::mouseDown(Point p) {
	
}

void RS::mouseUp(Point p) {

}

void RS::mouseMove(Point p) {

}



void RS::draw(Graphics ^g) {
	Brush ^b;
	Brush ^b2;
	Pen ^p;

	pos.Height = 30;
	if (pos.Height < 20) pos.Height = 20;
	pos.Width = 20;

	Rectangle rect = getPos();
	rect.X += PS::scroll.X;
	rect.Y += PS::scroll.Y;

	output->draw(g);
	inputs[0]->draw(g);
	inputs[1]->draw(g);
	
	if (PS::simulating) {
		if (active) {
			b = ColorStyle::brushActive;
		} else {
			p = ColorStyle::penInactive;
			b = ColorStyle::brushInactive;
		}
		b2 = ColorStyle::brushBack;
		p = ColorStyle::penBack;
	} else {
		p = ColorStyle::penNormal;
		b = ColorStyle::brushBack;
		b2 = ColorStyle::brushNormal;
	}

	//draw background of block
	g->FillRectangle(b, rect);

	//draw border of block
	g->DrawRectangle(p, rect);

	//draw the text on the block
	g->DrawString("RS", ColorStyle::fontFamily, b2, Rectangle(rect.X - 4, rect.Y, rect.Width + 8, ColorStyle::fontFamily->Size + 2), ColorStyle::fontFormatCenter);

	Block::draw(g);
}