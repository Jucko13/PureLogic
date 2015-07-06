#pragma once

#include "Pin.h"
#include "Line.h"

#include <string>

using namespace std;
using namespace System::Drawing;

class Pin;
class Line;

value class PS {
	public:
		static bool simulating;

		static System::String ^ TooltipMessage;

		static bool TooltipVisible;
		static Point TooltipPos;

		static Pin * mouseOverPin;
		static Line * mouseOverLine;

		static System::Timers::Timer^ timerRefresh;
		static bool refreshNeeded;
};

