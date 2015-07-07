#include "frmMain.h"

#include "AND.h"
#include "Block.h"
#include "Line.h"
#include "Input.h"
#include "ColorStyle.h"
#include "PS.h"


using namespace System::Windows::Forms;
using namespace PureLogic;

using namespace System::Drawing;

Point dragStart;
Point dragCurrent;
Pin * dragStartPin;

bool isDragging = false;

vector<Line *> connectionLines;
vector<Block *> blocks;

bool isRefreshing = false;

[STAThread]
int main(array<String^> ^args) {
	//Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	PureLogic::frmMain form;
	Application::Run(%form);

	return 0;
}

Rectangle getAbsoluteRectFromPoints(Point p1, Point p2) {
	Rectangle r;
	if (p1.X < p2.X) {
		r.X = p1.X;
		r.Width = p2.X - p1.X;
	} else {
		r.X = p2.X;
		r.Width = p1.X - p2.X;
	}

	if (p1.Y < p2.Y) {
		r.Y = p1.Y;
		r.Height = p2.Y - p1.Y;
	} else {
		r.Y = p2.Y;
		r.Height = p1.Y - p2.Y;
	}

	return r;
}

Pin * getPinAtPoint(Point p) {
	Pin * pinReturn;
	for (Block * b : blocks) {
		pinReturn = b->getSelectedPin(p);
		if (pinReturn != 0) break;
	}
	return pinReturn;
}

Line * getLineAtPoint(Point p) {
	for (Line * b : connectionLines) {
		if (b->isPointOnLine(p)) {
			return b;
		}
	}
	return 0;
}


unsigned long createRGB(int r, int g, int b) {
	return r + (g * 256) + (b * 256 * 256);
}

void frmMain::timerRefresh_Tick(Object^ state, System::Timers::ElapsedEventArgs^ e) {
	try {
		this->Invoke(gcnew MethodInvoker(this, &frmMain::Redraw));
		PS::timerRefresh->Start();
	} catch (System::ObjectDisposedException ^e) {
		
	}
}

void frmMain::Redraw() {
	if (PS::refreshNeeded) {
		this->pBackground->Invalidate();
		PS::refreshNeeded = false;
	}
}


void frmMain::pBackground_KeyDown(Object^  sender, KeyEventArgs^ e){
	if (e->Shift) lblStatusShift->Text = "Shift";
	if (e->Alt) lblStatusAlt->Text = "Alt";
	if (e->Control) lblStatusCtrl->Text = "Ctrl";
	//PS::TooltipMessage = e->Shift + " " + e->Alt + " " + e->Control;
	//PS::TooltipVisible = true;
}

void frmMain::pBackground_KeyUp(Object^  sender, KeyEventArgs^ e){
	if (!e->Shift) lblStatusShift->Text = "";
	if (!e->Alt) lblStatusAlt->Text = "";
	if (!e->Control) lblStatusCtrl->Text = "";
}

void frmMain::pBackground_KeyPress(Object^  sender, KeyPressEventArgs^ e){

}


void frmMain::frmMain_Unload(Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
	PS::timerRefresh->Stop();
	PS::timerRefresh->Enabled = false;
	PS::timerRefresh->Close();

	delete PS::timerRefresh;
}

void frmMain::frmMain_Load(System::Object^  sender, System::EventArgs^  e) {
	//MessageBox::Show("Startup test");
	

	ColorStyle::colorActive = Color(Color::FromArgb(255, 0, 0));
	ColorStyle::colorInactive = Color(Color::FromArgb(0, 0, 255));
	ColorStyle::colorNormal = Color(Color::FromArgb(0, 0, 0));
	ColorStyle::colorBack = Color(Color::FromArgb(255, 222, 140));
	ColorStyle::colorMouseOver = Color(Color::FromArgb(0, 255, 0));
	ColorStyle::colorSelected = Color(Color::FromArgb(120, 255, 0, 0));

	ColorStyle::brushActive = gcnew SolidBrush(ColorStyle::colorActive);
	ColorStyle::brushInactive = gcnew SolidBrush(ColorStyle::colorInactive);
	ColorStyle::brushNormal = gcnew SolidBrush(ColorStyle::colorNormal);
	ColorStyle::brushBack = gcnew SolidBrush(ColorStyle::colorBack);
	ColorStyle::brushMouseOver = gcnew SolidBrush(ColorStyle::colorMouseOver);
	ColorStyle::brushSelected = gcnew SolidBrush(ColorStyle::colorSelected);

	ColorStyle::penActive = gcnew Pen(ColorStyle::colorActive);
	ColorStyle::penInactive = gcnew Pen(ColorStyle::colorInactive);
	ColorStyle::penNormal = gcnew Pen(ColorStyle::colorNormal);
	ColorStyle::penBack = gcnew Pen(ColorStyle::colorBack);
	ColorStyle::penMouseOver = gcnew Pen(ColorStyle::colorMouseOver);
	ColorStyle::penSelected = gcnew Pen(ColorStyle::colorSelected);

	ColorStyle::fontFamily = gcnew System::Drawing::Font("Courier New",8.0);
	ColorStyle::fontFormatFar = gcnew StringFormat();
	ColorStyle::fontFormatFar->LineAlignment = System::Drawing::StringAlignment::Far;

	ColorStyle::fontFormatCenter = gcnew StringFormat();
	ColorStyle::fontFormatCenter->LineAlignment = System::Drawing::StringAlignment::Center;
	ColorStyle::fontFormatCenter->Alignment = System::Drawing::StringAlignment::Center;

	PS::simulating = false;
	//PS::TooltipMessage = new string;
	//PS::TooltipMessage->assign("lawla");
	PS::TooltipMessage = "";
	PS::TooltipVisible = false;
	
	PS::timerRefresh = gcnew System::Timers::Timer(10);
	PS::timerRefresh->BeginInit();
	PS::timerRefresh->AutoReset = false;
	PS::timerRefresh->Elapsed += gcnew System::Timers::ElapsedEventHandler(this, &frmMain::timerRefresh_Tick);
	PS::timerRefresh->EndInit();

	PS::timerRefresh->Start();

	int i = 0;
	int j = 0;
	int t = 0;

	for (j = 0; j < 4; j++) {
		for (i = 0; i < 10*4; i+=4) {
			
			connectionLines.push_back(new Line);
			connectionLines.push_back(new Line);
			connectionLines.push_back(new Line);
			connectionLines.push_back(new Line);

			blocks.push_back(new Input); //inpu
			blocks[t]->setPos(50 + j * 250, 20 + (i / 4) * 70);
			blocks[t]->attachLine(connectionLines[t], -1, 1);
			blocks[t]->attachLine(connectionLines[t + 3], -1, 1);
			//blocks[t]->selected = true;


			blocks.push_back(new Input); //inpu2
			blocks[t + 1]->setPos(50 + j * 250, 56 + (i / 4) * 70);
			blocks[t + 1]->attachLine(connectionLines[t + 1], -1, 1);

			blocks.push_back(new AND); //mygate
			blocks[t + 2]->setPos(150 + j * 250, 20 + (i / 4) * 70);
			blocks[t + 2]->attachLine(connectionLines[t], -1, 0); //input
			blocks[t + 2]->pinAdd();
			blocks[t + 2]->pinAdd();
			blocks[t + 2]->pinAdd();
			blocks[t + 2]->pinAdd();
			blocks[t + 2]->inputs[4]->setNegate(true);
			//blocks[i + 2]->inputs[0]->setNegate(true);
			blocks[t + 2]->attachLine(connectionLines[t + 1], 4, 0); //input
			blocks[t + 2]->attachLine(connectionLines[t + 2], -1, 1); //output
			blocks[t + 2]->attachLine(connectionLines[t + 3], -1, 0);

			blocks.push_back(new AND); //mygate2
			blocks[t + 3]->setPos(220 + j * 250, 20 + (i / 4) * 70);
			blocks[t + 3]->attachLine(connectionLines[t + 2], -1, 0);
			t += 4;
		}
		
	}

	for (Block * b : blocks) {
		b->execute();
	}

	PS::refreshNeeded = true;

}

void frmMain::pBackground_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	pBackground->Focus();
	
	if (e->Button == System::Windows::Forms::MouseButtons::Left) {

		for (Block * b : blocks) {
			if (b->pointInside(e->Location)) b->mouseDown(e->Location);
		}

		dragStartPin = 0;
		dragStart = e->Location;
		dragCurrent = e->Location;
		isDragging = true;
		pBackground_MouseMove(sender, e);

	} else if (e->Button == System::Windows::Forms::MouseButtons::Right) {
		
		dragStartPin = getPinAtPoint(e->Location);
		if (dragStartPin != 0) {
			dragStart = e->Location;
			dragCurrent = e->Location;
			isDragging = true;
			pBackground_MouseMove(sender, e);
		}
	}

	PS::refreshNeeded = true;
}

void frmMain::pBackground_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	
	
	
	if (!isDragging) {
		if (PS::mouseOverLine != 0) {
			PS::mouseOverLine->setMouseOver(false);
		}

		PS::mouseOverLine = getLineAtPoint(e->Location);
		if (PS::mouseOverLine != 0) {
			PS::mouseOverLine->setMouseOver(true);
		}
	}

	if (PS::mouseOverPin != 0) {
		PS::mouseOverPin->setBorder(false);
		PS::mouseOverPin = 0;
		PS::TooltipVisible = false;
	}

	PS::mouseOverPin = getPinAtPoint(e->Location);
	if (PS::mouseOverPin != 0) {
		
		if (isDragging && dragStartPin != 0) {
			if (PS::mouseOverPin == dragStartPin) {
				PS::TooltipVisible = true;
				PS::TooltipMessage = "Release to Negate PIN";
			} else if (!(PS::mouseOverPin->isOutput() ^ dragStartPin->isOutput())) {
				PS::TooltipVisible = true;
				PS::TooltipMessage = "PIN connection not allowed!\nOne INPUT PIN and one OUTPUT PIN!";
			} else if (!PS::mouseOverPin->isOutput() && PS::mouseOverPin->isConnected() || !dragStartPin->isOutput() && dragStartPin->isConnected()) {
				PS::TooltipVisible = true;
				PS::TooltipMessage = "PIN connection not allowed!\nINPUT PIN Already Connected!";
			} else {
				PS::TooltipVisible = false;
				PS::TooltipMessage = "";
			}
		}
		PS::mouseOverPin->setBorder(true);
	}
	
	


	if (isDragging) {
		dragCurrent = e->Location;
	}

	PS::TooltipPos = e->Location;

	PS::refreshNeeded = true;
}


void frmMain::pBackground_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	Pin * pin1;
	Pin * pin2;
	Pin * pintemp;

	if (e->Button == System::Windows::Forms::MouseButtons::Left) {
		for (Block * b : blocks) {
			b->mouseUp(e->Location);

			if (isDragging) {
				b->selected = false;
				if (getAbsoluteRectFromPoints(dragStart, dragCurrent).Contains(b->getPos())) {
					b->selected = true;
				}

			}else{

			}
		}

		bool checkSelect = (isDragging && dragStart != dragCurrent);

		for (Line * l : connectionLines) {
			l->selected = false;
			if (checkSelect) {
				if (getAbsoluteRectFromPoints(dragStart, dragCurrent).Contains(l->getPos())) {
					l->selected = true;
				}
			}
		}

		Line * li = getLineAtPoint(dragStart);

		if(li != 0){
			li->selected = true;
		}

		isDragging = false;

	} else if (e->Button == System::Windows::Forms::MouseButtons::Right) {
		dragCurrent = e->Location;
		isDragging = false;

		pin1 = getPinAtPoint(dragStart);
		pin2 = getPinAtPoint(dragCurrent);

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
					//MessageBox::Show("Already Connected!");
				}
				

			} else {
				if (pin1 == pin2) {
					pin1->setNegate(!pin1->isNegated());
				} else {
					//MessageBox::Show("Need one input and one output!");
				}
				
			}
		}

	}

	frmMain::Refresh();
}


void frmMain::cmdAdd_Click(Object^  sender, EventArgs^  e) {
	PS::simulating = !PS::simulating;

	if (!isRefreshing) frmMain::Refresh();
}

void frmMain::cmdRemove_Click(Object^  sender, EventArgs^  e) {
	if (!isRefreshing) frmMain::Refresh();
}


void frmMain::pBackground_Paint(Object^  sender, PaintEventArgs^  e) {

	System::Drawing::Graphics ^g = e->Graphics;
	Drawing::SolidBrush ^programBackground = gcnew Drawing::SolidBrush(Color::FromArgb(180, 180, 180));
	Drawing::Pen ^blockBorder = gcnew Pen(Drawing::Color::Black);
	
	Drawing::SolidBrush ^selectionBack = gcnew Drawing::SolidBrush(Color::FromArgb(80, 0, 162, 232));
	Drawing::Pen ^selectionBorder = gcnew Pen(Color::FromArgb(0, 162, 232));

	//e->Graphics->

	//g->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;


	//paint background
	//g->FillRectangle(programBackground, frmMain::ClientRectangle);

	for (Block * b : blocks) {
		b->draw(g);
	}

	for (Line * l : connectionLines) {
		l->draw(g);
	}

	if (isDragging) {
		if (dragStartPin != 0){
			g->DrawLine(blockBorder, dragStart, dragCurrent);
		}else{
			Rectangle selection = getAbsoluteRectFromPoints(dragStart, dragCurrent);

			g->FillRectangle(selectionBack, selection);
			g->DrawRectangle(selectionBorder, selection);
		}
	}
	
	if (PS::TooltipVisible) {
		System::Drawing::SizeF sSize = g->MeasureString(PS::TooltipMessage, ColorStyle::fontFamily);

		Point tooltip = Point(PS::TooltipPos.X - (int)sSize.Width - 10, PS::TooltipPos.Y+15);

		if (tooltip.X < 0) {
			tooltip.X = 0;
		} else if (tooltip.X + sSize.Width + 6 > ClientRectangle.Width) {
			tooltip.X = ClientRectangle.Width - (sSize.Width + 6);
		}

		//draw shadow of tooltip
		Drawing::SolidBrush ^ br = gcnew Drawing::SolidBrush(Color::FromArgb(128, 0, 0, 0));
		g->FillRectangle(br, tooltip.X + 2, tooltip.Y + 2, (int)sSize.Width + 6, (int)sSize.Height + 6);

		//draw tooltip
		g->FillRectangle(ColorStyle::brushBack, tooltip.X, tooltip.Y, (int)sSize.Width + 6, (int)sSize.Height + 6);
		g->DrawRectangle(ColorStyle::penNormal, tooltip.X, tooltip.Y, (int)sSize.Width + 6, (int)sSize.Height + 6);

		//draw text on tooltip
		g->DrawString(PS::TooltipMessage, ColorStyle::fontFamily, ColorStyle::brushNormal, tooltip.X + 3, tooltip.Y + 3);
	}

	//Application::DoEvents();
}

