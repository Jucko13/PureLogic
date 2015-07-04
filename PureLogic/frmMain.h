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
		void frmMain_Paint(Object^  sender, PaintEventArgs^  e);
		void frmMain_MouseDown(Object^  sender, MouseEventArgs^  e);

	protected:
		~frmMain()
		{
			if (components){ delete components;	}
		}

	private:
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->SuspendLayout(); //pause the layout refresh

			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 262);
			this->Name = L"frmMain";
			this->Text = L"frmMain";
			this->Load += gcnew System::EventHandler(this, &frmMain::frmMain_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &frmMain::frmMain_Paint);
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &frmMain::frmMain_MouseDown);

			this->ResumeLayout(false); //resume the refresh

		}
#pragma endregion
	};
};
