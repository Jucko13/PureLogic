#pragma once

#include "flickerlesspanel.h"

namespace PureLogic {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	

	/// <summary>
	/// Summary for frmMain
	/// </summary>
	public ref class frmMain : public System::Windows::Forms::Form
	{
	public:
		frmMain(void){ InitializeComponent(); }
		void frmMain_Load(Object^  sender, EventArgs^  e);
		void frmMain_Unload(Object^  sender, System::ComponentModel::CancelEventArgs^  e);
		void pBackground_Paint(Object^  sender, PaintEventArgs^  e);
		void pBackground_MouseDown(Object^  sender, MouseEventArgs^  e);
		void pBackground_MouseMove(Object^  sender, MouseEventArgs^  e);
		void pBackground_MouseUp(Object^  sender, MouseEventArgs^  e);
		void pBackground_KeyDown(Object^  sender, KeyEventArgs^ e);
		void pBackground_KeyUp(Object^  sender, KeyEventArgs^ e);
		void pBackground_KeyPress(Object^  sender, KeyPressEventArgs^ e);

		void cmdAdd_Click(Object^  sender, EventArgs^  e);
		void cmdRemove_Click(Object^  sender, EventArgs^  e);
		void timerRefresh_Tick(Object^ state, System::Timers::ElapsedEventArgs^ e);

	protected:
		~frmMain()
		{
			if (components){ delete components;	}
		}
	private: System::Windows::Forms::Button^  cmdAdd;
	private: System::Windows::Forms::Button^  cmdRemove;
	private: FlickerLessPanel^  pBackground;
	private: System::Windows::Forms::StatusStrip^  sStatus;



	private: System::Windows::Forms::ToolStripStatusLabel^  lblStatusCtrl;
	private: System::Windows::Forms::ToolStripStatusLabel^  lblStatusAlt;
	private: System::Windows::Forms::ToolStripStatusLabel^  lblStatusShift;
	private: System::Windows::Forms::ToolStripStatusLabel^  lblStatusSpring;





	protected:

	protected:

	private:
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->pBackground = (gcnew FlickerLessPanel());
			this->cmdAdd = (gcnew System::Windows::Forms::Button());
			this->cmdRemove = (gcnew System::Windows::Forms::Button());
			this->sStatus = (gcnew System::Windows::Forms::StatusStrip());
			this->lblStatusSpring = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->lblStatusCtrl = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->lblStatusAlt = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->lblStatusShift = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->pBackground->SuspendLayout();
			this->sStatus->SuspendLayout();
			this->SuspendLayout();
			// 
			// pBackground
			// 
			this->pBackground->Controls->Add(this->cmdAdd);
			this->pBackground->Controls->Add(this->cmdRemove);
			this->pBackground->Controls->Add(this->sStatus);
			this->pBackground->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pBackground->Location = System::Drawing::Point(0, 0);
			this->pBackground->Name = L"pBackground";
			this->pBackground->Size = System::Drawing::Size(660, 485);
			this->pBackground->TabIndex = 2;
			this->pBackground->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &frmMain::pBackground_KeyUp);
			this->pBackground->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &frmMain::pBackground_KeyDown);
			this->pBackground->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &frmMain::pBackground_KeyPress);
			this->pBackground->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &frmMain::pBackground_Paint);
			this->pBackground->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &frmMain::pBackground_MouseDown);
			this->pBackground->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &frmMain::pBackground_MouseMove);
			this->pBackground->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &frmMain::pBackground_MouseUp);
			// 
			// cmdAdd
			// 
			this->cmdAdd->Location = System::Drawing::Point(171, 12);
			this->cmdAdd->Name = L"cmdAdd";
			this->cmdAdd->Size = System::Drawing::Size(153, 24);
			this->cmdAdd->TabIndex = 0;
			this->cmdAdd->Text = L"Set SimulationMode";
			this->cmdAdd->UseVisualStyleBackColor = true;
			this->cmdAdd->Click += gcnew System::EventHandler(this, &frmMain::cmdAdd_Click);
			// 
			// cmdRemove
			// 
			this->cmdRemove->Location = System::Drawing::Point(12, 12);
			this->cmdRemove->Name = L"cmdRemove";
			this->cmdRemove->Size = System::Drawing::Size(153, 24);
			this->cmdRemove->TabIndex = 1;
			this->cmdRemove->Text = L"Remove Input";
			this->cmdRemove->UseVisualStyleBackColor = true;
			this->cmdRemove->Click += gcnew System::EventHandler(this, &frmMain::cmdRemove_Click);
			// 
			// sStatus
			// 
			this->sStatus->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->lblStatusSpring, this->lblStatusCtrl,
this->lblStatusAlt, this->lblStatusShift
			});
			this->sStatus->Location = System::Drawing::Point(0, 463);
			this->sStatus->Name = L"sStatus";
			this->sStatus->Size = System::Drawing::Size(660, 22);
			this->sStatus->TabIndex = 0;
			this->sStatus->Text = L"statusStrip1";
			// 
			// lblStatusSpring
			// 
			this->lblStatusSpring->Name = L"lblStatusSpring";
			this->lblStatusSpring->Size = System::Drawing::Size(495, 17);
			this->lblStatusSpring->Spring = true;
			// 
			// lblStatusCtrl
			// 
			this->lblStatusCtrl->AutoSize = false;
			this->lblStatusCtrl->Name = L"lblStatusCtrl";
			this->lblStatusCtrl->Size = System::Drawing::Size(50, 17);
			this->lblStatusCtrl->Text = L"Ctrl";
			// 
			// lblStatusAlt
			// 
			this->lblStatusAlt->AutoSize = false;
			this->lblStatusAlt->Name = L"lblStatusAlt";
			this->lblStatusAlt->Size = System::Drawing::Size(50, 17);
			this->lblStatusAlt->Text = L"Alt";
			// 
			// lblStatusShift
			// 
			this->lblStatusShift->AutoSize = false;
			this->lblStatusShift->Name = L"lblStatusShift";
			this->lblStatusShift->Size = System::Drawing::Size(50, 17);
			this->lblStatusShift->Text = L"Shift";
			// 
			// frmMain
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Silver;
			this->ClientSize = System::Drawing::Size(660, 485);
			this->Controls->Add(this->pBackground);
			this->Name = L"frmMain";
			this->Text = L"frmMain";
			this->Closing += gcnew System::ComponentModel::CancelEventHandler(this, &frmMain::frmMain_Unload);
			this->Load += gcnew System::EventHandler(this, &frmMain::frmMain_Load);
			this->pBackground->ResumeLayout(false);
			this->pBackground->PerformLayout();
			this->sStatus->ResumeLayout(false);
			this->sStatus->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

};
};
