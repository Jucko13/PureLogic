#include "frmMain.h"

#include "AND.h"
#include "Block.h"
#include "Line.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace PureLogic;

AND mygate;
AND mygate2;
Line connectionLine;

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
	mygate.setPos(20,20);


	mygate2.setPos(80, 20);

	mygate.attachLine(&connectionLine,-1,1);
	mygate2.attachLine(&connectionLine, -1, 0);


	mygate.setColors(createRGB(255, 0, 0), createRGB(0, 0, 255), createRGB(0, 0, 0), createRGB(255, 222, 140));
	mygate2.setColors(createRGB(255, 0, 0), createRGB(0, 0, 255), createRGB(0, 0, 0), createRGB(255, 222, 140));


	mygate.execute();
	mygate2.execute();
}

void frmMain::frmMain_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	if (e->Button == System::Windows::Forms::MouseButtons::Left) {
		mygate.pinAdd();
		frmMain::Refresh();
	} else if (e->Button == System::Windows::Forms::MouseButtons::Right) {
		mygate.pinRemove();
		frmMain::Refresh();
	}
}

void frmMain::frmMain_Paint(System::Object^  sender, PaintEventArgs^  e) {
	System::Drawing::Graphics ^g = e->Graphics;
	
	array<Color> ^blockColors = gcnew array<Color>(4) {
		Color::FromArgb(255, 222, 140), //background color
		Color::FromArgb(0, 0, 0),		//border color normal
		Color::FromArgb(255, 0, 0),		//border color active
		Color::FromArgb(0, 0, 255)		//border color inactive
	};


	Drawing::SolidBrush ^programBackground = gcnew Drawing::SolidBrush(Color::FromArgb(180, 180, 180));
	Drawing::Pen ^blockBorder = gcnew Pen(Drawing::Color::Black);
	

	//paint background
	g->FillRectangle(programBackground, frmMain::ClientRectangle);

	mygate.draw(g);
	mygate2.draw(g);
	connectionLine.draw(g);
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

