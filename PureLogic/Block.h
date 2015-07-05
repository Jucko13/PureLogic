#pragma once


#include <vector>
#include "line.h"
#include "Pin.h"
#include "ColorStyle.h"


class Pin;
class Line;

using namespace System::Drawing;
using std::vector;

class Block abstract {
	public:
		Block();
		virtual ~Block();

		virtual bool execute() = 0;
		virtual void draw(Graphics ^g) = 0;

		virtual void mouseDown(Point p) = 0;
		virtual void mouseUp(Point p) = 0;
		virtual void mouseMove(Point p) = 0;

		//void setColors(unsigned long  a, unsigned long  i, unsigned long  n, unsigned long  b);
		Rectangle getPos();
		void setPos(int,int); //x,y

		virtual void pinAdd();
		virtual void pinRemove();
		bool pointInside(Point p);
		Pin * getSelectedPin(Point p);

		void attachLine(Line *p, int pinNum, int isOutput);
		void detachLine(Line *p);

		

		bool simulating;
		bool active;

		std::vector<Pin*> inputs;
		Pin * output;

	protected:
		Rectangle pos;
		
};

