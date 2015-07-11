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
		void frmMain_Load(Object^ sender, EventArgs^  e);
		void frmMain_Unload(Object^ sender, System::ComponentModel::CancelEventArgs^  e);
		void pBackground_Paint(Object^ sender, PaintEventArgs^  e);
		void pBackground_MouseDown(Object^ sender, MouseEventArgs^  e);
		void pBackground_MouseMove(Object^ sender, MouseEventArgs^  e);
		void pBackground_MouseUp(Object^ sender, MouseEventArgs^  e);
		void pBackground_KeyDown(Object^ sender, KeyEventArgs^ e);
		void pBackground_KeyUp(Object^ sender, KeyEventArgs^ e);
		void pBackground_KeyPress(Object^ sender, KeyPressEventArgs^ e);

		void tcmdSimulateStart_Click(Object^ sender, EventArgs^  e);
		void tcmdSimulateStop_Click(Object^ sender, EventArgs^  e);
		void timerRefresh_Tick(Object^ state, System::Timers::ElapsedEventArgs^ e);
		void timerRecursive_Tick(Object^ state, System::Timers::ElapsedEventArgs^ e);

	protected:
		~frmMain()
		{
			if (components){ delete components;	}
		}


	private: FlickerLessPanel^  pBackground;








	private: System::Windows::Forms::ToolStripContainer^  toolStripContainer1;
	private: System::Windows::Forms::StatusStrip^  sStatus;
	private: System::Windows::Forms::ToolStripStatusLabel^  lblStatusSpring;
	private: System::Windows::Forms::ToolStripStatusLabel^  lblStatusCtrl;
	private: System::Windows::Forms::ToolStripStatusLabel^  lblStatusAlt;
	private: System::Windows::Forms::ToolStripStatusLabel^  lblStatusShift;
	private: System::Windows::Forms::ToolStrip^  toolStrip1;
	private: System::Windows::Forms::ToolStripButton^  tcmdOpen;
	private: System::Windows::Forms::ToolStripButton^  tcmdSave;
	private: System::Windows::Forms::ToolStripButton^  tcmdCopy;
	private: System::Windows::Forms::ToolStripButton^  tcmdPaste;
	private: System::Windows::Forms::ToolStrip^  toolStrip2;
	private: System::Windows::Forms::ToolStripButton^  tcmdSimulateStart;
	private: System::Windows::Forms::ToolStripButton^  tcmdSimulateStop;
	private: System::Windows::Forms::SplitContainer^  splitContainer1;
	private: System::Windows::Forms::ListView^  listView1;
	private: System::Windows::Forms::ImageList^  imgBlocks;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::ComponentModel::IContainer^  components;





	protected:

	protected:

	private:


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::Windows::Forms::ListViewItem^  listViewItem1 = (gcnew System::Windows::Forms::ListViewItem(L"hoi blokjehier", 0));
			System::Windows::Forms::ListViewItem^  listViewItem2 = (gcnew System::Windows::Forms::ListViewItem(L"nog een blokje hier", 8));
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(frmMain::typeid));
			this->toolStripContainer1 = (gcnew System::Windows::Forms::ToolStripContainer());
			this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
			this->tcmdOpen = (gcnew System::Windows::Forms::ToolStripButton());
			this->tcmdSave = (gcnew System::Windows::Forms::ToolStripButton());
			this->tcmdCopy = (gcnew System::Windows::Forms::ToolStripButton());
			this->tcmdPaste = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStrip2 = (gcnew System::Windows::Forms::ToolStrip());
			this->tcmdSimulateStart = (gcnew System::Windows::Forms::ToolStripButton());
			this->tcmdSimulateStop = (gcnew System::Windows::Forms::ToolStripButton());
			this->sStatus = (gcnew System::Windows::Forms::StatusStrip());
			this->lblStatusSpring = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->lblStatusCtrl = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->lblStatusAlt = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->lblStatusShift = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			this->listView1 = (gcnew System::Windows::Forms::ListView());
			this->imgBlocks = (gcnew System::Windows::Forms::ImageList(this->components));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->pBackground = (gcnew FlickerLessPanel());
			this->toolStripContainer1->ContentPanel->SuspendLayout();
			this->toolStripContainer1->TopToolStripPanel->SuspendLayout();
			this->toolStripContainer1->SuspendLayout();
			this->toolStrip1->SuspendLayout();
			this->toolStrip2->SuspendLayout();
			this->sStatus->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->BeginInit();
			this->splitContainer1->Panel1->SuspendLayout();
			this->splitContainer1->Panel2->SuspendLayout();
			this->splitContainer1->SuspendLayout();
			this->SuspendLayout();
			// 
			// toolStripContainer1
			// 
			this->toolStripContainer1->BottomToolStripPanelVisible = false;
			// 
			// toolStripContainer1.ContentPanel
			// 
			this->toolStripContainer1->ContentPanel->Controls->Add(this->splitContainer1);
			this->toolStripContainer1->ContentPanel->Size = System::Drawing::Size(783, 460);
			this->toolStripContainer1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->toolStripContainer1->LeftToolStripPanelVisible = false;
			this->toolStripContainer1->Location = System::Drawing::Point(0, 0);
			this->toolStripContainer1->Name = L"toolStripContainer1";
			this->toolStripContainer1->RightToolStripPanelVisible = false;
			this->toolStripContainer1->Size = System::Drawing::Size(783, 485);
			this->toolStripContainer1->TabIndex = 3;
			this->toolStripContainer1->Text = L"toolStripContainer1";
			// 
			// toolStripContainer1.TopToolStripPanel
			// 
			this->toolStripContainer1->TopToolStripPanel->Controls->Add(this->toolStrip1);
			this->toolStripContainer1->TopToolStripPanel->Controls->Add(this->toolStrip2);
			this->toolStripContainer1->TopToolStripPanel->MinimumSize = System::Drawing::Size(0, 25);
			// 
			// toolStrip1
			// 
			this->toolStrip1->Dock = System::Windows::Forms::DockStyle::None;
			this->toolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->tcmdOpen, this->tcmdSave,
this->tcmdCopy, this->tcmdPaste
			});
			this->toolStrip1->LayoutStyle = System::Windows::Forms::ToolStripLayoutStyle::HorizontalStackWithOverflow;
			this->toolStrip1->Location = System::Drawing::Point(3, 0);
			this->toolStrip1->MinimumSize = System::Drawing::Size(0, 25);
			this->toolStrip1->Name = L"toolStrip1";
			this->toolStrip1->Size = System::Drawing::Size(104, 25);
			this->toolStrip1->TabIndex = 0;
			// 
			// tcmdOpen
			// 
			this->tcmdOpen->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->tcmdOpen->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tcmdOpen.Image")));
			this->tcmdOpen->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tcmdOpen->Name = L"tcmdOpen";
			this->tcmdOpen->Size = System::Drawing::Size(23, 22);
			this->tcmdOpen->Text = L"toolStripButton1";
			// 
			// tcmdSave
			// 
			this->tcmdSave->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->tcmdSave->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tcmdSave.Image")));
			this->tcmdSave->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tcmdSave->Name = L"tcmdSave";
			this->tcmdSave->Size = System::Drawing::Size(23, 22);
			this->tcmdSave->Text = L"toolStripButton1";
			// 
			// tcmdCopy
			// 
			this->tcmdCopy->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->tcmdCopy->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tcmdCopy.Image")));
			this->tcmdCopy->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tcmdCopy->Name = L"tcmdCopy";
			this->tcmdCopy->Size = System::Drawing::Size(23, 22);
			this->tcmdCopy->Text = L"toolStripButton1";
			// 
			// tcmdPaste
			// 
			this->tcmdPaste->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->tcmdPaste->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tcmdPaste.Image")));
			this->tcmdPaste->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tcmdPaste->Name = L"tcmdPaste";
			this->tcmdPaste->Size = System::Drawing::Size(23, 22);
			this->tcmdPaste->Text = L"toolStripButton1";
			// 
			// toolStrip2
			// 
			this->toolStrip2->AllowMerge = false;
			this->toolStrip2->Dock = System::Windows::Forms::DockStyle::None;
			this->toolStrip2->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->tcmdSimulateStart,
this->tcmdSimulateStop
			});
			this->toolStrip2->Location = System::Drawing::Point(107, 0);
			this->toolStrip2->MaximumSize = System::Drawing::Size(0, 30);
			this->toolStrip2->MinimumSize = System::Drawing::Size(0, 25);
			this->toolStrip2->Name = L"toolStrip2";
			this->toolStrip2->Size = System::Drawing::Size(0, 25);
			this->toolStrip2->TabIndex = 1;
			// 
			// tcmdSimulateStart
			// 
			this->tcmdSimulateStart->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->tcmdSimulateStart->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tcmdSimulateStart.Image")));
			this->tcmdSimulateStart->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tcmdSimulateStart->Name = L"tcmdSimulateStart";
			this->tcmdSimulateStart->Size = System::Drawing::Size(23, 22);
			this->tcmdSimulateStart->Text = L"toolStripButton1";
			this->tcmdSimulateStart->ToolTipText = L"Start Simulator (F2)";
			this->tcmdSimulateStart->Click += gcnew System::EventHandler(this, &frmMain::tcmdSimulateStart_Click);
			// 
			// tcmdSimulateStop
			// 
			this->tcmdSimulateStop->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->tcmdSimulateStop->Enabled = false;
			this->tcmdSimulateStop->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tcmdSimulateStop.Image")));
			this->tcmdSimulateStop->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tcmdSimulateStop->Name = L"tcmdSimulateStop";
			this->tcmdSimulateStop->Size = System::Drawing::Size(23, 22);
			this->tcmdSimulateStop->Text = L"toolStripButton1";
			this->tcmdSimulateStop->ToolTipText = L"Stop Simulator (F3)";
			this->tcmdSimulateStop->Click += gcnew System::EventHandler(this, &frmMain::tcmdSimulateStop_Click);
			// 
			// sStatus
			// 
			this->sStatus->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->lblStatusSpring, this->lblStatusCtrl,
this->lblStatusAlt, this->lblStatusShift
			});
			this->sStatus->Location = System::Drawing::Point(0, 463);
			this->sStatus->Name = L"sStatus";
			this->sStatus->Size = System::Drawing::Size(783, 22);
			this->sStatus->TabIndex = 3;
			this->sStatus->Text = L"statusStrip1";
			// 
			// lblStatusSpring
			// 
			this->lblStatusSpring->Name = L"lblStatusSpring";
			this->lblStatusSpring->Size = System::Drawing::Size(618, 17);
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
			// splitContainer1
			// 
			this->splitContainer1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer1->Location = System::Drawing::Point(0, 0);
			this->splitContainer1->Name = L"splitContainer1";
			// 
			// splitContainer1.Panel1
			// 
			this->splitContainer1->Panel1->Controls->Add(this->label2);
			this->splitContainer1->Panel1->Controls->Add(this->label1);
			this->splitContainer1->Panel1->Controls->Add(this->listView1);
			// 
			// splitContainer1.Panel2
			// 
			this->splitContainer1->Panel2->Controls->Add(this->pBackground);
			this->splitContainer1->Size = System::Drawing::Size(783, 460);
			this->splitContainer1->SplitterDistance = 161;
			this->splitContainer1->TabIndex = 3;
			// 
			// listView1
			// 
			this->listView1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
						| System::Windows::Forms::AnchorStyles::Left)
						| System::Windows::Forms::AnchorStyles::Right));
			this->listView1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ListViewItem^  >(2) { listViewItem1, listViewItem2 });
			this->listView1->LargeImageList = this->imgBlocks;
			this->listView1->Location = System::Drawing::Point(0, 22);
			this->listView1->Name = L"listView1";
			this->listView1->Size = System::Drawing::Size(161, 417);
			this->listView1->SmallImageList = this->imgBlocks;
			this->listView1->TabIndex = 0;
			this->listView1->UseCompatibleStateImageBehavior = false;
			this->listView1->View = System::Windows::Forms::View::List;
			// 
			// imgBlocks
			// 
			this->imgBlocks->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^>(resources->GetObject(L"imgBlocks.ImageStream")));
			this->imgBlocks->TransparentColor = System::Drawing::Color::Transparent;
			this->imgBlocks->Images->SetKeyName(0, L"3d bar chart.png");
			this->imgBlocks->Images->SetKeyName(1, L"Abort.png");
			this->imgBlocks->Images->SetKeyName(2, L"About.png");
			this->imgBlocks->Images->SetKeyName(3, L"Accounting.png");
			this->imgBlocks->Images->SetKeyName(4, L"Address book.png");
			this->imgBlocks->Images->SetKeyName(5, L"Alarm clock.png");
			this->imgBlocks->Images->SetKeyName(6, L"Alarm.png");
			this->imgBlocks->Images->SetKeyName(7, L"Alert.png");
			this->imgBlocks->Images->SetKeyName(8, L"Alien.png");
			this->imgBlocks->Images->SetKeyName(9, L"Anchor.png");
			this->imgBlocks->Images->SetKeyName(10, L"Application.png");
			this->imgBlocks->Images->SetKeyName(11, L"Apply.png");
			this->imgBlocks->Images->SetKeyName(12, L"Back.png");
			this->imgBlocks->Images->SetKeyName(13, L"Bad mark.png");
			this->imgBlocks->Images->SetKeyName(14, L"Bee.png");
			this->imgBlocks->Images->SetKeyName(15, L"Black bookmark.png");
			this->imgBlocks->Images->SetKeyName(16, L"Black pin.png");
			this->imgBlocks->Images->SetKeyName(17, L"Black tag.png");
			this->imgBlocks->Images->SetKeyName(18, L"Blog.png");
			this->imgBlocks->Images->SetKeyName(19, L"Blue bookmark.png");
			// 
			// label1
			// 
			this->label1->BackColor = System::Drawing::Color::RoyalBlue;
			this->label1->Dock = System::Windows::Forms::DockStyle::Top;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::Color::White;
			this->label1->Location = System::Drawing::Point(0, 0);
			this->label1->MinimumSize = System::Drawing::Size(261, 22);
			this->label1->Name = L"label1";
			this->label1->Padding = System::Windows::Forms::Padding(5, 0, 0, 0);
			this->label1->Size = System::Drawing::Size(261, 22);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Logic Components";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label2
			// 
			this->label2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label2->BackColor = System::Drawing::Color::RoyalBlue;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::Color::White;
			this->label2->Location = System::Drawing::Point(128, 0);
			this->label2->Name = L"label2";
			this->label2->Padding = System::Windows::Forms::Padding(5, 0, 0, 0);
			this->label2->Size = System::Drawing::Size(33, 22);
			this->label2->TabIndex = 2;
			this->label2->Text = L"<<";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// pBackground
			// 
			this->pBackground->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pBackground->Location = System::Drawing::Point(0, 0);
			this->pBackground->Name = L"pBackground";
			this->pBackground->Size = System::Drawing::Size(618, 460);
			this->pBackground->TabIndex = 2;
			this->pBackground->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &frmMain::pBackground_KeyUp);
			this->pBackground->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &frmMain::pBackground_KeyDown);
			this->pBackground->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &frmMain::pBackground_KeyPress);
			this->pBackground->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &frmMain::pBackground_Paint);
			this->pBackground->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &frmMain::pBackground_MouseDown);
			this->pBackground->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &frmMain::pBackground_MouseMove);
			this->pBackground->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &frmMain::pBackground_MouseUp);
			// 
			// frmMain
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Silver;
			this->ClientSize = System::Drawing::Size(783, 485);
			this->Controls->Add(this->sStatus);
			this->Controls->Add(this->toolStripContainer1);
			this->KeyPreview = true;
			this->Name = L"frmMain";
			this->Text = L"frmMain";
			this->Closing += gcnew System::ComponentModel::CancelEventHandler(this, &frmMain::frmMain_Unload);
			this->Load += gcnew System::EventHandler(this, &frmMain::frmMain_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &frmMain::pBackground_KeyDown);
			this->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &frmMain::pBackground_KeyPress);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &frmMain::pBackground_KeyUp);
			this->toolStripContainer1->ContentPanel->ResumeLayout(false);
			this->toolStripContainer1->TopToolStripPanel->ResumeLayout(false);
			this->toolStripContainer1->TopToolStripPanel->PerformLayout();
			this->toolStripContainer1->ResumeLayout(false);
			this->toolStripContainer1->PerformLayout();
			this->toolStrip1->ResumeLayout(false);
			this->toolStrip1->PerformLayout();
			this->toolStrip2->ResumeLayout(false);
			this->toolStrip2->PerformLayout();
			this->sStatus->ResumeLayout(false);
			this->sStatus->PerformLayout();
			this->splitContainer1->Panel1->ResumeLayout(false);
			this->splitContainer1->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->EndInit();
			this->splitContainer1->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

};
};
