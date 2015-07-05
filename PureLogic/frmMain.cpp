#include "frmMain.h"

#include "AND.h"
#include "Block.h"
#include "Line.h"
#include "Input.h"
#include "ColorStyle.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace PureLogic;

using namespace System::Drawing;

AND mygate;
AND mygate2;
Input inpu;
Input inpu2;

Line connectionLine;
Line connectionLine2;
Line connectionLine3;

Point dragStart;
Point dragCurrent;
bool isDragging = false;


[STAThread]
int main(array<String^> ^args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	PureLogic::frmMain form;
	Application::Run(%form);

	return 0;
}

unsigned long createRGB(int r, int g, int b) {
	return r + (g * 256) + (b * 256 * 256);
}


void frmMain::frmMain_Load(System::Object^  sender, System::EventArgs^  e) {
	//MessageBox::Show("Startup test");
	

	ColorStyle::colorActive = Color(Color::FromArgb(255, 0, 0));
	ColorStyle::colorInactive = Color(Color::FromArgb(0, 0, 255));
	ColorStyle::colorNormal = Color(Color::FromArgb(0, 0, 0));
	ColorStyle::colorBack = Color(Color::FromArgb(255, 222, 140));

	inpu.setPos(50, 20);
	inpu2.setPos(50, 56);
	mygate.setPos(150,20);
	mygate2.setPos(220, 20);
	

	inpu.attachLine(&connectionLine2,-1,1);
	mygate.attachLine(&connectionLine2, -1, 0);


	inpu2.attachLine(&connectionLine3, -1, 1);
	mygate.pinAdd();
	mygate.pinAdd();
	mygate.pinAdd();
	mygate.pinAdd();
	mygate.inputs[4]->setNegate(true);
	mygate.inputs[0]->setNegate(true);
	mygate.attachLine(&connectionLine3, 4, 0);



	mygate.attachLine(&connectionLine, -1, 1);
	mygate2.attachLine(&connectionLine, -1, 0);


	inpu.execute();
	inpu2.execute();
	mygate.execute();
	mygate2.execute();
}

void frmMain::frmMain_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	if (e->Button == System::Windows::Forms::MouseButtons::Left) {

		if (mygate.pointInside(e->Location)) mygate.mouseDown(e->Location);
		if (mygate2.pointInside(e->Location)) mygate2.mouseDown(e->Location);
		if (inpu.pointInside(e->Location)) inpu.mouseDown(e->Location);
		if (inpu2.pointInside(e->Location)) inpu2.mouseDown(e->Location);

	} else if (e->Button == System::Windows::Forms::MouseButtons::Right) {
		dragStart = e->Location;
		dragCurrent = e->Location;
		isDragging = true;
	}

	frmMain::Refresh();
}

void frmMain::frmMain_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	if (isDragging) {
		dragCurrent = e->Location;
		frmMain::Refresh();
	}
}

void frmMain::frmMain_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	if (e->Button == System::Windows::Forms::MouseButtons::Left) {

		mygate.mouseUp(e->Location);
		mygate2.mouseUp(e->Location);
		inpu.mouseUp(e->Location);
		inpu2.mouseUp(e->Location);

	} else if (e->Button == System::Windows::Forms::MouseButtons::Right) {
		dragCurrent = e->Location;
		isDragging = false;





	}

	frmMain::Refresh();
}


void frmMain::cmdAdd_Click(Object^  sender, EventArgs^  e) {
	mygate.pinAdd();
	frmMain::Refresh();
}

void frmMain::cmdRemove_Click(Object^  sender, EventArgs^  e) {
	mygate.pinRemove();
	frmMain::Refresh();
}



void frmMain::frmMain_Paint(Object^  sender, PaintEventArgs^  e) {
	System::Drawing::Graphics ^g = e->Graphics;

	//array<Color> ^blockColors = gcnew array<Color>(4) {
	//	Color::FromArgb(255, 222, 140), //background color
	//		Color::FromArgb(0, 0, 0),		//border color normal
	//		Color::FromArgb(255, 0, 0),		//border color active
	//		Color::FromArgb(0, 0, 255)		//border color inactive
	//};
	
	Drawing::SolidBrush ^programBackground = gcnew Drawing::SolidBrush(Color::FromArgb(180, 180, 180));
	Drawing::Pen ^blockBorder = gcnew Pen(Drawing::Color::Black);
	
	g->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::HighSpeed;


	//paint background
	g->FillRectangle(programBackground, frmMain::ClientRectangle);

	inpu.draw(g);
	inpu2.draw(g);

	mygate.draw(g);
	mygate2.draw(g);
	connectionLine.draw(g);
	connectionLine2.draw(g);
	connectionLine3.draw(g);

	if (isDragging) {
		g->DrawLine(blockBorder, dragStart, dragCurrent);
	}
	

	//
	//
	//////draw background of block
	////b->Color = blockColors[0];
	////g->FillRectangle(b, 40, 40, 25, 35);
	//
	////draw border of block
	//p->Color = blockColors[3];
	//g->DrawRectangle(p, 40, 40, 25, 35);


	////draw inputs
	//g->DrawLine(p, 30, 44, 40, 44);
	//g->DrawLine(p, 30, 53, 40, 53);
	//g->DrawLine(p, 30, 62, 40, 62);
	//g->DrawLine(p, 30, 71, 40, 71);

	//b->Color = blockColors[1];
	////draw block type
	//Drawing::Font ^ f = gcnew Drawing::Font("Courier New",8.0);
	//StringFormat ^ sf = gcnew StringFormat();
	//sf->Alignment = System::Drawing::StringAlignment::Center;

	//g->DrawString("&", f, b, RectangleF(40, 40, 25, 20), sf);

}

