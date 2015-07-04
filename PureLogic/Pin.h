#pragma once

#include <vector>
#include "Block.h"
#include "Line.h"
class Block;
class Line;


using namespace System::Drawing;
using std::vector;

public class Pin {
	public:
		Pin(Block *b, int X, int Y, bool o);
		virtual ~Pin();
		void setPos(int,int);
		void draw(Graphics ^g);
		bool isPositive();
		bool isConnected();
		bool isNegated();
		void setState(bool);
		void setNegate(bool);
		void attachLine(Line *p);
		Point getPos();
		Block* getBlock();

	private:
		//Block ^connection;
		Point offsetPos;
		Rectangle pos;

		bool positive;
		Block * connectedBlock;
		bool isOutput;
		bool negate;

		std::vector<Line *> lines;
};
