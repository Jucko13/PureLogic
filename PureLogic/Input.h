#pragma once
#include "Block.h"

using namespace System::Drawing;


class INPUT : public Block {
	public:
		INPUT();
		virtual ~INPUT();

		bool execute() override;
		void draw(Graphics ^g) override;

		void mouseDown(Point p) override;
		void mouseUp(Point p) override;
		void mouseMove(Point p) override;

		const bool mayAddPin = false;

	private:
		int pressState = 0;

};

