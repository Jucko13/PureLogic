#pragma once


#include <vector>
#include "line.h"
#include "Pin.h"
#include "ColorStyle.h"
#include "PS.h"


class Pin;
class Line;

using namespace System::Drawing;
using std::vector;

class Block abstract {
	public:
		Block(std::string n);
		virtual ~Block();

		virtual bool execute() = 0;
		virtual void draw(Graphics ^g) = 0;

		virtual void mouseDown(Point p) = 0;
		virtual void mouseUp(Point p) = 0;
		virtual void mouseMove(Point p) = 0;
		
		bool isSelected();


		Rectangle getPos();
		void setPos(int,int); //x,y

		virtual void pinAdd();
		virtual void pinRemove();
		Pin * getSelectedPin(Point p);
		std::vector<Pin*> inputs;
		Pin * output;
		void attachLine(Line *p, int pinNum, int isOutput);
		void detachLine(Line *p);

		bool active;
		bool pointInside(Point p);
		std::string getName();
		

	protected:
		Rectangle pos;

	private:
		std::string name;
		bool selected;

};

