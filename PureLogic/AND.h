#pragma once


#include "Block.h"

using namespace System::Drawing;

class AND : public Block {
	public:
		AND();
		bool execute() override;
		void draw(Graphics ^g) override;
		void pinAdd() override;
		void pinRemove() override;

	private:
		const int pinsMin = 1;
		const int pinsMax = 10;
};

