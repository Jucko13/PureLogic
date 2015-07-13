#pragma once

#include <string.h>

using namespace System::Drawing;

ref class RotationLabel : public System::Windows::Forms::Label {
	public :
		property int RotateAngle {
			int get(){
				return this->RotateAngleA;
			}

			void set(int n){
				RotateAngleA = n;
			}
		}

		property System::String ^  NewText {
			System::String ^  get() {
				return this->NewTextA;
			}

			void set(System::String ^ n) {
				NewTextA = n;
				this->Invalidate();
			}
		}

	protected:
		

		void OnPaint(System::Windows::Forms::PaintEventArgs ^e) override {
			Brush ^ b = gcnew SolidBrush(this->ForeColor);
			e->Graphics->TranslateTransform(this->Width / 2.0f, (float)this->Height);
			e->Graphics->RotateTransform((float)this->RotateAngle);
			e->Graphics->DrawString(this->NewText, this->Font, b, PointF((float)-this->Height + this->Padding.Left, (float)-this->Padding.Top));
			System::Windows::Forms::Label::OnPaint(e);
		}

	private:
		System::String ^ NewTextA;
		int RotateAngleA = 0;

};