#include "frmMain.h"

#include "AND.h"
#include "ANDR.h"
#include "ANDF.h"
#include "OR.h"
#include "RS.h"
#include "Block.h"
#include "Line.h"
#include "INPUT.h"
#include "ColorStyle.h"
#include "PS.h"
#include <algorithm>
#include "TagShifting.h"
#include <iostream>


using namespace System::Windows::Forms;
using namespace PureLogic;
using namespace System::Resources;

using namespace System::Drawing;

//Point dragStart;
//Point dragCurrent;
//Pin * dragStartPin;

//bool isDragging = false;

vector<Line *> connectionLines;
vector<Block *> blocks;
vector<Line *> recurse;

vector<Block *> drawings;



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

void frmMain::fillImageList(){
	Bitmap ^ b;
	Graphics ^ g;

	drawings.push_back(new AND);
	drawings.push_back(new OR);
	drawings.push_back(new ANDR);
	drawings.push_back(new ANDF);
	drawings.push_back(new INPUT);

	for (unsigned int i = 0; i < drawings.size(); i++){
		if (drawings[i]->type == PS::blockTypes::INPUT){
			drawings[i]->setPos(5, 5);
		}else{
			drawings[i]->setPos(5, 0);
		}

		drawings[i]->execute();

		b = gcnew Bitmap(32, 32, System::Drawing::Imaging::PixelFormat::Format32bppArgb);
		g = Graphics::FromImage(b);

		drawings[i]->draw(g);

		imgBlocksLarge->Images->Add(b);
		lstComponents->Items[i]->ImageIndex = i;
		delete b;
	}

	//IndexOfKey("AND")


}

bool findRecursiveConnection(Pin * pStart, Pin * pEnd) {
	Block * bTmp;
	Pin * pTmp;
	Pin * loopStart;

	loopStart = pStart;

	if (!pStart->isOutput()) { //is an input.
		bTmp = pStart->getBlock();
		pTmp = bTmp->output;
		if (pTmp != pEnd) {
			if (pTmp->isConnected()) {
				for (Line * l : pTmp->lines) {
					if (l->getRecursive()) return false;
					if (findRecursiveConnection(l->getInput(), pEnd)) return true;
				}
			} else {
				return false;
			}
		} else {
			return true;
		}
	}
	return false;
}

bool getIntersectionOfRects(Rectangle *r1, Rectangle *r2) {
	return (r1->X >= r2->X && r1->X <= r2->X + r2->Width || r2->X >= r1->X && r2->X <= r1->X + r1->Width) && (r1->Y >= r2->Y && r1->Y <= r2->Y + r2->Height || r2->Y >= r1->Y && r2->Y <= r1->Y + r1->Height);
}

void removeLine(Line * l) {
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
		if (connectionLines[j] != NULL && connectionLines[j]->selected) {
			if (connectionLines[j]->getRecursive()) {
				for (unsigned int k = 0; k < recurse.size(); k++) {
					if (recurse[k] != NULL){
						if (recurse[k] == connectionLines[j]) {
							recurse[k] = NULL;
						}
					}
				}
			}
			Line * l = connectionLines[j];
			delete l;
			connectionLines[j] = NULL;
		}
	}

	
	PS::mouseOverLine = NULL;
	PS::mouseOverPin = NULL;
	if (PS::dragMode != PS::dragType::line){
		PS::dragStartPin = NULL;
		PS::dragMode = PS::dragType::none;
	}

	blocks.erase(std::remove_if(blocks.begin(), blocks.end(), [](Block * bb) {return bb == NULL; }), blocks.end());
	//connectionLines.erase(std::remove(connectionLines.begin(), connectionLines.end(), static_cast<Line*>(NULL)), connectionLines.end());
	connectionLines.erase(std::remove_if(connectionLines.begin(), connectionLines.end(), [](Line * ll){return ll == NULL;}), connectionLines.end());
	recurse.erase(std::remove_if(recurse.begin(), recurse.end(), [](Line * ll) {return ll == NULL; }), recurse.end());
}

bool getAbsoluteRectFromPoints(Point ^p1, Point ^p2, Rectangle *r) {
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
		if (pinReturn != NULL) return pinReturn;
	}
	return NULL;
}

Line * getLineAtPoint(Point p) {
	for (Line * l : connectionLines) {
		if (l->isPointOnLine(p)) {
			return l;
		}
	}
	return NULL;
}

Block * getBlockAtPoint(Point p) {
	for (Block * b : blocks) {
		if (b->getPos().Contains(p)) {
			return b;
		}
	}
	return NULL;
}


unsigned long createRGB(int r, int g, int b) {
	return r + (g * 256) + (b * 256 * 256);
}

void addLineToQuery(Line * l) {
	bool found = false;
	for (Line * l1 : recurse) {
		if (l1 == l) {
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
			if (recurse[i]) {
				recurse[i]->activateRecursive();
				repeatCounter++;
			}
			recurse[i] = NULL;
		}

		recurse.erase(std::remove(recurse.begin(), recurse.end(), static_cast<Line*>(NULL)), recurse.end());

		PS::refreshNeeded = true;

		//PS::Tooltip("count: " + s);

	}
}


void frmMain::timerRefresh_Tick(Object^ state, System::Timers::ElapsedEventArgs^ e) {
	if (PS::refreshNeeded) {
		this->pBackground->Invalidate();
		PS::refreshNeeded = false;

	}
}


void frmMain::frmMain_KeyDown(Object^  sender, KeyEventArgs^ e) {
	PS::keys = e;

	if (e->Shift) lblStatusShift->Text = "Shift";
	if (e->Alt) lblStatusAlt->Text = "Alt";
	if (e->Control) lblStatusCtrl->Text = "Ctrl";

	switch (e->KeyCode) {
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
						b->setPosOffset(Point(0, 0));
					}
					PS::dragMode = PS::dragType::none;
			}
			break;
	}

	PS::refreshNeeded = true;
}

void frmMain::frmMain_KeyUp(Object^  sender, KeyEventArgs^ e) {
	PS::keys = e;

	if (!e->Shift) lblStatusShift->Text = "";
	if (!e->Alt) lblStatusAlt->Text = "";
	if (!e->Control) lblStatusCtrl->Text = "";

	if (PS::simulating) {
		switch (e->KeyCode) {
			case Keys::Enter:
				for (Block * b : blocks) {
					b->mouseUp(Point(0, 0));
				}
				break;
		}
	} else {
		switch (e->KeyCode) {

			case Keys::Delete:
				removeSelectedItems();
				break;

		}
	}

	PS::refreshNeeded = true;

}


void frmMain::frmMain_KeyPress(Object^  sender, KeyPressEventArgs^ e) {

}


void frmMain::frmMain_Unload(Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
	PS::timerRefresh->Stop();
	PS::timerRefresh->Enabled = false;
	PS::timerRefresh->Close();

	delete PS::timerRefresh;
}

void frmMain::setZoomLevel(double newZoom) {
	PS::zoom = newZoom;

	ColorStyle::fontFamily = gcnew System::Drawing::Font("Courier", (float)(9.0 * PS::zoom), System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Pixel);
	
	lblStatusAlt->Font = gcnew System::Drawing::Font("Courier New", 12.0f, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Pixel);
	lblStatusCtrl->Font = lblStatusAlt->Font;
	lblStatusShift->Font = lblStatusAlt->Font;
}

void frmMain::gridTagList_CellContentClick(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
	
}

void frmMain::gridTagList_CellEndEdit(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
	int row = e->RowIndex;
	int cell = e->ColumnIndex;
	array<System::String ^>^ strCell = gcnew array<System::String ^>(4);

	bool cellEmpty = false;

	for(int i = 0; i < 4; i++){
		if (!String::IsNullOrEmpty(gridTagList->Rows[row]->Cells[i]->FormattedValue->ToString())) {
			strCell[i] = gridTagList->Rows[row]->Cells[i]->Value->ToString();
		}else{
			if (i != 3){
				gridTagList->Rows[row]->Cells[i]->Style->BackColor = Color::FromArgb(255, 200, 200);
				cellEmpty = true;
			}
		}
	}
	if(cellEmpty) return;

	DataGridViewComboBoxCell ^ comb = reinterpret_cast<DataGridViewComboBoxCell^> (gridTagList->Rows[row]->Cells[1]);
	int addressType = comb->Items->IndexOf(comb->Value);


	//validate input of address range
	String ^ firstPart;
	String ^ secondPart;
	int addressByte;
	int addressBit;

			

	if (strCell[2]->Contains(".")) {

		firstPart = strCell[2]->Substring(0, strCell[2]->IndexOf("."));
		secondPart = strCell[2]->Substring(strCell[2]->IndexOf(".") + 1);
		if (secondPart->Length != 1){
			gridTagList->Rows[row]->ErrorText = "The bit address must be 0..7!";
			gridTagList->Rows[row]->Cells[cell]->Style->BackColor = Color::FromArgb(255, 200, 200);
			return;
		}

		if (!int::TryParse(secondPart, addressBit)) {
			gridTagList->Rows[row]->ErrorText = "The bit address must be a number!";
			gridTagList->Rows[row]->Cells[cell]->Style->BackColor = Color::FromArgb(255, 200, 200);
			return;
		}

		if (addressBit < 0 || addressBit > 7) {
			gridTagList->Rows[row]->ErrorText = "The bit address must be 0..7!";
			gridTagList->Rows[row]->Cells[cell]->Style->BackColor = Color::FromArgb(255, 200, 200);
			return;
		}

		if (!int::TryParse(firstPart, addressByte)) {
			gridTagList->Rows[row]->ErrorText = "The byte address must be a number!";
			gridTagList->Rows[row]->Cells[cell]->Style->BackColor = Color::FromArgb(255, 200, 200);
			return;
		}

		if (addressByte < 0 || addressByte > 100) {
			gridTagList->Rows[row]->ErrorText = "The byte address must be 0..100!";
			gridTagList->Rows[row]->Cells[cell]->Style->BackColor = Color::FromArgb(255, 200, 200);
			return;
		}

		if (addressType != 0) {
			gridTagList->Rows[row]->Cells[1]->Style->BackColor = Color::FromArgb(255, 200, 200);
			gridTagList->Rows[row]->Cells[2]->Style->BackColor = Color::FromArgb(255, 200, 200);

			gridTagList->Rows[row]->ErrorText = "Only datatype that can be placed on " + addressByte + "." + addressBit + " is a Bool. Try " + addressByte + " instead!";
			return;
		}


	}else{ //address is complete number
		if (!int::TryParse(strCell[2], addressByte)) {
			gridTagList->Rows[row]->ErrorText = "The byte address must be a number!";
			gridTagList->Rows[row]->Cells[cell]->Style->BackColor = Color::FromArgb(255,200,200);
			return;
		}

		if (addressByte < 0 || addressByte > 100) {
			gridTagList->Rows[row]->ErrorText = "The byte address must be 0..100!";
			gridTagList->Rows[row]->Cells[cell]->Style->BackColor = Color::FromArgb(255, 200, 200);
			return;
		}

		if (addressType == 0) {
			gridTagList->Rows[row]->Cells[1]->Style->BackColor = Color::FromArgb(255, 200, 200);
			gridTagList->Rows[row]->Cells[2]->Style->BackColor = Color::FromArgb(255, 200, 200);

			gridTagList->Rows[row]->ErrorText = "Datatype Bool cannot be placed on " + addressByte + ". Try " + +addressByte + ".0 instead!";
			return;
		}
	}

	gridTagList->Rows[row]->ErrorText = "";
	for (int i = 0; i < 4; i++) {
		gridTagList->Rows[row]->Cells[i]->Style->BackColor = Color::FromArgb(255, 255, 255);
	}

	//trigger check for all rows do not have any red backgrounds.
	//if check completed parse all the data and fill the value column.
}

void frmMain::gridTagList_KeyPress(Object^ sender, KeyPressEventArgs^ e){
	
	
}


void frmMain::frmMain_Load(System::Object^  sender, System::EventArgs^  e) {
	//MessageBox::Show("Startup test");

	//TagShifting<bool> b1;
	//TagShifting<bool> b2;

	//b1.setAdress(102);
	//b2.setAdress(12);
	//bool u1 = b1;
	//bool u2 = b2;

	//MessageBox::Show(u1.ToString());
	//MessageBox::Show(u2.ToString());

	//b1 = true;
	//u1 = b1;
	//u2 = b2;

	//MessageBox::Show(u1.ToString());
	//MessageBox::Show(u2.ToString());


	/*lol.setAdress(0);
	lol = 0;
	int ijk = 0;
	int bla = 0;

	for (bla = 0; bla <= 1; bla++) {
		lol = bla;
		for(ijk = 0; ijk < 32; ijk++){
			cout << lol.getBit(ijk);
		}
		cout << endl;
	}*/

	//lol.setBit(0,true);


 	//if(lol.getBit(1) == true){
	//	MessageBox::Show("is 10!!");
	//}
	
	//lol = lol2;

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

	//this->toolsEdit->Location = Point(3, 0);
	//this->toolsSimulate->Location = Point(159, 0);
	//this->toolsView->Location = Point(216, 0);

	this->lstComponents->Columns[0]->AutoResize(System::Windows::Forms::ColumnHeaderAutoResizeStyle::ColumnContent);

	//dpi scaling compensation calculation
	//Graphics ^g = pBackground->CreateGraphics();
	//float scaleDpi = 96.0f / g->DpiX;
	tcmbZoom->SelectedIndex = 2;
	PS::scroll.X = 0;
	PS::scroll.Y = 0;


	lblStatusAlt->Text = "";
	lblStatusCtrl->Text = "";
	lblStatusShift->Text = "";
	//delete g;

	ColorStyle::fontFormatFar = gcnew StringFormat();
	ColorStyle::fontFormatFar->LineAlignment = System::Drawing::StringAlignment::Far;

	ColorStyle::fontFormatCenter = gcnew StringFormat();
	ColorStyle::fontFormatCenter->LineAlignment = System::Drawing::StringAlignment::Center;
	ColorStyle::fontFormatCenter->Alignment = System::Drawing::StringAlignment::Center;

	PS::simulating = false;
	//PS::TooltipMessage = new string;
	//PS::TooltipMessage->assign("lawla");
	PS::TooltipHide();

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

	fillImageList();

	int i = 0;
	int j = 0;
	int t = 0;

	//for (j = 0; j < 4; j++) {
	for (i = 0; i < 5 * 4; i += 4) {

		//connectionLines.push_back(new Line);
		//connectionLines.push_back(new Line);
		//connectionLines.push_back(new Line);
		//connectionLines.push_back(new Line);

		blocks.push_back(new INPUT); //inpu
		blocks[t]->setPos(50 + j * 250, 50 + (i / 4) * 70);
		//blocks[t]->attachLine(connectionLines[t], -1, 1);
		//blocks[t]->attachLine(connectionLines[t + 3], -1, 1);


		blocks.push_back(new INPUT); //inpu2
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

		blocks.push_back(new RS); //mygate2
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


void frmMain::tcmbZoom_OnSelectedIndexChanged(System::Object^ sender, System::EventArgs^  e) {
	//int newZoom = 
	switch (tcmbZoom->SelectedIndex) {
		case 0:
			setZoomLevel(0.6);
			break;
		case 1:
			setZoomLevel(0.8);
			break;
		case 2:
			setZoomLevel(1);
			break;
		case 3:
			setZoomLevel(1.5);
			break;
		case 4:
			setZoomLevel(2);
			break;
	}

	PS::refreshNeeded = true;
}

void frmMain::pBackground_OnMouseWheel(Object^ sender, MouseEventArgs^  e) {
	if (PS::keys->Control) {
		if (e->Delta > 0) {
			if (tcmbZoom->SelectedIndex < tcmbZoom->Items->Count - 1) {
				tcmbZoom->SelectedIndex++;
			}
		} else {
			if (tcmbZoom->SelectedIndex > 0) {
				tcmbZoom->SelectedIndex--;
			}
		}
	}

}

void frmMain::pBackground_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	Point loc = Point(e->Location.X - PS::scroll.X, e->Location.Y - PS::scroll.Y);
	Block * b = NULL;
	Line * l = NULL;
	
	pBackground->Focus();


	if (e->Button == System::Windows::Forms::MouseButtons::Left) {

		l = getLineAtPoint(loc);
		b = getBlockAtPoint(loc);

		if (((b != NULL && b->selected) || (l != NULL && l->selected)) && !PS::simulating && !PS::keys->Control) {
			PS::dragMode = PS::dragType::moving;
		} else {
			PS::dragMode = PS::dragType::selecting;
		}

		PS::dragStart = e->Location;
		PS::dragCurrent = e->Location;


		pBackground_MouseMove(sender, e);

	} else if (e->Button == System::Windows::Forms::MouseButtons::Right) {
		b = getBlockAtPoint(loc);
		if (b != NULL)  b->mouseDown(e->Location);

		PS::dragStartPin = getPinAtPoint(e->Location);
		if (PS::dragStartPin != 0 && !PS::simulating) {
			PS::dragStart = PS::dragStartPin->getPos();
			PS::dragStart.X += (PS::dragStartPin->isOutput() ? int(10 * PS::zoom) : 0);

			PS::dragCurrent = e->Location;
			PS::dragMode = PS::dragType::line;

			pBackground_MouseMove(sender, e);
		} else { //we are scrolling! :D

			PS::dragStart = e->Location;
			PS::dragCurrent = e->Location;
			PS::dragMode = PS::dragType::scroll;
			PS::scrollStart = PS::scroll;

			pBackground_MouseMove(sender, e);
		}
	}

	PS::refreshNeeded = true;
}

void frmMain::pBackground_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	Point loc = Point(e->Location.X - PS::scroll.X, e->Location.Y - PS::scroll.Y);

	PS::dragCurrent = e->Location;

	if (PS::dragMode == PS::dragType::none) {
		if (PS::mouseOverLine != NULL) {
			PS::mouseOverLine->setMouseOver(false);
			PS::mouseOverLine = NULL;
		}

		PS::mouseOverLine = getLineAtPoint(PS::dragCurrent);
		if (PS::mouseOverLine != NULL) {
			PS::mouseOverLine->setMouseOver(true);
		}
	} else if (PS::dragMode == PS::dragType::moving) {
		Point p = Point(PS::dragCurrent.X - PS::dragStart.X, PS::dragCurrent.Y - PS::dragStart.Y);
		p.X -= p.X % (int)(10 * PS::zoom);
		p.Y -= p.Y % (int)(10 * PS::zoom);

		for (Block *b : blocks) {
			if (b->selected) {
				b->setPosOffset(p);
			}
		}

	} else if (PS::dragMode == PS::dragType::scroll) {
		PS::scroll = Point(PS::scrollStart.X + (PS::dragCurrent.X - PS::dragStart.X), PS::scrollStart.Y + (PS::dragCurrent.Y - PS::dragStart.Y));
	}

	if (PS::mouseOverPin != NULL) {
		PS::mouseOverPin->setBorder(false);
		PS::mouseOverPin = NULL;
		PS::TooltipHide();
	}

	if (PS::dragMode == PS::dragType::line || PS::dragMode == PS::dragType::none) {
		PS::mouseOverPin = getPinAtPoint(PS::dragCurrent);

		if (PS::mouseOverPin != 0) {

			if (PS::dragMode == PS::dragType::line) {
				if (PS::mouseOverPin == PS::dragStartPin) {
					PS::Tooltip("Release to Negate PIN", PS::tooltipType::information);
				} else if (!(PS::mouseOverPin->isOutput() ^ PS::dragStartPin->isOutput())) {
					PS::Tooltip("PIN connection not allowed!\nOne INPUT PIN and one OUTPUT PIN!", PS::tooltipType::warning);
				} else if (!PS::mouseOverPin->isOutput() && PS::mouseOverPin->isConnected() || !PS::dragStartPin->isOutput() && PS::dragStartPin->isConnected()) {
					PS::Tooltip("PIN connection not allowed!\nINPUT PIN Already Connected!", PS::tooltipType::warning);
				} else {

					Pin * pin1 = PS::mouseOverPin;
					Pin * pin2 = PS::dragStartPin;
					Pin * pintemp;
					if (pin1->isOutput()) {
						pintemp = pin1;
						pin1 = pin2;
						pin2 = pintemp;
					}

					if (findRecursiveConnection(pin1, pin2)) {
						PS::Tooltip("Release to create RecursiveLine", PS::tooltipType::information);

					} else {
						PS::TooltipHide();
					}
				}
			}
			PS::mouseOverPin->setBorder(true);
		}
	}



	PS::TooltipPos = e->Location;
	PS::refreshNeeded = true;
}


void frmMain::pBackground_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	Pin * pin1;
	Pin * pin2;
	Pin * pintemp;
	Rectangle selection;

	Point loc = Point(e->Location.X - PS::scroll.X, e->Location.Y - PS::scroll.Y);


	bool clicked = (PS::dragStart == PS::dragCurrent);


	if (e->Button == System::Windows::Forms::MouseButtons::Left) {
		for (Block * b : blocks) {
			//b->mouseUp(loc);
			if (!PS::keys->Control && !PS::keys->Shift && PS::dragMode != PS::dragType::moving) {
				b->selected = false;
			}
		}

		switch (PS::dragMode) {

			case PS::dragType::moving:
				for (Block * b : blocks) {
					if (b->selected) {
						b->setPosCalculateOffset();
					}
				}
				break;

			case PS::dragType::selecting:
				bool selectInvert = getAbsoluteRectFromPoints(PS::dragStart, PS::dragCurrent, &selection);

				for (Line * l : connectionLines) {
					if (!PS::keys->Control && !PS::keys->Shift) {
						l->selected = false;
					}

					if (clicked) {
						if (l->isPointOnLine(PS::dragStart)) {
							l->selected = (PS::keys->Control || PS::keys->Shift ? !l->selected : true);
						}
					} else {
						if (selectInvert) {
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

				selection.X -= PS::scroll.X;
				selection.Y -= PS::scroll.Y;
				for (Block * b : blocks) {

					if (clicked) {
						if (b->getPos().Contains(loc)) {
							b->selected = (PS::keys->Control || PS::keys->Shift ? !b->selected : true);
						}
					} else {
						if (selectInvert) {
							if (getIntersectionOfRects(&b->getPos(), &selection)) {
								b->selected = (PS::keys->Shift ? !b->selected : true);
							}
						} else {
							if (selection.Contains(b->getPos())) {
								b->selected = (PS::keys->Shift ? !b->selected : true);
							}
						}
					}
				}



				break;
		}

	} else if (e->Button == System::Windows::Forms::MouseButtons::Right) {

		for (Block * b : blocks) {
			if(b->type == PS::blockTypes::INPUT){
				if(PS::keys->KeyCode == Keys::Enter){
					if(!b->selected){
						b->mouseUp(loc);
					}
				}else{
					b->mouseUp(loc);
				}
			}else{
				b->mouseUp(loc);
			}
		}

		if (!PS::simulating) {
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

						if (findRecursiveConnection(pin2, pin1)) {
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

	

	for(Block * b: blocks){
		if(b->type == PS::blockTypes::RS){
			//bool tmp = b->inputs[1]->getState();
			//b->inputs[1]->setState(true);
			//b->execute();
			//b->inputs[1]->setState(false);
			//b->execute();
			b->active = false;
			b->output->setState(false);
			b->execute();
		}
	}

	//this->splitContainer1->Panel1Collapsed = !this->splitContainer1->Panel1Collapsed;
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

void frmMain::lblComponentCollapse_Click(System::Object^  sender, System::EventArgs^  e) {
	if (lblComponentCollapse->Text == "<<") {
		lblComponentCollapse->Text = ">>";
		PS::splitWindowPos = splitWindow->SplitterDistance;
		splitWindow->IsSplitterFixed = true;
		lblRotatedComponents->Visible = true;
		lblRotatedDescription->Visible = true;
		splitWindow->SplitterDistance = 30;

	} else {
		lblComponentCollapse->Text = "<<";
		splitWindow->IsSplitterFixed = false;
		lblRotatedComponents->Visible = false;
		lblRotatedDescription->Visible = false;
		splitWindow->SplitterDistance = PS::splitWindowPos;
	}
	//splitComponents
}


void frmMain::pBackground_Paint(Object^  sender, PaintEventArgs^  e) {

	Graphics ^g = e->Graphics;
	SolidBrush ^programBackground = gcnew SolidBrush(Color::FromArgb(180, 180, 180));
	Pen ^blockBorder = gcnew Pen(Color::Black);
	Brush ^grid = gcnew SolidBrush(Color::Black);

	Drawing::SolidBrush ^selectionBack;  //= gcnew Drawing::SolidBrush(Color::FromArgb(80, 0, 162, 232));
	Drawing::Pen ^selectionBorder;  //= gcnew Pen(Color::FromArgb(0, 162, 232));

	g->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::HighSpeed;
	g->TextRenderingHint = System::Drawing::Text::TextRenderingHint::SingleBitPerPixelGridFit;
	//g->PixelOffsetMode = System::Drawing::Drawing2D::PixelOffsetMode::HighSpeed;

	//g->RenderingOrigin = Point(-50,-50);

	//paint background
	//g->FillRectangle(programBackground, frmMain::ClientRectangle);

	if (!PS::simulating) {
		for (double X = 0; X < ClientRectangle.Width / PS::zoom; X += 10) {
			for (double Y = 0; Y < ClientRectangle.Height / PS::zoom; Y += 10) {
				g->FillRectangle(grid, int(X * PS::zoom) + PS::scroll.X % int(10 * PS::zoom), int(Y * PS::zoom) + PS::scroll.Y % int(10 * PS::zoom), 1, 1);
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
		} else {
			selectionBack = gcnew Drawing::SolidBrush(Color::FromArgb(80, 0, 162, 232));
			selectionBorder = gcnew Pen(Color::FromArgb(0, 162, 232));

		}

		g->FillRectangle(selectionBack, selection);
		g->DrawRectangle(selectionBorder, selection);
	}

	if (PS::TooltipVisible) {
		System::Drawing::SizeF sSize = g->MeasureString(PS::TooltipMessage, lblStatusAlt->Font);

		Rectangle tooltip = Rectangle(PS::TooltipPos.X - (int)sSize.Width - 10, PS::TooltipPos.Y + 15, (int)sSize.Width + 6 + (PS::TooltipMode != PS::tooltipType::none ? 24 : 0), (int)sSize.Height + 6);

		if (tooltip.X < 0) {
			tooltip.X = 0;
		} else if (tooltip.X + sSize.Width + 6 > ClientRectangle.Width) {
			tooltip.X = ClientRectangle.Width - ((int)sSize.Width + 6);
		}

		//draw shadow of tooltip
		Drawing::SolidBrush ^ br = gcnew Drawing::SolidBrush(Color::FromArgb(128, 0, 0, 0));
		g->FillRectangle(br, tooltip.X + 2, tooltip.Y + 2, tooltip.Width, tooltip.Height);

		//draw tooltip
		g->FillRectangle(ColorStyle::brushBack, tooltip.X, tooltip.Y, tooltip.Width, tooltip.Height);
		g->DrawRectangle(ColorStyle::penNormal, tooltip.X, tooltip.Y, tooltip.Width, tooltip.Height);

		//draw text on tooltip
		g->DrawString(PS::TooltipMessage, lblStatusAlt->Font, ColorStyle::brushNormal, tooltip.X + 3.0f + (PS::TooltipMode != PS::tooltipType::none ? 24 : 0), tooltip.Y + 3.0f);

		if (PS::TooltipMode != PS::tooltipType::none) {
			ResourceManager^ rm = gcnew ResourceManager("PureLogic.ImportantFiles", GetType()->Assembly);

			switch (PS::TooltipMode) {
				case PS::tooltipType::error:
					g->DrawImage((safe_cast<Image^>(rm->GetObject(L"Error.png"))), tooltip.X + 6.0f, tooltip.Y + tooltip.Height / 2 - 8.0f);
					break;

				case PS::tooltipType::information:
					g->DrawImage((safe_cast<Image^>(rm->GetObject(L"Info.png"))), tooltip.X + 6.0f, tooltip.Y + tooltip.Height / 2 - 8.0f);
					break;

				case PS::tooltipType::warning:
					g->DrawImage((safe_cast<Image^>(rm->GetObject(L"Warning.png"))), tooltip.X + 6.0f, tooltip.Y + tooltip.Height / 2 - 8.0f);
					break;
			}
		}
	}

	/*this creates an image for in the imagelist
	
	Bitmap ^ b = gcnew Bitmap(30,30,g);

	Graphics ^ g1 = Graphics::FromImage(b);

	g1->FillRectangle(ColorStyle::brushActive,0,0,30,30);

	imgBlocksLarge->Images[0] = b;

	*/
}

