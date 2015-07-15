#pragma once

#include "Block.h"

using namespace System::Drawing;

class AND : public Block {
	public:
		AND();
		AND(std::string, std::wstring, PS::blockTypes t);
		virtual ~AND();

		virtual bool execute() override;
		void draw(Graphics ^g) override;

		void pinAdd() override;
		void pinRemove() override;

		void mouseDown(Point p) override;
		void mouseUp(Point p) override;
		void mouseMove(Point p) override;

		const bool mayAddPin = true;
	private:
		const int pinsMin = 2;
		const int pinsMax = 10;
		Rectangle posPlus;
		Rectangle posMin;
		std::wstring mark;

};

