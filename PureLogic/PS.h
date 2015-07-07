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

		static Pin * mouseOverPin = 0;
		static Line * mouseOverLine = 0;

		static System::Timers::Timer^ timerRefresh;
		static bool refreshNeeded = false;

		static bool keyShift = false;
		static bool keyCtrl = false;
		static bool keyAlt = false;

};

