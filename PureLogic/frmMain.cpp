#include "frmMain.h"

#include "AND.h"
#include "Block.h"
#include "Line.h"
#include "Input.h"
#include "ColorStyle.h"
#include "PS.h"
#include <algorithm>


using namespace System::Windows::Forms;
using namespace PureLogic;

using namespace System::Drawing;

//Point dragStart;
//Point dragCurrent;
//Pin * dragStartPin;

//bool isDragging = false;

vector<Line *> connectionLines;
vector<Block *> blocks;
vector<Line *> recurse;

bool isRefreshing = false;

int repeatCounter = 0;


[STAThread]
int main(array<String^> ^args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	PureLogic::frmMain form;
	Application::Run(%form);

	return 0;
}

bool findRecursiveConnection(Pin * pStart, Pin * pEnd){
	Block * bTmp;
	Pin * pTmp;
	Pin * loopStart;

	loopStart = pStart;

	if (!pStart->isOutput()) { //is an input.
		bTmp = pStart->getBlock();
		pTmp = bTmp->output;
		if (pTmp != pEnd) {
			if (pTmp->isConnected()){
				for (Line * l : pTmp->lines) {
					if(l->getRecursive()) return false;
					if (findRecursiveConnection(l->getInput(), pEnd)) return true;
				}
			}else{
				return false;
			}
		}else{
			return true;
		}
	}
	return false;
}

bool getIntersectionOfRects(Rectangle *r1, Rectangle *r2) {
	return (r1->X >= r2->X && r1->X <= r2->X + r2->Width || r2->X >= r1->X && r2->X <= r1->X + r1->Width) && (r1->Y >= r2->Y && r1->Y <= r2->Y + r2->Height || r2->Y >= r1->Y && r2->Y <= r1->Y + r1->Height);
}

void removeLine(Line * l){
	if (l->getRecursive()) {
		for (unsigned int j = 0; j < recurse.size(); j++) {
			if (recurse[j] == l) {
				recurse[j] = NULL;
			}
		}
	}

	for (unsigned int j = 0; j < connectionLines.size(); j++) {
		if (connectionLines[j] == l) {
			delete connectionLines[j];
			connectionLines[j] = NULL;
		}
	}
}


void removeSelectedItems() {
	for (unsigned int i = 0; i < blocks.size(); i++) {
		if (blocks[i]->selected) {

			for (Pin * p : blocks[i]->inputs) {
				if (p->isConnected()) {
					while (p->lines.size() > 0) {
						removeLine(p->lines[0]);
					}
				}
			}

			if (blocks[i]->output->isConnected()) {
				while (blocks[i]->output->lines.size() > 0) {
					removeLine(blocks[i]->output->lines[0]);
					
				}
			}

			delete blocks[i];
			blocks[i] = NULL;
		}
	}

	for (unsigned int j = 0; j < connectionLines.size(); j++) {
		if (connectionLines[j] != 0 && connectionLines[j]->selected) {
			if (connectionLines[j]->getRecursive()) {
				for (unsigned int k = 0; k < recurse.size(); k++) {
					if (recurse[k] == connectionLines[j]) {
						recurse[k] = NULL;
					}
				}
			}

			delete connectionLines[j];
			connectionLines[j] = NULL;
		}
	}


	blocks.erase(std::remove(blocks.begin(), blocks.end(), static_cast<Block*>(NULL)), blocks.end());
	connectionLines.erase(std::remove(connectionLines.begin(), connectionLines.end(), static_cast<Line*>(NULL)), connectionLines.end());
}

bool getAbsoluteRectFromPoints(Point ^p1, Point ^p2,Rectangle *r) {
	if (p1->Y < p2->Y) {
		r->Y = p1->Y;
		r->Height = p2->Y - p1->Y;
	} else {
		r->Y = p2->Y;
		r->Height = p1->Y - p2->Y;
	}

	if (p1->X < p2->X) {
		r->X = p1->X;
		r->Width = p2->X - p1->X;
		return false;
	} else {
		r->X = p2->X;
		r->Width = p1->X - p2->X;
		return true;
	}
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
	for (Line * l : connectionLines) {
		if (l->isPointOnLine(p)) {
			return l;
		}
	}
	return 0;
}

Block * getBlockAtPoint(Point p){
	for (Block * b : blocks) {
		if (b->getPos().Contains(p)) {
			return b;
		}
	}
	return 0;
}


unsigned long createRGB(int r, int g, int b) {
	return r + (g * 256) + (b * 256 * 256);
}

void addLineToQuery(Line * l) {
	bool found = false;
	for(Line * l1: recurse){
		if (l1 == l){
			if (found) return;
			found = true;
		}
	}
	recurse.push_back(l);
	//PS::refreshNeeded = true;
	//MessageBox::Show("added!");
}

void frmMain::timerRecursive_Tick(Object^ state, System::Timers::ElapsedEventArgs^ e) {
	unsigned int s = recurse.size();
	if (s > 0) {
		for (unsigned int i = 0; i < s; i++) {
			if (recurse[i]){
				recurse[i]->activateRecursive();
				repeatCounter++;
			}
			recurse[i] = NULL;
		}

		recurse.erase(std::remove(recurse.begin(), recurse.end(), static_cast<Line*>(NULL)), recurse.end());

		PS::refreshNeeded = true;
		PS::TooltipMessage = "count: " + s;
		PS::TooltipVisible = true;

	}
}


void frmMain::timerRefresh_Tick(Object^ state, System::Timers::ElapsedEventArgs^ e) {
	if (PS::refreshNeeded) {
		this->pBackground->Invalidate();
		PS::refreshNeeded = false;
		
	}
}


void frmMain::pBackground_KeyDown(Object^  sender, KeyEventArgs^ e){
	PS::keys = e;

	if (e->Shift) lblStatusShift->Text = "Shift";
	if (e->Alt) lblStatusAlt->Text = "Alt";
	if (e->Control) lblStatusCtrl->Text = "Ctrl";

	switch (e->KeyCode){
		case Keys::Enter:
			for (Block * b : blocks) {
				if (b->selected) {
					b->mouseDown(Point(0, 0));
				}
			}
		break;

		case Keys::F2:
			tcmdSimulateStart->PerformClick();
			break;

		case Keys::F3:
			tcmdSimulateStop->PerformClick();
			break;

		case Keys::Escape:
			switch (PS::dragMode) {
				case PS::dragType::moving:
					for (Block * b : blocks) {
						b->setPosOffset(Point(0,0));
					}
					PS::dragMode = PS::dragType::none;
			}
		break;
	}

	PS::refreshNeeded = true;

	//PS::TooltipMessage = e->Shift + " " + e->Alt + " " + e->Control;
	//PS::TooltipVisible = true;
}

void frmMain::pBackground_KeyUp(Object^  sender, KeyEventArgs^ e){
	PS::keys = e;

	if (!e->Shift) lblStatusShift->Text = "";
	if (!e->Alt) lblStatusAlt->Text = "";
	if (!e->Control) lblStatusCtrl->Text = "";

	if(PS::simulating){
		switch (e->KeyCode) {
			case Keys::Enter:
				for (Block * b : blocks) {
					b->mouseUp(Point(0, 0));
				}
				break;
		}
	}else{
		switch (e->KeyCode) {
		
			case Keys::Delete:
				removeSelectedItems();
				break;

		}
	}

	PS::refreshNeeded = true;
	
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
	
	pBackground->BackColor = Color(Color::FromArgb(180, 180, 180));

	ColorStyle::colorActive = Color(Color::FromArgb(255, 0, 0));        //255, 0, 0
	ColorStyle::colorInactive = Color(Color::FromArgb(0, 0, 255));      //0, 0, 255
	ColorStyle::colorNormal = Color(Color::FromArgb(0, 0, 0));          //0, 0, 0
	ColorStyle::colorBack = Color(Color::FromArgb(82, 204, 255));        //255, 222, 140
	ColorStyle::colorMouseOver = Color(Color::FromArgb(0, 255, 0));     //0, 255, 0
	ColorStyle::colorSelected = Color(Color::FromArgb(120, 255, 0, 0)); //120, 255, 0, 0

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

	PS::zoom = 1.0;
	 
	//dpi scaling compensation calculation
	Graphics ^g = pBackground->CreateGraphics();
	float scaleDpi = 96.0f / g->DpiX;
	ColorStyle::fontFamily = gcnew System::Drawing::Font("Courier New", scaleDpi * 8.0f * PS::zoom);
	lblStatusAlt->Font = gcnew System::Drawing::Font("Courier New", scaleDpi * 10.0f * PS::zoom);
	lblStatusCtrl->Font = lblStatusAlt->Font;
	lblStatusShift->Font = lblStatusAlt->Font;
	lblStatusAlt->Text = "";
	lblStatusCtrl->Text = "";
	lblStatusShift->Text = "";
	delete g;

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
	
	PS::timerRefresh = gcnew System::Timers::Timer(9);
	PS::timerRefresh->BeginInit();
	PS::timerRefresh->AutoReset = true;
	PS::timerRefresh->Elapsed += gcnew System::Timers::ElapsedEventHandler(this, &frmMain::timerRefresh_Tick);
	PS::timerRefresh->EndInit();

	PS::timerRefresh->Start();

	PS::timerRecursive = gcnew System::Timers::Timer(1);
	PS::timerRecursive->BeginInit();
	PS::timerRecursive->AutoReset = true;
	PS::timerRecursive->Elapsed += gcnew System::Timers::ElapsedEventHandler(this, &frmMain::timerRecursive_Tick);
	PS::timerRecursive->EndInit();
	//PS::timerRecursive->Start();


	PS::keys = gcnew KeyEventArgs(System::Windows::Forms::Keys::None);

	int i = 0;
	int j = 0;
	int t = 0;

	//for (j = 0; j < 4; j++) {
		for (i = 0; i < 5*4; i+=4) {
			
			//connectionLines.push_back(new Line);
			//connectionLines.push_back(new Line);
			//connectionLines.push_back(new Line);
			//connectionLines.push_back(new Line);

			blocks.push_back(new Input); //inpu
			blocks[t]->setPos(50 + j * 250, 50 + (i / 4) * 70);
			//blocks[t]->attachLine(connectionLines[t], -1, 1);
			//blocks[t]->attachLine(connectionLines[t + 3], -1, 1);
			

			blocks.push_back(new Input); //inpu2
			blocks[t + 1]->setPos(50 + j * 250, 90 + (i / 4) * 70);
			//blocks[t + 1]->attachLine(connectionLines[t + 1], -1, 1);

			blocks.push_back(new AND); //mygate
			blocks[t + 2]->setPos(150 + j * 250, 50 + (i / 4) * 70);
			//blocks[t + 2]->attachLine(connectionLines[t], -1, 0); //input
			//blocks[t + 2]->pinAdd();
			//blocks[t + 2]->pinAdd();
			//blocks[t + 2]->pinAdd();
			//blocks[t + 2]->pinAdd();
			//blocks[t + 2]->inputs[4]->setNegate(true);
			//blocks[t + 2]->inputs[0]->setNegate(true);
			//blocks[t + 2]->attachLine(connectionLines[t + 1], 4, 0); //input
			//blocks[t + 2]->attachLine(connectionLines[t + 2], -1, 1); //output
			//blocks[t + 2]->attachLine(connectionLines[t + 3], -1, 0);

			blocks.push_back(new AND); //mygate2
			blocks[t + 3]->setPos(220 + j * 250, 50 + (i / 4) * 70);
			//blocks[t + 3]->attachLine(connectionLines[t + 2], -1, 0);
			t += 4;
		}
		
	//}

	for (Block * b : blocks) {
		b->execute();
	}

	PS::refreshNeeded = true;

}

void frmMain::pBackground_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	pBackground->Focus();
	
	if (e->Button == System::Windows::Forms::MouseButtons::Left) {
		
		Block * b = getBlockAtPoint(e->Location);
		if (b != 0)  b->mouseDown(e->Location);

		Line * l = getLineAtPoint(e->Location);


		if (((b != 0 && b->selected) || (l != 0 && l->selected)) && !PS::simulating) {
			PS::dragMode = PS::dragType::moving;
		}else{
			PS::dragMode = PS::dragType::selecting;
		}

		PS::dragStart = e->Location;
		PS::dragCurrent = e->Location;
		

		pBackground_MouseMove(sender, e);

	} else if (e->Button == System::Windows::Forms::MouseButtons::Right) {
		
		PS::dragStartPin = getPinAtPoint(e->Location);
		if (PS::dragStartPin != 0 && !PS::simulating) {
			PS::dragStart = PS::dragStartPin->getPos();
			PS::dragStart.X += (PS::dragStartPin->isOutput() ? 10 : 0);

			PS::dragCurrent = e->Location;
			PS::dragMode = PS::dragType::line;

			pBackground_MouseMove(sender, e);
		}
	}

	PS::refreshNeeded = true;
}

void frmMain::pBackground_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	
	PS::dragCurrent = e->Location;
	
	if (PS::dragMode == PS::dragType::none) {
		if (PS::mouseOverLine != 0) {
			PS::mouseOverLine->setMouseOver(false);
		}

		PS::mouseOverLine = getLineAtPoint(PS::dragCurrent);
		if (PS::mouseOverLine != 0) {
			PS::mouseOverLine->setMouseOver(true);
		}
	} else if (PS::dragMode == PS::dragType::moving) {
		Point p = Point(PS::dragCurrent.X - PS::dragStart.X, PS::dragCurrent.Y - PS::dragStart.Y);
		p.X -= p.X % 10;
		p.Y -= p.Y % 10;

		for(Block *b: blocks){
			if(b->selected){
				b->setPosOffset(p);
			}
		}

	}

	if (PS::mouseOverPin != 0) {
		PS::mouseOverPin->setBorder(false);
		PS::mouseOverPin = 0;
		PS::TooltipVisible = false;
	}

	if (PS::dragMode == PS::dragType::line || PS::dragMode == PS::dragType::none) {
		PS::mouseOverPin = getPinAtPoint(PS::dragCurrent);
	}

	if (PS::mouseOverPin != 0) {
		
		if (PS::dragMode == PS::dragType::line) {
			if (PS::mouseOverPin == PS::dragStartPin) {
				PS::TooltipVisible = true;
				PS::TooltipMessage = "Release to Negate PIN";
			} else if (!(PS::mouseOverPin->isOutput() ^ PS::dragStartPin->isOutput())) {
				PS::TooltipVisible = true;
				PS::TooltipMessage = "PIN connection not allowed!\nOne INPUT PIN and one OUTPUT PIN!";
			} else if (!PS::mouseOverPin->isOutput() && PS::mouseOverPin->isConnected() || !PS::dragStartPin->isOutput() && PS::dragStartPin->isConnected()) {
				PS::TooltipVisible = true;
				PS::TooltipMessage = "PIN connection not allowed!\nINPUT PIN Already Connected!";
			} else {
				
				Pin * pin1 = PS::mouseOverPin;
				Pin * pin2 = PS::dragStartPin;
				Pin * pintemp;
				if (pin1->isOutput()) {
					pintemp = pin1;
					pin1 = pin2;
					pin2 = pintemp;
				}

				if(findRecursiveConnection(pin1,pin2)){
					PS::TooltipVisible = true;
					PS::TooltipMessage = "Release to create RecursiveLine";
				}else{
					PS::TooltipVisible = false;
					PS::TooltipMessage = "";
				}
			}
		}
		PS::mouseOverPin->setBorder(true);
	}
	
	PS::TooltipPos = e->Location;
	PS::refreshNeeded = true;
}


void frmMain::pBackground_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	Pin * pin1;
	Pin * pin2;
	Pin * pintemp;
	Rectangle selection;

	bool clicked = (PS::dragStart == PS::dragCurrent);
	for (Block * b : blocks) {
		b->mouseUp(e->Location);
		if (!PS::keys->Control && !PS::keys->Shift && PS::dragMode != PS::dragType::moving) {
			b->selected = false;
		}
	}


	if (e->Button == System::Windows::Forms::MouseButtons::Left) {
		

		switch (PS::dragMode){

			case PS::dragType::moving:
				for (Block * b : blocks) {
					if(b->selected){
						b->setPosCalculateOffset();
					}
				}
				break;

			case PS::dragType::selecting:
				
				for (Block * b : blocks) {

					if (getAbsoluteRectFromPoints(PS::dragStart, PS::dragCurrent, &selection)) {
						if (getIntersectionOfRects(&b->getPos(), &selection)){
							b->selected = (PS::keys->Shift ? !b->selected : true);
						}
					}else{
						if (selection.Contains(b->getPos())) {
							b->selected = (PS::keys->Shift ? !b->selected : true);
						}
					}
				}

		
				for (Line * l : connectionLines) {
					if (!PS::keys->Control && !PS::keys->Shift) {
						l->selected = false;
					}

					if (clicked) {
						if (l->isPointOnLine(PS::dragStart)) {
							l->selected = true;
						}
					}else{
						if (getAbsoluteRectFromPoints(PS::dragStart, PS::dragCurrent, &selection)) {
							if (getIntersectionOfRects(&l->getPos(), &selection)) {
								l->selected = (PS::keys->Shift ? !l->selected : true);
							}
						} else {
							if (selection.Contains(l->getPos())) {
								l->selected = (PS::keys->Shift ? !l->selected : true);
							}
						}
					}
				}
				break;
		}

	} else if (e->Button == System::Windows::Forms::MouseButtons::Right) {
		if(!PS::simulating){
			PS::dragCurrent = e->Location;

			pin1 = getPinAtPoint(PS::dragStart);
			pin2 = getPinAtPoint(PS::dragCurrent);

			//if we found the pins, connect them if we have one input and one output
			if (pin1 != 0 && pin2 != 0) {
				if (pin1->isOutput() ^ pin2->isOutput()) {
				
					if (pin2->isOutput()) {
						pintemp = pin1;
						pin1 = pin2;
						pin2 = pintemp;
					}

					if (!pin2->isConnected()) {
					
						Line * l = new Line(&addLineToQuery);
						connectionLines.push_back(l);

						pin1->attachLine(l);
						pin2->attachLine(l);

						if (findRecursiveConnection(pin2, pin1)){
							l->setRecursive(true);
						}

						//pin1->getBlock()->attachLine(l, -1, 1);
						//pin2->getBlock()->attachLine(l, -1, 0);

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
	}

	PS::dragMode = PS::dragType::none;


	frmMain::Refresh();
}


void frmMain::tcmdSimulateStart_Click(Object^  sender, EventArgs^  e) {
	if (PS::simulating) return;

	this->tcmdSimulateStart->Enabled = false;
	this->tcmdSimulateStop->Enabled = true;
	PS::simulating = true;
	PS::timerRecursive->Start();
	PS::refreshNeeded = true;
}

void frmMain::tcmdSimulateStop_Click(Object^  sender, EventArgs^  e) {
	if (!PS::simulating) return;

	this->tcmdSimulateStart->Enabled = true;
	this->tcmdSimulateStop->Enabled = false;
	PS::simulating = false;
	PS::timerRecursive->Stop();
	PS::refreshNeeded = true;
}


void frmMain::pBackground_Paint(Object^  sender, PaintEventArgs^  e) {

	Graphics ^g = e->Graphics;
	SolidBrush ^programBackground = gcnew SolidBrush(Color::FromArgb(180, 180, 180));
	Pen ^blockBorder = gcnew Pen(Color::Black);
	Brush ^grid = gcnew SolidBrush(Color::Black);

	Drawing::SolidBrush ^selectionBack;  //= gcnew Drawing::SolidBrush(Color::FromArgb(80, 0, 162, 232));
	Drawing::Pen ^selectionBorder;  //= gcnew Pen(Color::FromArgb(0, 162, 232));

	g->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::HighSpeed;
	//g->PixelOffsetMode = System::Drawing::Drawing2D::PixelOffsetMode::HighSpeed;

	//g->RenderingOrigin = Point(-50,-50);

	//paint background
	//g->FillRectangle(programBackground, frmMain::ClientRectangle);

	if(!PS::simulating){
		for(int X = 0; X < ClientRectangle.Width; X+=10){
			for (int Y = 0; Y < ClientRectangle.Height; Y += 10) {
				g->FillRectangle(grid, X, Y, 1, 1);
			}
		}
	}

	for (Block * b : blocks) {
		b->draw(g);
	}

	for (Line * l : connectionLines) {
		l->draw(g);
	}

	if (PS::dragMode == PS::dragType::line) {
		g->DrawLine(blockBorder, PS::dragStart, PS::dragCurrent);

	} else if (PS::dragMode == PS::dragType::selecting) {
		Rectangle selection;

		if (getAbsoluteRectFromPoints(PS::dragStart, PS::dragCurrent, &selection)) {
			selectionBack = gcnew Drawing::SolidBrush(Color::FromArgb(80, 0, 232, 40));
			selectionBorder = gcnew Pen(Color::FromArgb(0, 232, 40));
			selectionBorder->DashStyle = Drawing2D::DashStyle::Dash;
		}else{
			selectionBack = gcnew Drawing::SolidBrush(Color::FromArgb(80, 0, 162, 232));
			selectionBorder = gcnew Pen(Color::FromArgb(0, 162, 232));
				
		}

		g->FillRectangle(selectionBack, selection);
		g->DrawRectangle(selectionBorder, selection);
	}
	
	if (PS::TooltipVisible) {
		System::Drawing::SizeF sSize = g->MeasureString(PS::TooltipMessage, ColorStyle::fontFamily);

		Point tooltip = Point(PS::TooltipPos.X - (int)sSize.Width - 10, PS::TooltipPos.Y+15);

		if (tooltip.X < 0) {
			tooltip.X = 0;
		} else if (tooltip.X + sSize.Width + 6 > ClientRectangle.Width) {
			tooltip.X = ClientRectangle.Width - ((int)sSize.Width + 6);
		}

		//draw shadow of tooltip
		Drawing::SolidBrush ^ br = gcnew Drawing::SolidBrush(Color::FromArgb(128, 0, 0, 0));
		g->FillRectangle(br, tooltip.X + 2, tooltip.Y + 2, (int)sSize.Width + 6, (int)sSize.Height + 6);

		//draw tooltip
		g->FillRectangle(ColorStyle::brushBack, tooltip.X, tooltip.Y, (int)sSize.Width + 6, (int)sSize.Height + 6);
		g->DrawRectangle(ColorStyle::penNormal, tooltip.X, tooltip.Y, (int)sSize.Width + 6, (int)sSize.Height + 6);

		//draw text on tooltip
		g->DrawString(PS::TooltipMessage, ColorStyle::fontFamily, ColorStyle::brushNormal, tooltip.X + 3.0f, tooltip.Y + 3.0f);
	}

	//Application::DoEvents();
}

