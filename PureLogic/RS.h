#pragma once
#include "Block.h"
class RS : public Block {
	public:
		RS();
		~RS();

		virtual bool execute() override;
		void draw(Graphics ^g) override;

		void mouseDown(Point p) override;
		void mouseUp(Point p) override;
		void mouseMove(Point p) override;

	private:
		
};

