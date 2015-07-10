#pragma once

#include <vcclr.h>
#include "Pin.h"
class Pin;
value class ColorStyle;

using namespace System::Drawing;

class Line {
	public:
		Line(void(*f)(Line*));
		~Line();
		void setInput(Pin *b);
		void setOutput(Pin *b);
		Pin * getInput();
		Pin * getOutput();

		void draw(Graphics ^g);
		void setState(bool);
		bool getState();

		bool getRecursive();
		void setRecursive(bool);
		void activateRecursive();

		bool isPointOnLine(Point p);
		void setMouseOver(bool);

		Rectangle getPos();
		bool selected = false;



	private:
		Pin * Input = 0;
		Pin * Output = 0;
		bool positive;
		bool mouseOver;
		bool recursive;
		bool nextState;
		void(*addToQuery)(Line*);

		//gcroot<System::Timers::Timer ^> tmrRecursive;
		//void tmrRecursive_Tick(System::Object ^sender, System::Timers::ElapsedEventArgs ^e);

};

