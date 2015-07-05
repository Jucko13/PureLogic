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

	private:
		Pin * Input;
		Pin * Output;
		bool positive;
};

