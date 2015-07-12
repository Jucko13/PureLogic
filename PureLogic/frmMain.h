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
		private: System::Windows::Forms::ToolStrip^  toolsEdit;

	private: System::Windows::Forms::ToolStripButton^  tcmdOpen;
	private: System::Windows::Forms::ToolStripButton^  tcmdSave;
	private: System::Windows::Forms::ToolStripButton^  tcmdCopy;
	private: System::Windows::Forms::ToolStripButton^  tcmdPaste;
		private: System::Windows::Forms::ToolStrip^  toolsSimulate;

	private: System::Windows::Forms::ToolStripButton^  tcmdSimulateStart;
	private: System::Windows::Forms::ToolStripButton^  tcmdSimulateStop;
	private: System::Windows::Forms::SplitContainer^  splitContainer1;
		private: System::Windows::Forms::ListView^  lstComponents;

	private: System::Windows::Forms::ImageList^  imgBlocks;
	private: System::Windows::Forms::Label^  label1;
		private: System::Windows::Forms::Label^  lblComponentCollapse;

		private: System::Windows::Forms::ToolStripButton^  tcmdDelete;
		private: System::Windows::Forms::ColumnHeader^  columnHeader1;
		private: System::Windows::Forms::SplitContainer^  splitContainer2;
		private: System::Windows::Forms::Label^  label2;
		private: System::Windows::Forms::TextBox^  textBox1;
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
			System::Windows::Forms::ListViewItem^  listViewItem2 = (gcnew System::Windows::Forms::ListViewItem(L"nog een b", 8));
			System::Windows::Forms::ListViewItem^  listViewItem3 = (gcnew System::Windows::Forms::ListViewItem(L"a"));
			System::Windows::Forms::ListViewItem^  listViewItem4 = (gcnew System::Windows::Forms::ListViewItem(L"a"));
			System::Windows::Forms::ListViewItem^  listViewItem5 = (gcnew System::Windows::Forms::ListViewItem(L"a"));
			System::Windows::Forms::ListViewItem^  listViewItem6 = (gcnew System::Windows::Forms::ListViewItem(L"a"));
			System::Windows::Forms::ListViewItem^  listViewItem7 = (gcnew System::Windows::Forms::ListViewItem(L"a"));
			System::Windows::Forms::ListViewItem^  listViewItem8 = (gcnew System::Windows::Forms::ListViewItem(L"a", 9));
			System::Windows::Forms::ListViewItem^  listViewItem9 = (gcnew System::Windows::Forms::ListViewItem(L"a", 8));
			System::Windows::Forms::ListViewItem^  listViewItem10 = (gcnew System::Windows::Forms::ListViewItem(L"a"));
			System::Windows::Forms::ListViewItem^  listViewItem11 = (gcnew System::Windows::Forms::ListViewItem(L"a"));
			System::Windows::Forms::ListViewItem^  listViewItem12 = (gcnew System::Windows::Forms::ListViewItem(L"a"));
			System::Windows::Forms::ListViewItem^  listViewItem13 = (gcnew System::Windows::Forms::ListViewItem(L"a"));
			System::Windows::Forms::ListViewItem^  listViewItem14 = (gcnew System::Windows::Forms::ListViewItem(L"a"));
			System::Windows::Forms::ListViewItem^  listViewItem15 = (gcnew System::Windows::Forms::ListViewItem(L"a"));
			System::Windows::Forms::ListViewItem^  listViewItem16 = (gcnew System::Windows::Forms::ListViewItem(L"a"));
			System::Windows::Forms::ListViewItem^  listViewItem17 = (gcnew System::Windows::Forms::ListViewItem(L"a"));
			System::Windows::Forms::ListViewItem^  listViewItem18 = (gcnew System::Windows::Forms::ListViewItem(L"a"));
			System::Windows::Forms::ListViewItem^  listViewItem19 = (gcnew System::Windows::Forms::ListViewItem(L"a"));
			System::Windows::Forms::ListViewItem^  listViewItem20 = (gcnew System::Windows::Forms::ListViewItem(L"a"));
			System::Windows::Forms::ListViewItem^  listViewItem21 = (gcnew System::Windows::Forms::ListViewItem(L"a"));
			System::Windows::Forms::ListViewItem^  listViewItem22 = (gcnew System::Windows::Forms::ListViewItem(L"a"));
			System::Windows::Forms::ListViewItem^  listViewItem23 = (gcnew System::Windows::Forms::ListViewItem(L"a", 11));
			System::Windows::Forms::ListViewItem^  listViewItem24 = (gcnew System::Windows::Forms::ListViewItem(L"a", 10));
			System::Windows::Forms::ListViewItem^  listViewItem25 = (gcnew System::Windows::Forms::ListViewItem(L"a"));
			System::Windows::Forms::ListViewItem^  listViewItem26 = (gcnew System::Windows::Forms::ListViewItem(L"a"));
			System::Windows::Forms::ListViewItem^  listViewItem27 = (gcnew System::Windows::Forms::ListViewItem(L"a"));
			System::Windows::Forms::ListViewItem^  listViewItem28 = (gcnew System::Windows::Forms::ListViewItem(L"a"));
			System::Windows::Forms::ListViewItem^  listViewItem29 = (gcnew System::Windows::Forms::ListViewItem(L"a"));
			System::Windows::Forms::ListViewItem^  listViewItem30 = (gcnew System::Windows::Forms::ListViewItem(L"a"));
			System::Windows::Forms::ListViewItem^  listViewItem31 = (gcnew System::Windows::Forms::ListViewItem(L"a"));
			System::Windows::Forms::ListViewItem^  listViewItem32 = (gcnew System::Windows::Forms::ListViewItem(L"a"));
			System::Windows::Forms::ListViewItem^  listViewItem33 = (gcnew System::Windows::Forms::ListViewItem(L"a"));
			System::Windows::Forms::ListViewItem^  listViewItem34 = (gcnew System::Windows::Forms::ListViewItem(L"a"));
			System::Windows::Forms::ListViewItem^  listViewItem35 = (gcnew System::Windows::Forms::ListViewItem(L"a"));
			System::Windows::Forms::ListViewItem^  listViewItem36 = (gcnew System::Windows::Forms::ListViewItem(L"a"));
			System::Windows::Forms::ListViewItem^  listViewItem37 = (gcnew System::Windows::Forms::ListViewItem(L"a"));
			System::Windows::Forms::ListViewItem^  listViewItem38 = (gcnew System::Windows::Forms::ListViewItem(L"a"));
			System::Windows::Forms::ListViewItem^  listViewItem39 = (gcnew System::Windows::Forms::ListViewItem(L"a", 19));
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(frmMain::typeid));
			this->toolStripContainer1 = (gcnew System::Windows::Forms::ToolStripContainer());
			this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			this->lblComponentCollapse = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->lstComponents = (gcnew System::Windows::Forms::ListView());
			this->columnHeader1 = (gcnew System::Windows::Forms::ColumnHeader());
			this->imgBlocks = (gcnew System::Windows::Forms::ImageList(this->components));
			this->toolsEdit = (gcnew System::Windows::Forms::ToolStrip());
			this->tcmdOpen = (gcnew System::Windows::Forms::ToolStripButton());
			this->tcmdSave = (gcnew System::Windows::Forms::ToolStripButton());
			this->tcmdCopy = (gcnew System::Windows::Forms::ToolStripButton());
			this->tcmdPaste = (gcnew System::Windows::Forms::ToolStripButton());
			this->tcmdDelete = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolsSimulate = (gcnew System::Windows::Forms::ToolStrip());
			this->tcmdSimulateStart = (gcnew System::Windows::Forms::ToolStripButton());
			this->tcmdSimulateStop = (gcnew System::Windows::Forms::ToolStripButton());
			this->sStatus = (gcnew System::Windows::Forms::StatusStrip());
			this->lblStatusSpring = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->lblStatusCtrl = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->lblStatusAlt = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->lblStatusShift = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->splitContainer2 = (gcnew System::Windows::Forms::SplitContainer());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->pBackground = (gcnew FlickerLessPanel());
			this->toolStripContainer1->ContentPanel->SuspendLayout();
			this->toolStripContainer1->TopToolStripPanel->SuspendLayout();
			this->toolStripContainer1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->BeginInit();
			this->splitContainer1->Panel1->SuspendLayout();
			this->splitContainer1->Panel2->SuspendLayout();
			this->splitContainer1->SuspendLayout();
			this->toolsEdit->SuspendLayout();
			this->toolsSimulate->SuspendLayout();
			this->sStatus->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer2))->BeginInit();
			this->splitContainer2->Panel1->SuspendLayout();
			this->splitContainer2->Panel2->SuspendLayout();
			this->splitContainer2->SuspendLayout();
			this->SuspendLayout();
			// 
			// toolStripContainer1
			// 
			this->toolStripContainer1->BottomToolStripPanelVisible = false;
			// 
			// toolStripContainer1.ContentPanel
			// 
			this->toolStripContainer1->ContentPanel->Controls->Add(this->splitContainer1);
			this->toolStripContainer1->ContentPanel->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->toolStripContainer1->ContentPanel->Size = System::Drawing::Size(1174, 721);
			this->toolStripContainer1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->toolStripContainer1->LeftToolStripPanelVisible = false;
			this->toolStripContainer1->Location = System::Drawing::Point(0, 0);
			this->toolStripContainer1->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->toolStripContainer1->Name = L"toolStripContainer1";
			this->toolStripContainer1->RightToolStripPanelVisible = false;
			this->toolStripContainer1->Size = System::Drawing::Size(1174, 746);
			this->toolStripContainer1->TabIndex = 3;
			this->toolStripContainer1->Text = L"toolStripContainer1";
			// 
			// toolStripContainer1.TopToolStripPanel
			// 
			this->toolStripContainer1->TopToolStripPanel->Controls->Add(this->toolsEdit);
			this->toolStripContainer1->TopToolStripPanel->Controls->Add(this->toolsSimulate);
			// 
			// splitContainer1
			// 
			this->splitContainer1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->splitContainer1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer1->Location = System::Drawing::Point(0, 0);
			this->splitContainer1->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->splitContainer1->Name = L"splitContainer1";
			// 
			// splitContainer1.Panel1
			// 
			this->splitContainer1->Panel1->Controls->Add(this->splitContainer2);
			// 
			// splitContainer1.Panel2
			// 
			this->splitContainer1->Panel2->Controls->Add(this->pBackground);
			this->splitContainer1->Size = System::Drawing::Size(1174, 721);
			this->splitContainer1->SplitterDistance = 187;
			this->splitContainer1->SplitterWidth = 6;
			this->splitContainer1->TabIndex = 3;
			// 
			// lblComponentCollapse
			// 
			this->lblComponentCollapse->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->lblComponentCollapse->BackColor = System::Drawing::Color::RoyalBlue;
			this->lblComponentCollapse->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblComponentCollapse->ForeColor = System::Drawing::Color::White;
			this->lblComponentCollapse->Location = System::Drawing::Point(140, 0);
			this->lblComponentCollapse->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lblComponentCollapse->Name = L"lblComponentCollapse";
			this->lblComponentCollapse->Padding = System::Windows::Forms::Padding(8, 0, 0, 0);
			this->lblComponentCollapse->Size = System::Drawing::Size(47, 34);
			this->lblComponentCollapse->TabIndex = 2;
			this->lblComponentCollapse->Text = L"<<";
			this->lblComponentCollapse->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label1
			// 
			this->label1->BackColor = System::Drawing::Color::RoyalBlue;
			this->label1->Dock = System::Windows::Forms::DockStyle::Top;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Pixel));
			this->label1->ForeColor = System::Drawing::Color::White;
			this->label1->Location = System::Drawing::Point(0, 0);
			this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label1->MinimumSize = System::Drawing::Size(392, 34);
			this->label1->Name = L"label1";
			this->label1->Padding = System::Windows::Forms::Padding(8, 0, 0, 0);
			this->label1->Size = System::Drawing::Size(392, 34);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Logic Components";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->label1->UseCompatibleTextRendering = true;
			// 
			// lstComponents
			// 
			this->lstComponents->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
						| System::Windows::Forms::AnchorStyles::Left)
						| System::Windows::Forms::AnchorStyles::Right));
			this->lstComponents->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->lstComponents->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(1) { this->columnHeader1 });
			this->lstComponents->FullRowSelect = true;
			this->lstComponents->GridLines = true;
			this->lstComponents->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::None;
			listViewItem1->StateImageIndex = 0;
			this->lstComponents->Items->AddRange(gcnew cli::array< System::Windows::Forms::ListViewItem^  >(39) {
				listViewItem1, listViewItem2,
listViewItem3, listViewItem4, listViewItem5, listViewItem6, listViewItem7, listViewItem8, listViewItem9, listViewItem10, listViewItem11,
listViewItem12, listViewItem13, listViewItem14, listViewItem15, listViewItem16, listViewItem17, listViewItem18, listViewItem19,
listViewItem20, listViewItem21, listViewItem22, listViewItem23, listViewItem24, listViewItem25, listViewItem26, listViewItem27,
listViewItem28, listViewItem29, listViewItem30, listViewItem31, listViewItem32, listViewItem33, listViewItem34, listViewItem35,
listViewItem36, listViewItem37, listViewItem38, listViewItem39
			});
			this->lstComponents->LabelWrap = false;
			this->lstComponents->LargeImageList = this->imgBlocks;
			this->lstComponents->Location = System::Drawing::Point(0, 34);
			this->lstComponents->Margin = System::Windows::Forms::Padding(0);
			this->lstComponents->Name = L"lstComponents";
			this->lstComponents->Size = System::Drawing::Size(187, 466);
			this->lstComponents->SmallImageList = this->imgBlocks;
			this->lstComponents->TabIndex = 0;
			this->lstComponents->UseCompatibleStateImageBehavior = false;
			this->lstComponents->View = System::Windows::Forms::View::Details;
			// 
			// columnHeader1
			// 
			this->columnHeader1->Width = 152;
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
			// toolsEdit
			// 
			this->toolsEdit->Dock = System::Windows::Forms::DockStyle::None;
			this->toolsEdit->ImageScalingSize = System::Drawing::Size(24, 24);
			this->toolsEdit->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->tcmdOpen, this->tcmdSave,
this->tcmdCopy, this->tcmdPaste, this->tcmdDelete
			});
			this->toolsEdit->LayoutStyle = System::Windows::Forms::ToolStripLayoutStyle::HorizontalStackWithOverflow;
			this->toolsEdit->Location = System::Drawing::Point(3, 0);
			this->toolsEdit->Name = L"toolsEdit";
			this->toolsEdit->Size = System::Drawing::Size(127, 25);
			this->toolsEdit->TabIndex = 0;
			// 
			// tcmdOpen
			// 
			this->tcmdOpen->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->tcmdOpen->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tcmdOpen.Image")));
			this->tcmdOpen->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
			this->tcmdOpen->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tcmdOpen->Name = L"tcmdOpen";
			this->tcmdOpen->Size = System::Drawing::Size(23, 22);
			this->tcmdOpen->Text = L"toolStripButton1";
			// 
			// tcmdSave
			// 
			this->tcmdSave->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->tcmdSave->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tcmdSave.Image")));
			this->tcmdSave->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
			this->tcmdSave->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tcmdSave->Name = L"tcmdSave";
			this->tcmdSave->Size = System::Drawing::Size(23, 22);
			this->tcmdSave->Text = L"toolStripButton1";
			// 
			// tcmdCopy
			// 
			this->tcmdCopy->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->tcmdCopy->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tcmdCopy.Image")));
			this->tcmdCopy->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
			this->tcmdCopy->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tcmdCopy->Name = L"tcmdCopy";
			this->tcmdCopy->Size = System::Drawing::Size(23, 22);
			this->tcmdCopy->Text = L"toolStripButton1";
			// 
			// tcmdPaste
			// 
			this->tcmdPaste->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->tcmdPaste->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tcmdPaste.Image")));
			this->tcmdPaste->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
			this->tcmdPaste->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tcmdPaste->Name = L"tcmdPaste";
			this->tcmdPaste->Size = System::Drawing::Size(23, 22);
			this->tcmdPaste->Text = L"toolStripButton1";
			// 
			// tcmdDelete
			// 
			this->tcmdDelete->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->tcmdDelete->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tcmdDelete.Image")));
			this->tcmdDelete->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
			this->tcmdDelete->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tcmdDelete->Name = L"tcmdDelete";
			this->tcmdDelete->Size = System::Drawing::Size(23, 22);
			this->tcmdDelete->Text = L"toolStripButton1";
			this->tcmdDelete->ToolTipText = L"Delete  Selected Items (Del)";
			// 
			// toolsSimulate
			// 
			this->toolsSimulate->AllowMerge = false;
			this->toolsSimulate->Dock = System::Windows::Forms::DockStyle::None;
			this->toolsSimulate->ImageScalingSize = System::Drawing::Size(24, 24);
			this->toolsSimulate->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->tcmdSimulateStart,
this->tcmdSimulateStop
			});
			this->toolsSimulate->Location = System::Drawing::Point(130, 0);
			this->toolsSimulate->Name = L"toolsSimulate";
			this->toolsSimulate->Size = System::Drawing::Size(58, 25);
			this->toolsSimulate->TabIndex = 1;
			// 
			// tcmdSimulateStart
			// 
			this->tcmdSimulateStart->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->tcmdSimulateStart->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tcmdSimulateStart.Image")));
			this->tcmdSimulateStart->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
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
			this->tcmdSimulateStop->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
			this->tcmdSimulateStop->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tcmdSimulateStop->Name = L"tcmdSimulateStop";
			this->tcmdSimulateStop->Size = System::Drawing::Size(23, 22);
			this->tcmdSimulateStop->Text = L"toolStripButton1";
			this->tcmdSimulateStop->ToolTipText = L"Stop Simulator (F3)";
			this->tcmdSimulateStop->Click += gcnew System::EventHandler(this, &frmMain::tcmdSimulateStop_Click);
			// 
			// sStatus
			// 
			this->sStatus->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->sStatus->ImageScalingSize = System::Drawing::Size(24, 24);
			this->sStatus->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->lblStatusSpring, this->lblStatusCtrl,
this->lblStatusAlt, this->lblStatusShift
			});
			this->sStatus->Location = System::Drawing::Point(0, 718);
			this->sStatus->Name = L"sStatus";
			this->sStatus->Padding = System::Windows::Forms::Padding(2, 0, 21, 0);
			this->sStatus->Size = System::Drawing::Size(1174, 28);
			this->sStatus->TabIndex = 3;
			this->sStatus->Text = L"statusStrip1";
			// 
			// lblStatusSpring
			// 
			this->lblStatusSpring->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->lblStatusSpring->Name = L"lblStatusSpring";
			this->lblStatusSpring->Size = System::Drawing::Size(946, 23);
			this->lblStatusSpring->Spring = true;
			// 
			// lblStatusCtrl
			// 
			this->lblStatusCtrl->AutoSize = false;
			this->lblStatusCtrl->BackColor = System::Drawing::Color::Silver;
			this->lblStatusCtrl->Margin = System::Windows::Forms::Padding(3, 3, 0, 2);
			this->lblStatusCtrl->Name = L"lblStatusCtrl";
			this->lblStatusCtrl->Size = System::Drawing::Size(50, 23);
			this->lblStatusCtrl->Text = L"Ctrl";
			// 
			// lblStatusAlt
			// 
			this->lblStatusAlt->AutoSize = false;
			this->lblStatusAlt->BackColor = System::Drawing::Color::Silver;
			this->lblStatusAlt->Margin = System::Windows::Forms::Padding(3, 3, 0, 2);
			this->lblStatusAlt->Name = L"lblStatusAlt";
			this->lblStatusAlt->Size = System::Drawing::Size(50, 23);
			this->lblStatusAlt->Text = L"Alt";
			// 
			// lblStatusShift
			// 
			this->lblStatusShift->AutoSize = false;
			this->lblStatusShift->BackColor = System::Drawing::Color::Silver;
			this->lblStatusShift->Margin = System::Windows::Forms::Padding(3, 3, 0, 2);
			this->lblStatusShift->Name = L"lblStatusShift";
			this->lblStatusShift->Size = System::Drawing::Size(50, 23);
			this->lblStatusShift->Text = L"Shift";
			// 
			// splitContainer2
			// 
			this->splitContainer2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer2->Location = System::Drawing::Point(0, 0);
			this->splitContainer2->Name = L"splitContainer2";
			this->splitContainer2->Orientation = System::Windows::Forms::Orientation::Horizontal;
			// 
			// splitContainer2.Panel1
			// 
			this->splitContainer2->Panel1->Controls->Add(this->lblComponentCollapse);
			this->splitContainer2->Panel1->Controls->Add(this->lstComponents);
			this->splitContainer2->Panel1->Controls->Add(this->label1);
			// 
			// splitContainer2.Panel2
			// 
			this->splitContainer2->Panel2->Controls->Add(this->textBox1);
			this->splitContainer2->Panel2->Controls->Add(this->label2);
			this->splitContainer2->Size = System::Drawing::Size(187, 721);
			this->splitContainer2->SplitterDistance = 500;
			this->splitContainer2->TabIndex = 3;
			// 
			// label2
			// 
			this->label2->BackColor = System::Drawing::Color::RoyalBlue;
			this->label2->Dock = System::Windows::Forms::DockStyle::Top;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Pixel));
			this->label2->ForeColor = System::Drawing::Color::White;
			this->label2->Location = System::Drawing::Point(0, 0);
			this->label2->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label2->MinimumSize = System::Drawing::Size(392, 34);
			this->label2->Name = L"label2";
			this->label2->Padding = System::Windows::Forms::Padding(8, 0, 0, 0);
			this->label2->Size = System::Drawing::Size(392, 34);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Description";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->label2->UseCompatibleTextRendering = true;
			// 
			// textBox1
			// 
			this->textBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
						| System::Windows::Forms::AnchorStyles::Left)
						| System::Windows::Forms::AnchorStyles::Right));
			this->textBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox1->Location = System::Drawing::Point(0, 33);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(187, 158);
			this->textBox1->TabIndex = 3;
			// 
			// pBackground
			// 
			this->pBackground->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pBackground->Location = System::Drawing::Point(0, 0);
			this->pBackground->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->pBackground->Name = L"pBackground";
			this->pBackground->Size = System::Drawing::Size(981, 721);
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
			this->BackColor = System::Drawing::Color::Silver;
			this->ClientSize = System::Drawing::Size(1174, 746);
			this->Controls->Add(this->sStatus);
			this->Controls->Add(this->toolStripContainer1);
			this->KeyPreview = true;
			this->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
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
			this->splitContainer1->Panel1->ResumeLayout(false);
			this->splitContainer1->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->EndInit();
			this->splitContainer1->ResumeLayout(false);
			this->toolsEdit->ResumeLayout(false);
			this->toolsEdit->PerformLayout();
			this->toolsSimulate->ResumeLayout(false);
			this->toolsSimulate->PerformLayout();
			this->sStatus->ResumeLayout(false);
			this->sStatus->PerformLayout();
			this->splitContainer2->Panel1->ResumeLayout(false);
			this->splitContainer2->Panel2->ResumeLayout(false);
			this->splitContainer2->Panel2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer2))->EndInit();
			this->splitContainer2->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

};
};
