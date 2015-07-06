#pragma once

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
		void frmMain_Paint(Object^  sender, PaintEventArgs^  e);
		void frmMain_MouseDown(Object^  sender, MouseEventArgs^  e);
		void frmMain_MouseMove(Object^  sender, MouseEventArgs^  e);
		void frmMain_MouseUp(Object^  sender, MouseEventArgs^  e);
		void cmdAdd_Click(Object^  sender, EventArgs^  e);
		void cmdRemove_Click(Object^  sender, EventArgs^  e);
		void timerRefresh_Tick(Object^ state, System::Timers::ElapsedEventArgs^ e);
		void Redraw();

	protected:
		~frmMain()
		{
			if (components){ delete components;	}
		}
	private: System::Windows::Forms::Button^  cmdAdd;
	private: System::Windows::Forms::Button^  cmdRemove;
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
			this->cmdAdd = (gcnew System::Windows::Forms::Button());
			this->cmdRemove = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// cmdAdd
			// 
			this->cmdAdd->Location = System::Drawing::Point(344, 12);
			this->cmdAdd->Name = L"cmdAdd";
			this->cmdAdd->Size = System::Drawing::Size(153, 24);
			this->cmdAdd->TabIndex = 0;
			this->cmdAdd->Text = L"Set SimulationMode";
			this->cmdAdd->UseVisualStyleBackColor = true;
			this->cmdAdd->Click += gcnew System::EventHandler(this, &frmMain::cmdAdd_Click);
			// 
			// cmdRemove
			// 
			this->cmdRemove->Location = System::Drawing::Point(344, 42);
			this->cmdRemove->Name = L"cmdRemove";
			this->cmdRemove->Size = System::Drawing::Size(153, 24);
			this->cmdRemove->TabIndex = 1;
			this->cmdRemove->Text = L"Remove Input";
			this->cmdRemove->UseVisualStyleBackColor = true;
			this->cmdRemove->Click += gcnew System::EventHandler(this, &frmMain::cmdRemove_Click);
			// 
			// frmMain
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(509, 318);
			this->Controls->Add(this->cmdRemove);
			this->Controls->Add(this->cmdAdd);
			this->DoubleBuffered = true;
			this->Name = L"frmMain";
			this->Text = L"frmMain";
			this->Load += gcnew System::EventHandler(this, &frmMain::frmMain_Load);
			this->Closing += gcnew System::ComponentModel::CancelEventHandler(this, &frmMain::frmMain_Unload);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &frmMain::frmMain_Paint);
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &frmMain::frmMain_MouseDown);
			this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &frmMain::frmMain_MouseMove);
			this->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &frmMain::frmMain_MouseUp);
			this->ResumeLayout(false);

		}
#pragma endregion

	};
};
