#include "frmMain.h"

#include "AND.h"
#include "Block.h"
#include "Line.h"
#include "Input.h"
#include "ColorStyle.h"

//using namespace System;
using namespace System::Windows::Forms;
using namespace PureLogic;

using namespace System::Drawing;

//AND mygate;
//AND mygate2;
//Input inpu;
//Input inpu2;

//Line connectionLine;
//Line connectionLine2;
//Line connectionLine3;

Point dragStart;
Point dragCurrent;
bool isDragging = false;

vector<Line *> connectionLines;
vector<Block *> blocks;

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

	ColorStyle::brushActive = gcnew SolidBrush(ColorStyle::colorActive);
	ColorStyle::brushInactive = gcnew SolidBrush(ColorStyle::colorInactive);
	ColorStyle::brushNormal = gcnew SolidBrush(ColorStyle::colorNormal);
	ColorStyle::brushBack = gcnew SolidBrush(ColorStyle::colorBack);

	ColorStyle::penActive = gcnew Pen(ColorStyle::colorActive);
	ColorStyle::penInactive = gcnew Pen(ColorStyle::colorInactive);
	ColorStyle::penNormal = gcnew Pen(ColorStyle::colorNormal);
	ColorStyle::penBack = gcnew Pen(ColorStyle::colorBack);

	ColorStyle::fontFamily = gcnew System::Drawing::Font("Courier New",8.0);
	ColorStyle::fontFormatFar = gcnew StringFormat();
	ColorStyle::fontFormatFar->LineAlignment = System::Drawing::StringAlignment::Far;

	ColorStyle::fontFormatCenter = gcnew StringFormat();
	ColorStyle::fontFormatCenter->LineAlignment = System::Drawing::StringAlignment::Center;
	ColorStyle::fontFormatCenter->Alignment = System::Drawing::StringAlignment::Center;

	connectionLines.push_back(new Line);
	connectionLines.push_back(new Line);
	//connectionLines.push_back(new Line);

	blocks.push_back(new Input); //inpu
	blocks[0]->setPos(50, 20);
	blocks[0]->attachLine(connectionLines[0], -1, 1);


	blocks.push_back(new Input); //inpu2
	blocks[1]->setPos(50, 56);
	blocks[1]->attachLine(connectionLines[1], -1, 1);

	blocks.push_back(new AND); //mygate
	blocks[2]->setPos(150, 20);
	blocks[2]->attachLine(connectionLines[0], -1, 0); //input
	blocks[2]->pinAdd();
	blocks[2]->pinAdd();
	blocks[2]->pinAdd();
	blocks[2]->pinAdd();
	blocks[2]->inputs[4]->setNegate(true);
	blocks[2]->inputs[0]->setNegate(true);
	blocks[2]->attachLine(connectionLines[1], 4, 0); //input
	//blocks[2]->attachLine(connectionLines[2], -1, 1); //output

	blocks.push_back(new AND); //mygate2
	blocks[3]->setPos(220, 20);
	//blocks[3]->attachLine(connectionLines[2], -1, 0);

	for (Block * b : blocks) {
		b->execute();
	}


	/*
	inpu.execute();
	inpu2.execute();
	mygate.execute();
	mygate2.execute();*/
}

void frmMain::frmMain_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	if (e->Button == System::Windows::Forms::MouseButtons::Left) {

		//if (mygate.pointInside(e->Location)) mygate.mouseDown(e->Location);
		//if (mygate2.pointInside(e->Location)) mygate2.mouseDown(e->Location);
		//if (inpu.pointInside(e->Location)) inpu.mouseDown(e->Location);
		//if (inpu2.pointInside(e->Location)) inpu2.mouseDown(e->Location);

		for (Block * b : blocks) {
			if (b->pointInside(e->Location)) b->mouseDown(e->Location);
		}

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
	Pin * pin1;
	Pin * pin2;
	Pin * pintemp;

	if (e->Button == System::Windows::Forms::MouseButtons::Left) {

		//mygate.mouseUp(e->Location);
		//mygate2.mouseUp(e->Location);
		//inpu.mouseUp(e->Location);
		//inpu2.mouseUp(e->Location);

		for (Block * b : blocks) {
			b->mouseUp(e->Location);
		}

	} else if (e->Button == System::Windows::Forms::MouseButtons::Right) {
		dragCurrent = e->Location;
		isDragging = false;

		for (Block * b : blocks) {
			pin1 = b->getSelectedPin(dragStart);
			if (pin1 != 0) break;
		}

		for (Block * b : blocks) {
			pin2 = b->getSelectedPin(dragCurrent);
			if (pin2 != 0) break;
		}

		//if we found the pins, connect them if we have one input and one output
		if (pin1 != 0 && pin2 != 0) {
			if (pin1->isOutput() ^ pin2->isOutput()) {
				
				if (pin2->isOutput()) {
					pintemp = pin1;
					pin1 = pin2;
					pin2 = pintemp;
				}

				if (!pin2->isConnected()){

					Line * l = new Line;
					connectionLines.push_back(l);

					pin1->getBlock()->attachLine(l, -1, 1);
					pin2->getBlock()->attachLine(l, -1, 0);

					l->setState(pin1->getState());
				} else {
					MessageBox::Show("Already Connected!");
				}
				

			} else {
				if (pin1 = pin2) {
					pin1->setNegate(!pin1->isNegated());
				} else {
					MessageBox::Show("Need one input and one output!");
				}
				
			}
		}

		//this needs to happen to create a line and connect it:
		//connectionLines.push_back(new Line);
		//blocks[2]->attachLine(connectionLines[2], -1, 1); //output
		//blocks[3]->attachLine(connectionLines[2], -1, 0);




	}

	frmMain::Refresh();
}


void frmMain::cmdAdd_Click(Object^  sender, EventArgs^  e) {
	//mygate.pinAdd();
	frmMain::Refresh();
}

void frmMain::cmdRemove_Click(Object^  sender, EventArgs^  e) {
	//mygate.pinRemove();
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

	//inpu.draw(g);
	//inpu2.draw(g);

	//mygate.draw(g);
	//mygate2.draw(g);
	

	for (Block * b : blocks) {
		b->draw(g);
	}

	for (Line * l : connectionLines) {
		l->draw(g);
	}

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

