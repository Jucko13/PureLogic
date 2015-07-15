#pragma once
#include "AND.h"
class ANDF : public AND {
	public:
		ANDF();
		virtual ~ANDF();
		bool execute() override;


};

