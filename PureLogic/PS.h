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
			line = 3,
			scroll = 4
		};

		static enum class tooltipType : int {
			none = 0,
			warning = 1,
			error = 2,
			information = 3
		};

		static enum class blockTypes : int {
			AND = 0,
			OR = 1,
			ANDR = 2,
			ANDF = 3,
			RS = 4,
			INPUT = 5,
			NONE = 999
		};

		static bool simulating;

		static System::String ^ TooltipMessage;
		static bool TooltipVisible;
		static tooltipType TooltipMode;
		static Point TooltipPos;

		static void Tooltip(System::String ^ s, tooltipType m) {
			TooltipMode = m;
			TooltipVisible = true;
			TooltipMessage = s;
		}

		static void Tooltip(System::String ^ s) {
			Tooltip(s,tooltipType::none);
		}

		static void TooltipHide(){
			TooltipMode = tooltipType::none;
			TooltipVisible = false;
		}


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
		static Point scroll;
		static Point scrollStart;

		static int splitWindowPos;


		static blockTypes placeBlockType = blockTypes::NONE;
};

