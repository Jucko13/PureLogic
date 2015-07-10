#pragma once

#include "Pin.h"
#include "Line.h"

#include <string>

#include <cliext/vector>

using namespace std;
using namespace System::Drawing;

class Pin;
class Line;



value class PS {
	public:
		static enum class dragType: int {
			none = 0,
			selecting = 1,
			moving = 2,
			line = 3
		};

		static bool simulating;

		static System::String ^ TooltipMessage;
		static bool TooltipVisible;
		static Point TooltipPos;

		static Pin * mouseOverPin = 0;
		static Line * mouseOverLine = 0;

		static System::Timers::Timer^ timerRefresh;
		static System::Timers::Timer^ timerRecursive;

		static bool refreshNeeded = false;

		static System::Windows::Forms::KeyEventArgs^ keys;

		static Point dragStart;
		static Point dragCurrent;
		static Pin * dragStartPin;
		static dragType dragMode;

		static double zoom;
};

