#pragma once

using namespace System::Drawing;

value class ColorStyle {
public:
	//ColorStyle();
	//virtual ~ColorStyle();

	static Color colorActive;
	static Color colorInactive;
	static Color colorNormal;
	static Color colorBack;
	static Color colorMouseOver;

	static Pen ^ penActive;
	static Pen ^ penInactive;
	static Pen ^ penNormal;
	static Pen ^ penBack;
	static Pen ^ penMouseOver;


	static Brush ^ brushActive;
	static Brush ^ brushInactive;
	static Brush ^ brushNormal;
	static Brush ^ brushBack;
	static Brush ^ brushMouseOver;

	static Font ^ fontFamily;
	static StringFormat ^ fontFormatCenter;
	static StringFormat ^ fontFormatFar;

};

