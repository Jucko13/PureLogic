#pragma once

#include <vector>
#include "Block.h"
#include "Line.h"
class Block;
class Line;
value class ColorStyle;


using namespace System::Drawing;
using std::vector;

public class Pin {
	public:
		Pin(Block *b, int X, int Y, bool o);
		virtual ~Pin();
		void setPos(int,int);
		void draw(Graphics ^g);
		bool getState();
		bool isConnected();
		bool isOutput();
		bool isNegated();
		void setState(bool);
		void setNegate(bool);
		void attachLine(Line *p);
		void deatachLine(Line *p);
		Point getPos();
		Block* getBlock();

		void setBorder(bool);

		std::vector<Line *> lines;

	private:
		//Block ^connection;
		Point offsetPos;
		Rectangle pos;


		bool border;
		bool positive;
		Block * connectedBlock;
		bool output;
		bool negate;

		
};
