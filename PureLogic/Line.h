#pragma once


#include "Pin.h"
class Pin;
value class ColorStyle;

using namespace System::Drawing;


class Line {
	public:
		Line();
		Line(Pin *i, Pin *o);
		~Line();
		void setInput(Pin *b);
		void setOutput(Pin *b);
		void draw(Graphics ^g);
		void setState(bool);
		bool getState();
		bool isPointOnLine(Point p);
		void setMouseOver(bool);

		Rectangle getPos();
		bool selected = false;

	private:
		Pin * Input = 0;
		Pin * Output = 0;
		bool positive;
		bool mouseOver;
		
};

