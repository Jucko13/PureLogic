#pragma once

#include "flickerlesspanel.h"
#include "RotationLabel.h"

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
		void pBackground_OnMouseWheel(Object^ sender, MouseEventArgs^  e);
		
		void frmMain_KeyDown(Object^ sender, KeyEventArgs^ e);
		void frmMain_KeyUp(Object^ sender, KeyEventArgs^ e);
		void frmMain_KeyPress(Object^ sender, KeyPressEventArgs^ e);

		void lblComponentCollapse_Click(System::Object^  sender, System::EventArgs^  e);

		void tcmdSimulateStart_Click(Object^ sender, EventArgs^  e);
		void tcmdSimulateStop_Click(Object^ sender, EventArgs^  e);
		void timerRefresh_Tick(Object^ state, System::Timers::ElapsedEventArgs^ e);
		void timerRecursive_Tick(Object^ state, System::Timers::ElapsedEventArgs^ e);
		void tcmbZoom_OnSelectedIndexChanged(Object^ sender, EventArgs^  e);
		void setZoomLevel(double newZoom);
		void fillImageList();


	protected:
		~frmMain()
		{
			if (components){ delete components;	}
		}


	private: 
		FlickerLessPanel^  pBackground;

		System::Windows::Forms::ToolStripContainer^  toolStripContainer1;
		System::Windows::Forms::StatusStrip^  sStatus;
		System::Windows::Forms::ToolStripStatusLabel^  lblStatusSpring;
		System::Windows::Forms::ToolStripStatusLabel^  lblStatusCtrl;
		System::Windows::Forms::ToolStripStatusLabel^  lblStatusAlt;
		System::Windows::Forms::ToolStripStatusLabel^  lblStatusShift;
		System::Windows::Forms::ToolStrip^  toolsEdit;

		System::Windows::Forms::ToolStripButton^  tcmdOpen;
		System::Windows::Forms::ToolStripButton^  tcmdSave;
		System::Windows::Forms::ToolStripButton^  tcmdCopy;
		System::Windows::Forms::ToolStripButton^  tcmdPaste;
		System::Windows::Forms::ToolStrip^  toolsSimulate;

		System::Windows::Forms::ToolStripButton^  tcmdSimulateStart;
		System::Windows::Forms::ToolStripButton^  tcmdSimulateStop;
		System::Windows::Forms::SplitContainer^  splitWindow;

		System::Windows::Forms::ListView^  lstComponents;
		System::Windows::Forms::ImageList^  imgBlocksSmall;


		System::Windows::Forms::Label^  label1;
		System::Windows::Forms::Label^  lblComponentCollapse;

		System::Windows::Forms::ToolStripButton^  tcmdDelete;
		System::Windows::Forms::ColumnHeader^  columnHeader1;
		System::Windows::Forms::SplitContainer^  splitComponents;


		System::Windows::Forms::Label^  label2;
		System::Windows::Forms::TextBox^  textBox1;
		System::Windows::Forms::ToolStrip^  toolsView;
		System::Windows::Forms::ToolStripLabel^  tlblZoom;
		System::Windows::Forms::ToolStripComboBox^  tcmbZoom;
		RotationLabel^  lblRotatedComponents;
		RotationLabel^  lblRotatedDescription;
		System::Windows::Forms::ToolStripButton^  tcmdCut;
		System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
		System::Windows::Forms::ImageList^  imgBlocksLarge;


		System::ComponentModel::IContainer^  components;



#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::Windows::Forms::ListViewGroup^  listViewGroup1 = (gcnew System::Windows::Forms::ListViewGroup(L"Logic Gates", System::Windows::Forms::HorizontalAlignment::Center));
			System::Windows::Forms::ListViewGroup^  listViewGroup2 = (gcnew System::Windows::Forms::ListViewGroup(L"Timers", System::Windows::Forms::HorizontalAlignment::Center));
			System::Windows::Forms::ListViewGroup^  listViewGroup3 = (gcnew System::Windows::Forms::ListViewGroup(L"Counters", System::Windows::Forms::HorizontalAlignment::Left));
			System::Windows::Forms::ListViewGroup^  listViewGroup4 = (gcnew System::Windows::Forms::ListViewGroup(L"Special Components", System::Windows::Forms::HorizontalAlignment::Left));
			System::Windows::Forms::ListViewItem^  listViewItem1 = (gcnew System::Windows::Forms::ListViewItem(L"AND"));
			System::Windows::Forms::ListViewItem^  listViewItem2 = (gcnew System::Windows::Forms::ListViewItem(L"OR"));
			System::Windows::Forms::ListViewItem^  listViewItem3 = (gcnew System::Windows::Forms::ListViewItem(L"AND Rising Edge"));
			System::Windows::Forms::ListViewItem^  listViewItem4 = (gcnew System::Windows::Forms::ListViewItem(L"AND Faling Edge"));
			System::Windows::Forms::ListViewItem^  listViewItem5 = (gcnew System::Windows::Forms::ListViewItem(L"INPUT"));
			System::Windows::Forms::ListViewItem^  listViewItem6 = (gcnew System::Windows::Forms::ListViewItem(L"ON Timer"));
			System::Windows::Forms::ListViewItem^  listViewItem7 = (gcnew System::Windows::Forms::ListViewItem(L"OFF Timer"));
			System::Windows::Forms::ListViewItem^  listViewItem8 = (gcnew System::Windows::Forms::ListViewItem(L"Retentive ON Timer"));
			System::Windows::Forms::ListViewItem^  listViewItem9 = (gcnew System::Windows::Forms::ListViewItem(L"UP Counter"));
			System::Windows::Forms::ListViewItem^  listViewItem10 = (gcnew System::Windows::Forms::ListViewItem(L"DOWN Counter"));
			System::Windows::Forms::ListViewItem^  listViewItem11 = (gcnew System::Windows::Forms::ListViewItem(L"Tag From TagList"));
			System::Windows::Forms::ListViewItem^  listViewItem12 = (gcnew System::Windows::Forms::ListViewItem(L"Tag Output (=, R, S)"));
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(frmMain::typeid));
			this->toolStripContainer1 = (gcnew System::Windows::Forms::ToolStripContainer());
			this->splitWindow = (gcnew System::Windows::Forms::SplitContainer());
			this->splitComponents = (gcnew System::Windows::Forms::SplitContainer());
			this->lblComponentCollapse = (gcnew System::Windows::Forms::Label());
			this->lblRotatedComponents = (gcnew RotationLabel());
			this->lstComponents = (gcnew System::Windows::Forms::ListView());
			this->columnHeader1 = (gcnew System::Windows::Forms::ColumnHeader());
			this->imgBlocksLarge = (gcnew System::Windows::Forms::ImageList(this->components));
			this->imgBlocksSmall = (gcnew System::Windows::Forms::ImageList(this->components));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->lblRotatedDescription = (gcnew RotationLabel());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->pBackground = (gcnew FlickerLessPanel());
			this->toolsEdit = (gcnew System::Windows::Forms::ToolStrip());
			this->tcmdOpen = (gcnew System::Windows::Forms::ToolStripButton());
			this->tcmdSave = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->tcmdCopy = (gcnew System::Windows::Forms::ToolStripButton());
			this->tcmdCut = (gcnew System::Windows::Forms::ToolStripButton());
			this->tcmdPaste = (gcnew System::Windows::Forms::ToolStripButton());
			this->tcmdDelete = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolsSimulate = (gcnew System::Windows::Forms::ToolStrip());
			this->tcmdSimulateStart = (gcnew System::Windows::Forms::ToolStripButton());
			this->tcmdSimulateStop = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolsView = (gcnew System::Windows::Forms::ToolStrip());
			this->tlblZoom = (gcnew System::Windows::Forms::ToolStripLabel());
			this->tcmbZoom = (gcnew System::Windows::Forms::ToolStripComboBox());
			this->sStatus = (gcnew System::Windows::Forms::StatusStrip());
			this->lblStatusSpring = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->lblStatusCtrl = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->lblStatusAlt = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->lblStatusShift = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripContainer1->ContentPanel->SuspendLayout();
			this->toolStripContainer1->TopToolStripPanel->SuspendLayout();
			this->toolStripContainer1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitWindow))->BeginInit();
			this->splitWindow->Panel1->SuspendLayout();
			this->splitWindow->Panel2->SuspendLayout();
			this->splitWindow->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitComponents))->BeginInit();
			this->splitComponents->Panel1->SuspendLayout();
			this->splitComponents->Panel2->SuspendLayout();
			this->splitComponents->SuspendLayout();
			this->toolsEdit->SuspendLayout();
			this->toolsSimulate->SuspendLayout();
			this->toolsView->SuspendLayout();
			this->sStatus->SuspendLayout();
			this->SuspendLayout();
			// 
			// toolStripContainer1
			// 
			this->toolStripContainer1->BottomToolStripPanelVisible = false;
			// 
			// toolStripContainer1.ContentPanel
			// 
			this->toolStripContainer1->ContentPanel->Controls->Add(this->splitWindow);
			this->toolStripContainer1->ContentPanel->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->toolStripContainer1->ContentPanel->Size = System::Drawing::Size(1174, 671);
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
			this->toolStripContainer1->TopToolStripPanel->Controls->Add(this->toolsView);
			this->toolStripContainer1->TopToolStripPanel->RenderMode = System::Windows::Forms::ToolStripRenderMode::Professional;
			// 
			// splitWindow
			// 
			this->splitWindow->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->splitWindow->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitWindow->FixedPanel = System::Windows::Forms::FixedPanel::Panel1;
			this->splitWindow->Location = System::Drawing::Point(0, 0);
			this->splitWindow->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->splitWindow->Name = L"splitWindow";
			// 
			// splitWindow.Panel1
			// 
			this->splitWindow->Panel1->Controls->Add(this->splitComponents);
			// 
			// splitWindow.Panel2
			// 
			this->splitWindow->Panel2->Controls->Add(this->pBackground);
			this->splitWindow->Size = System::Drawing::Size(1174, 671);
			this->splitWindow->SplitterDistance = 229;
			this->splitWindow->SplitterWidth = 6;
			this->splitWindow->TabIndex = 3;
			// 
			// splitComponents
			// 
			this->splitComponents->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitComponents->FixedPanel = System::Windows::Forms::FixedPanel::Panel2;
			this->splitComponents->Location = System::Drawing::Point(0, 0);
			this->splitComponents->Name = L"splitComponents";
			this->splitComponents->Orientation = System::Windows::Forms::Orientation::Horizontal;
			// 
			// splitComponents.Panel1
			// 
			this->splitComponents->Panel1->Controls->Add(this->lblComponentCollapse);
			this->splitComponents->Panel1->Controls->Add(this->lblRotatedComponents);
			this->splitComponents->Panel1->Controls->Add(this->lstComponents);
			this->splitComponents->Panel1->Controls->Add(this->label1);
			// 
			// splitComponents.Panel2
			// 
			this->splitComponents->Panel2->Controls->Add(this->lblRotatedDescription);
			this->splitComponents->Panel2->Controls->Add(this->textBox1);
			this->splitComponents->Panel2->Controls->Add(this->label2);
			this->splitComponents->Panel2MinSize = 53;
			this->splitComponents->Size = System::Drawing::Size(229, 671);
			this->splitComponents->SplitterDistance = 530;
			this->splitComponents->TabIndex = 3;
			// 
			// lblComponentCollapse
			// 
			this->lblComponentCollapse->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->lblComponentCollapse->BackColor = System::Drawing::Color::RoyalBlue;
			this->lblComponentCollapse->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Pixel));
			this->lblComponentCollapse->ForeColor = System::Drawing::Color::White;
			this->lblComponentCollapse->ImageAlign = System::Drawing::ContentAlignment::TopLeft;
			this->lblComponentCollapse->Location = System::Drawing::Point(201, -1);
			this->lblComponentCollapse->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lblComponentCollapse->Name = L"lblComponentCollapse";
			this->lblComponentCollapse->Size = System::Drawing::Size(27, 30);
			this->lblComponentCollapse->TabIndex = 2;
			this->lblComponentCollapse->Text = L"<<";
			this->lblComponentCollapse->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->lblComponentCollapse->Click += gcnew System::EventHandler(this, &frmMain::lblComponentCollapse_Click);
			// 
			// lblRotatedComponents
			// 
			this->lblRotatedComponents->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
						| System::Windows::Forms::AnchorStyles::Left));
			this->lblRotatedComponents->BackColor = System::Drawing::Color::RoyalBlue;
			this->lblRotatedComponents->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Pixel));
			this->lblRotatedComponents->ForeColor = System::Drawing::Color::White;
			this->lblRotatedComponents->Location = System::Drawing::Point(0, 0);
			this->lblRotatedComponents->Margin = System::Windows::Forms::Padding(0);
			this->lblRotatedComponents->Name = L"lblRotatedComponents";
			this->lblRotatedComponents->NewText = L"Logic Components";
			this->lblRotatedComponents->Padding = System::Windows::Forms::Padding(40, 10, 0, 0);
			this->lblRotatedComponents->RotateAngle = 90;
			this->lblRotatedComponents->Size = System::Drawing::Size(30, 530);
			this->lblRotatedComponents->TabIndex = 2;
			this->lblRotatedComponents->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->lblRotatedComponents->UseCompatibleTextRendering = true;
			this->lblRotatedComponents->Visible = false;
			this->lblRotatedComponents->Click += gcnew System::EventHandler(this, &frmMain::lblComponentCollapse_Click);
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
			listViewGroup1->Header = L"Logic Gates";
			listViewGroup1->HeaderAlignment = System::Windows::Forms::HorizontalAlignment::Center;
			listViewGroup1->Name = L"lstGroupGates";
			listViewGroup2->Header = L"Timers";
			listViewGroup2->HeaderAlignment = System::Windows::Forms::HorizontalAlignment::Center;
			listViewGroup2->Name = L"lstGroupTimers";
			listViewGroup3->Header = L"Counters";
			listViewGroup3->Name = L"lstGroupCounters";
			listViewGroup4->Header = L"Special Components";
			listViewGroup4->Name = L"lstGroupSpecial";
			this->lstComponents->Groups->AddRange(gcnew cli::array< System::Windows::Forms::ListViewGroup^  >(4) {
				listViewGroup1, listViewGroup2,
listViewGroup3, listViewGroup4
			});
			this->lstComponents->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::None;
			this->lstComponents->HideSelection = false;
			listViewItem1->Group = listViewGroup1;
			listViewItem1->UseItemStyleForSubItems = false;
			listViewItem2->Group = listViewGroup1;
			listViewItem3->Group = listViewGroup1;
			listViewItem4->Group = listViewGroup1;
			listViewItem5->Group = listViewGroup1;
			listViewItem6->Group = listViewGroup2;
			listViewItem7->Group = listViewGroup2;
			listViewItem8->Group = listViewGroup2;
			listViewItem9->Group = listViewGroup3;
			listViewItem10->Group = listViewGroup3;
			listViewItem11->Group = listViewGroup4;
			listViewItem12->Group = listViewGroup4;
			this->lstComponents->Items->AddRange(gcnew cli::array< System::Windows::Forms::ListViewItem^  >(12) {
				listViewItem1, listViewItem2,
listViewItem3, listViewItem4, listViewItem5, listViewItem6, listViewItem7, listViewItem8, listViewItem9, listViewItem10, listViewItem11,
listViewItem12
			});
			this->lstComponents->LabelWrap = false;
			this->lstComponents->LargeImageList = this->imgBlocksLarge;
			this->lstComponents->Location = System::Drawing::Point(0, 30);
			this->lstComponents->Margin = System::Windows::Forms::Padding(0);
			this->lstComponents->MultiSelect = false;
			this->lstComponents->Name = L"lstComponents";
			this->lstComponents->Size = System::Drawing::Size(229, 500);
			this->lstComponents->SmallImageList = this->imgBlocksSmall;
			this->lstComponents->TabIndex = 0;
			this->lstComponents->UseCompatibleStateImageBehavior = false;
			this->lstComponents->View = System::Windows::Forms::View::Tile;
			// 
			// columnHeader1
			// 
			this->columnHeader1->Text = L"";
			this->columnHeader1->Width = 152;
			// 
			// imgBlocksLarge
			// 
			this->imgBlocksLarge->ColorDepth = System::Windows::Forms::ColorDepth::Depth32Bit;
			this->imgBlocksLarge->ImageSize = System::Drawing::Size(32, 32);
			this->imgBlocksLarge->TransparentColor = System::Drawing::Color::Transparent;
			// 
			// imgBlocksSmall
			// 
			this->imgBlocksSmall->ColorDepth = System::Windows::Forms::ColorDepth::Depth32Bit;
			this->imgBlocksSmall->ImageSize = System::Drawing::Size(16, 16);
			this->imgBlocksSmall->TransparentColor = System::Drawing::Color::Transparent;
			// 
			// label1
			// 
			this->label1->BackColor = System::Drawing::Color::RoyalBlue;
			this->label1->Dock = System::Windows::Forms::DockStyle::Top;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Pixel));
			this->label1->ForeColor = System::Drawing::Color::White;
			this->label1->Location = System::Drawing::Point(0, 0);
			this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label1->MinimumSize = System::Drawing::Size(392, 30);
			this->label1->Name = L"label1";
			this->label1->Padding = System::Windows::Forms::Padding(8, 0, 0, 0);
			this->label1->Size = System::Drawing::Size(392, 30);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Logic Components";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->label1->UseCompatibleTextRendering = true;
			// 
			// lblRotatedDescription
			// 
			this->lblRotatedDescription->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
						| System::Windows::Forms::AnchorStyles::Left));
			this->lblRotatedDescription->BackColor = System::Drawing::Color::RoyalBlue;
			this->lblRotatedDescription->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Pixel));
			this->lblRotatedDescription->ForeColor = System::Drawing::Color::White;
			this->lblRotatedDescription->Location = System::Drawing::Point(0, 0);
			this->lblRotatedDescription->Margin = System::Windows::Forms::Padding(0);
			this->lblRotatedDescription->Name = L"lblRotatedDescription";
			this->lblRotatedDescription->NewText = L"Description";
			this->lblRotatedDescription->Padding = System::Windows::Forms::Padding(10, 10, 0, 0);
			this->lblRotatedDescription->RotateAngle = 90;
			this->lblRotatedDescription->Size = System::Drawing::Size(30, 141);
			this->lblRotatedDescription->TabIndex = 3;
			this->lblRotatedDescription->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->lblRotatedDescription->UseCompatibleTextRendering = true;
			this->lblRotatedDescription->Visible = false;
			this->lblRotatedDescription->Click += gcnew System::EventHandler(this, &frmMain::lblComponentCollapse_Click);
			// 
			// textBox1
			// 
			this->textBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
						| System::Windows::Forms::AnchorStyles::Left)
						| System::Windows::Forms::AnchorStyles::Right));
			this->textBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox1->Location = System::Drawing::Point(0, 29);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(229, 83);
			this->textBox1->TabIndex = 3;
			this->textBox1->Text = L"akjshdkjashdkjashdkjhaskjdh aksjdh kajshd kjashdk jahsdkjh askjdh kjahsdkjh aksjd"
			L"hk jahsdkj hdh ksajhkajshdkjasdh kjashd ajksd hkajsh kajshd kahsd kjhasd kjhasd "
			L"hsad hkasdhjashdk jhaskdh ";
			// 
			// label2
			// 
			this->label2->BackColor = System::Drawing::Color::RoyalBlue;
			this->label2->Dock = System::Windows::Forms::DockStyle::Top;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Pixel));
			this->label2->ForeColor = System::Drawing::Color::White;
			this->label2->Location = System::Drawing::Point(0, 0);
			this->label2->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label2->MinimumSize = System::Drawing::Size(392, 30);
			this->label2->Name = L"label2";
			this->label2->Padding = System::Windows::Forms::Padding(8, 0, 0, 0);
			this->label2->Size = System::Drawing::Size(392, 30);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Description";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->label2->UseCompatibleTextRendering = true;
			// 
			// pBackground
			// 
			this->pBackground->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pBackground->Location = System::Drawing::Point(0, 0);
			this->pBackground->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->pBackground->Name = L"pBackground";
			this->pBackground->Size = System::Drawing::Size(939, 671);
			this->pBackground->TabIndex = 2;
			this->pBackground->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &frmMain::pBackground_Paint);
			this->pBackground->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &frmMain::pBackground_MouseDown);
			this->pBackground->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &frmMain::pBackground_MouseMove);
			this->pBackground->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &frmMain::pBackground_MouseUp);
			this->pBackground->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &frmMain::pBackground_OnMouseWheel);
			// 
			// toolsEdit
			// 
			this->toolsEdit->Dock = System::Windows::Forms::DockStyle::None;
			this->toolsEdit->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7) {
				this->tcmdOpen, this->tcmdSave,
this->toolStripSeparator1, this->tcmdCopy, this->tcmdCut, this->tcmdPaste, this->tcmdDelete
			});
			this->toolsEdit->LayoutStyle = System::Windows::Forms::ToolStripLayoutStyle::HorizontalStackWithOverflow;
			this->toolsEdit->Location = System::Drawing::Point(3, 50);
			this->toolsEdit->Name = L"toolsEdit";
			this->toolsEdit->Size = System::Drawing::Size(156, 25);
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
			this->tcmdOpen->Text = L"Open";
			this->tcmdOpen->ToolTipText = L"Open (Ctrl + O)";
			// 
			// tcmdSave
			// 
			this->tcmdSave->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->tcmdSave->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tcmdSave.Image")));
			this->tcmdSave->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
			this->tcmdSave->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tcmdSave->Name = L"tcmdSave";
			this->tcmdSave->Size = System::Drawing::Size(23, 22);
			this->tcmdSave->Text = L"Save";
			this->tcmdSave->ToolTipText = L"Save (Ctrl + S)";
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(6, 25);
			// 
			// tcmdCopy
			// 
			this->tcmdCopy->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->tcmdCopy->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tcmdCopy.Image")));
			this->tcmdCopy->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
			this->tcmdCopy->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tcmdCopy->Name = L"tcmdCopy";
			this->tcmdCopy->Size = System::Drawing::Size(23, 22);
			this->tcmdCopy->Text = L"Copy";
			this->tcmdCopy->ToolTipText = L"Copy (Ctrl + C)";
			// 
			// tcmdCut
			// 
			this->tcmdCut->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->tcmdCut->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tcmdCut.Image")));
			this->tcmdCut->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tcmdCut->Name = L"tcmdCut";
			this->tcmdCut->Size = System::Drawing::Size(23, 22);
			this->tcmdCut->Text = L"Cut";
			this->tcmdCut->ToolTipText = L"Cut (Ctrl + X)";
			// 
			// tcmdPaste
			// 
			this->tcmdPaste->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->tcmdPaste->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tcmdPaste.Image")));
			this->tcmdPaste->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
			this->tcmdPaste->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tcmdPaste->Name = L"tcmdPaste";
			this->tcmdPaste->Size = System::Drawing::Size(23, 22);
			this->tcmdPaste->Text = L"Paste";
			this->tcmdPaste->ToolTipText = L"Paste (Ctrl + V)";
			// 
			// tcmdDelete
			// 
			this->tcmdDelete->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->tcmdDelete->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tcmdDelete.Image")));
			this->tcmdDelete->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
			this->tcmdDelete->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tcmdDelete->Name = L"tcmdDelete";
			this->tcmdDelete->Size = System::Drawing::Size(23, 22);
			this->tcmdDelete->Text = L"Delete";
			this->tcmdDelete->ToolTipText = L"Delete  Selected Items (Del)";
			// 
			// toolsSimulate
			// 
			this->toolsSimulate->AllowMerge = false;
			this->toolsSimulate->Dock = System::Windows::Forms::DockStyle::None;
			this->toolsSimulate->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->tcmdSimulateStart,
this->tcmdSimulateStop
			});
			this->toolsSimulate->Location = System::Drawing::Point(93, 25);
			this->toolsSimulate->Name = L"toolsSimulate";
			this->toolsSimulate->Padding = System::Windows::Forms::Padding(0);
			this->toolsSimulate->Size = System::Drawing::Size(57, 25);
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
			// toolsView
			// 
			this->toolsView->AllowMerge = false;
			this->toolsView->Dock = System::Windows::Forms::DockStyle::None;
			this->toolsView->ImageScalingSize = System::Drawing::Size(24, 24);
			this->toolsView->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) { this->tlblZoom, this->tcmbZoom });
			this->toolsView->Location = System::Drawing::Point(19, 0);
			this->toolsView->Name = L"toolsView";
			this->toolsView->Size = System::Drawing::Size(131, 25);
			this->toolsView->TabIndex = 2;
			// 
			// tlblZoom
			// 
			this->tlblZoom->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Pixel));
			this->tlblZoom->Name = L"tlblZoom";
			this->tlblZoom->Size = System::Drawing::Size(42, 22);
			this->tlblZoom->Text = L"Zoom:";
			// 
			// tcmbZoom
			// 
			this->tcmbZoom->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->tcmbZoom->DropDownWidth = 75;
			this->tcmbZoom->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->tcmbZoom->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Pixel));
			this->tcmbZoom->Items->AddRange(gcnew cli::array< System::Object^  >(5) { L"60%", L"80%", L"100%", L"150%", L"200%" });
			this->tcmbZoom->MergeAction = System::Windows::Forms::MergeAction::MatchOnly;
			this->tcmbZoom->MergeIndex = 0;
			this->tcmbZoom->Name = L"tcmbZoom";
			this->tcmbZoom->Size = System::Drawing::Size(75, 25);
			this->tcmbZoom->SelectedIndexChanged += gcnew System::EventHandler(this, &frmMain::tcmbZoom_OnSelectedIndexChanged);
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
			this->sStatus->Location = System::Drawing::Point(0, 721);
			this->sStatus->Name = L"sStatus";
			this->sStatus->Padding = System::Windows::Forms::Padding(2, 0, 21, 0);
			this->sStatus->Size = System::Drawing::Size(1174, 25);
			this->sStatus->TabIndex = 3;
			this->sStatus->Text = L"statusStrip1";
			// 
			// lblStatusSpring
			// 
			this->lblStatusSpring->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->lblStatusSpring->Name = L"lblStatusSpring";
			this->lblStatusSpring->Size = System::Drawing::Size(992, 20);
			this->lblStatusSpring->Spring = true;
			// 
			// lblStatusCtrl
			// 
			this->lblStatusCtrl->AutoSize = false;
			this->lblStatusCtrl->BackColor = System::Drawing::Color::Silver;
			this->lblStatusCtrl->Margin = System::Windows::Forms::Padding(3, 3, 0, 2);
			this->lblStatusCtrl->Name = L"lblStatusCtrl";
			this->lblStatusCtrl->Size = System::Drawing::Size(50, 20);
			this->lblStatusCtrl->Text = L"Ctrl";
			// 
			// lblStatusAlt
			// 
			this->lblStatusAlt->AutoSize = false;
			this->lblStatusAlt->BackColor = System::Drawing::Color::Silver;
			this->lblStatusAlt->Margin = System::Windows::Forms::Padding(3, 3, 0, 2);
			this->lblStatusAlt->Name = L"lblStatusAlt";
			this->lblStatusAlt->Size = System::Drawing::Size(50, 20);
			this->lblStatusAlt->Text = L"Alt";
			// 
			// lblStatusShift
			// 
			this->lblStatusShift->AutoSize = false;
			this->lblStatusShift->BackColor = System::Drawing::Color::Silver;
			this->lblStatusShift->Margin = System::Windows::Forms::Padding(3, 3, 0, 2);
			this->lblStatusShift->Name = L"lblStatusShift";
			this->lblStatusShift->Size = System::Drawing::Size(50, 20);
			this->lblStatusShift->Text = L"Shift";
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
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &frmMain::frmMain_KeyDown);
			this->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &frmMain::frmMain_KeyPress);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &frmMain::frmMain_KeyUp);
			this->toolStripContainer1->ContentPanel->ResumeLayout(false);
			this->toolStripContainer1->TopToolStripPanel->ResumeLayout(false);
			this->toolStripContainer1->TopToolStripPanel->PerformLayout();
			this->toolStripContainer1->ResumeLayout(false);
			this->toolStripContainer1->PerformLayout();
			this->splitWindow->Panel1->ResumeLayout(false);
			this->splitWindow->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitWindow))->EndInit();
			this->splitWindow->ResumeLayout(false);
			this->splitComponents->Panel1->ResumeLayout(false);
			this->splitComponents->Panel2->ResumeLayout(false);
			this->splitComponents->Panel2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitComponents))->EndInit();
			this->splitComponents->ResumeLayout(false);
			this->toolsEdit->ResumeLayout(false);
			this->toolsEdit->PerformLayout();
			this->toolsSimulate->ResumeLayout(false);
			this->toolsSimulate->PerformLayout();
			this->toolsView->ResumeLayout(false);
			this->toolsView->PerformLayout();
			this->sStatus->ResumeLayout(false);
			this->sStatus->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private: System::Void pBackground_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
}
private: System::Void pBackground_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
}
private: System::Void pBackground_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
}
};
};
