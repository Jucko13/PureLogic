#pragma once
#include "AND.h"
class ANDR : public AND {
	public:
		ANDR();
		virtual ~ANDR();
		bool execute() override;
};

