#pragma once


#include <vector>
#include "line.h"
#include "Pin.h"

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
		void setColors(unsigned long  a, unsigned long  i, unsigned long  n, unsigned long  b);
		Rectangle getPos();
		void setPos(int,int); //x,y
		virtual void pinAdd() = 0;
		virtual void pinRemove() = 0;

		void attachLine(Line *p, int pinNum, int isOutput);
		void detachLine(Line *p);

		unsigned long colorActive;
		unsigned long colorInactive;
		unsigned long colorNormal;
		unsigned long colorBack;

		bool simulating;
		bool active;

		std::vector<Pin*> inputs;
		Pin * output;

	protected:
		Rectangle pos;
		int Height;

		
};

