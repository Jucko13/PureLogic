#pragma once
#include "AND.h"
class OR : public AND {
	public:
		OR();
		virtual ~OR();
		bool execute() override;

};

