#pragma once
#define WIN32_LEAN_AND_MEAN
#include <chrono>		//Pomiar czasu wykonania
#include <omp.h>		//Wielowatkowosc
#include "Bmps.h"		//Funkcje obslugi Bitmap

julia fractal;							//Klasa fraktali
std::complex<long double> c;			//Liczba zespolona przechowujaca zmienne z aplikacji okienkowej
long double factor = FCT / BMP_SIZE;	//Stala dla bitmapy
int prgs = 0;						//Licznik dla Progress bar
HINSTANCE DLL_LIB;	//DLL handler
fnptr fn;			//Typ wskaznika na funkcje, zdefiniowany w Bmps.h

namespace CppCLRWinformsProjekt {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
		}

	protected:
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::GroupBox^ DLLgroupBox;
	private: System::Windows::Forms::RadioButton^ DLLradioButtonASM;
	private: System::Windows::Forms::RadioButton^ DLLradioButtonCPP;
	private: System::Windows::Forms::GroupBox^ PreviewgroupBox;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::Button^ Generatebutton;
	private: System::Windows::Forms::GroupBox^ ThreadsgroupBox;
	private: System::Windows::Forms::Label^ Threadslabel;
	private: System::Windows::Forms::TrackBar^ ThreadstrackBar;

	private: System::Windows::Forms::GroupBox^ ParametersgroupBox;
	private: System::Windows::Forms::Label^ Imaginarislabel;

	private: System::Windows::Forms::Label^ Realislabel;
	private: System::Windows::Forms::NumericUpDown^ IMnumericUpDown;

	private: System::Windows::Forms::NumericUpDown^ REnumericUpDown;
	private: System::Windows::Forms::GroupBox^ OutputgroupBox;
	private: System::Windows::Forms::ProgressBar^ progressBar;


	private: System::Windows::Forms::Label^ TimeExecutionlabel;
	private: System::Windows::Forms::Label^ TIMElabel;
	private: System::Windows::Forms::GroupBox^ Errorgroupbox;
	private: System::Windows::Forms::Label^ ErrorOutpulabel;
	private: System::Windows::Forms::Label^ Creditlabel;

	protected:

	protected:

	private:
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->DLLgroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->DLLradioButtonASM = (gcnew System::Windows::Forms::RadioButton());
			this->DLLradioButtonCPP = (gcnew System::Windows::Forms::RadioButton());
			this->PreviewgroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->Generatebutton = (gcnew System::Windows::Forms::Button());
			this->ThreadsgroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->Threadslabel = (gcnew System::Windows::Forms::Label());
			this->ThreadstrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->ParametersgroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->IMnumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->REnumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->Imaginarislabel = (gcnew System::Windows::Forms::Label());
			this->Realislabel = (gcnew System::Windows::Forms::Label());
			this->OutputgroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->progressBar = (gcnew System::Windows::Forms::ProgressBar());
			this->TimeExecutionlabel = (gcnew System::Windows::Forms::Label());
			this->TIMElabel = (gcnew System::Windows::Forms::Label());
			this->Errorgroupbox = (gcnew System::Windows::Forms::GroupBox());
			this->ErrorOutpulabel = (gcnew System::Windows::Forms::Label());
			this->Creditlabel = (gcnew System::Windows::Forms::Label());
			this->DLLgroupBox->SuspendLayout();
			this->PreviewgroupBox->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->ThreadsgroupBox->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ThreadstrackBar))->BeginInit();
			this->ParametersgroupBox->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->IMnumericUpDown))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->REnumericUpDown))->BeginInit();
			this->OutputgroupBox->SuspendLayout();
			this->Errorgroupbox->SuspendLayout();
			this->SuspendLayout();
			// 
			// DLLgroupBox
			// 
			this->DLLgroupBox->Controls->Add(this->DLLradioButtonASM);
			this->DLLgroupBox->Controls->Add(this->DLLradioButtonCPP);
			this->DLLgroupBox->Location = System::Drawing::Point(726, 12);
			this->DLLgroupBox->Name = L"DLLgroupBox";
			this->DLLgroupBox->Size = System::Drawing::Size(200, 52);
			this->DLLgroupBox->TabIndex = 0;
			this->DLLgroupBox->TabStop = false;
			this->DLLgroupBox->Text = L"DLL";
			// 
			// DLLradioButtonASM
			// 
			this->DLLradioButtonASM->AutoSize = true;
			this->DLLradioButtonASM->Location = System::Drawing::Point(146, 19);
			this->DLLradioButtonASM->Name = L"DLLradioButtonASM";
			this->DLLradioButtonASM->Size = System::Drawing::Size(48, 17);
			this->DLLradioButtonASM->TabIndex = 0;
			this->DLLradioButtonASM->Text = L"ASM";
			this->DLLradioButtonASM->UseVisualStyleBackColor = true;
			this->DLLradioButtonASM->CheckedChanged += gcnew System::EventHandler(this, &Form1::DLLradioButtonASM_CheckedChanged);
			// 
			// DLLradioButtonCPP
			// 
			this->DLLradioButtonCPP->AutoSize = true;
			this->DLLradioButtonCPP->Location = System::Drawing::Point(6, 19);
			this->DLLradioButtonCPP->Name = L"DLLradioButtonCPP";
			this->DLLradioButtonCPP->Size = System::Drawing::Size(44, 17);
			this->DLLradioButtonCPP->TabIndex = 0;
			this->DLLradioButtonCPP->Text = L"C++";
			this->DLLradioButtonCPP->UseVisualStyleBackColor = true;
			this->DLLradioButtonCPP->CheckedChanged += gcnew System::EventHandler(this, &Form1::DLLradioButtonCPP_CheckedChanged);
			// 
			// PreviewgroupBox
			// 
			this->PreviewgroupBox->Controls->Add(this->pictureBox1);
			this->PreviewgroupBox->Location = System::Drawing::Point(12, 12);
			this->PreviewgroupBox->Name = L"PreviewgroupBox";
			this->PreviewgroupBox->Size = System::Drawing::Size(708, 631);
			this->PreviewgroupBox->TabIndex = 1;
			this->PreviewgroupBox->TabStop = false;
			this->PreviewgroupBox->Text = L"Preview";
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(6, 19);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(696, 606);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// Generatebutton
			// 
			this->Generatebutton->Location = System::Drawing::Point(726, 594);
			this->Generatebutton->Name = L"Generatebutton";
			this->Generatebutton->Size = System::Drawing::Size(200, 36);
			this->Generatebutton->TabIndex = 2;
			this->Generatebutton->Text = L"Generate";
			this->Generatebutton->UseVisualStyleBackColor = true;
			this->Generatebutton->Click += gcnew System::EventHandler(this, &Form1::Generatebutton_Click);
			// 
			// ThreadsgroupBox
			// 
			this->ThreadsgroupBox->Controls->Add(this->Threadslabel);
			this->ThreadsgroupBox->Controls->Add(this->ThreadstrackBar);
			this->ThreadsgroupBox->Location = System::Drawing::Point(726, 70);
			this->ThreadsgroupBox->Name = L"ThreadsgroupBox";
			this->ThreadsgroupBox->Size = System::Drawing::Size(200, 66);
			this->ThreadsgroupBox->TabIndex = 3;
			this->ThreadsgroupBox->TabStop = false;
			this->ThreadsgroupBox->Text = L"Threads";
			// 
			// Threadslabel
			// 
			this->Threadslabel->AutoSize = true;
			this->Threadslabel->Location = System::Drawing::Point(6, 28);
			this->Threadslabel->Name = L"Threadslabel";
			this->Threadslabel->Size = System::Drawing::Size(13, 13);
			this->Threadslabel->TabIndex = 4;
			this->Threadslabel->Text = L"1";
			// 
			// ThreadstrackBar
			// 
			this->ThreadstrackBar->Location = System::Drawing::Point(25, 16);
			this->ThreadstrackBar->Maximum = 64;
			this->ThreadstrackBar->Minimum = 1;
			this->ThreadstrackBar->Name = L"ThreadstrackBar";
			this->ThreadstrackBar->Size = System::Drawing::Size(163, 45);
			this->ThreadstrackBar->TabIndex = 0;
			this->ThreadstrackBar->TickStyle = System::Windows::Forms::TickStyle::Both;
			this->ThreadstrackBar->Value = 1;
			this->ThreadstrackBar->Scroll += gcnew System::EventHandler(this, &Form1::ThreadstrackBar_Scroll);
			// 
			// ParametersgroupBox
			// 
			this->ParametersgroupBox->Controls->Add(this->IMnumericUpDown);
			this->ParametersgroupBox->Controls->Add(this->REnumericUpDown);
			this->ParametersgroupBox->Controls->Add(this->Imaginarislabel);
			this->ParametersgroupBox->Controls->Add(this->Realislabel);
			this->ParametersgroupBox->Location = System::Drawing::Point(726, 142);
			this->ParametersgroupBox->Name = L"ParametersgroupBox";
			this->ParametersgroupBox->Size = System::Drawing::Size(200, 78);
			this->ParametersgroupBox->TabIndex = 4;
			this->ParametersgroupBox->TabStop = false;
			this->ParametersgroupBox->Text = L"Parameters";
			// 
			// IMnumericUpDown
			// 
			this->IMnumericUpDown->DecimalPlaces = 5;
			this->IMnumericUpDown->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 327680 });
			this->IMnumericUpDown->Location = System::Drawing::Point(37, 45);
			this->IMnumericUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			this->IMnumericUpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, System::Int32::MinValue });
			this->IMnumericUpDown->Name = L"IMnumericUpDown";
			this->IMnumericUpDown->Size = System::Drawing::Size(151, 20);
			this->IMnumericUpDown->TabIndex = 8;
			// 
			// REnumericUpDown
			// 
			this->REnumericUpDown->DecimalPlaces = 5;
			this->REnumericUpDown->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 327680 });
			this->REnumericUpDown->Location = System::Drawing::Point(37, 19);
			this->REnumericUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			this->REnumericUpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, System::Int32::MinValue });
			this->REnumericUpDown->Name = L"REnumericUpDown";
			this->REnumericUpDown->Size = System::Drawing::Size(151, 20);
			this->REnumericUpDown->TabIndex = 7;
			// 
			// Imaginarislabel
			// 
			this->Imaginarislabel->AutoSize = true;
			this->Imaginarislabel->Location = System::Drawing::Point(9, 47);
			this->Imaginarislabel->Name = L"Imaginarislabel";
			this->Imaginarislabel->Size = System::Drawing::Size(22, 13);
			this->Imaginarislabel->TabIndex = 6;
			this->Imaginarislabel->Text = L"IM:";
			// 
			// Realislabel
			// 
			this->Realislabel->AutoSize = true;
			this->Realislabel->Location = System::Drawing::Point(6, 21);
			this->Realislabel->Name = L"Realislabel";
			this->Realislabel->Size = System::Drawing::Size(25, 13);
			this->Realislabel->TabIndex = 5;
			this->Realislabel->Text = L"RE:";
			// 
			// OutputgroupBox
			// 
			this->OutputgroupBox->Controls->Add(this->progressBar);
			this->OutputgroupBox->Controls->Add(this->TimeExecutionlabel);
			this->OutputgroupBox->Controls->Add(this->TIMElabel);
			this->OutputgroupBox->Location = System::Drawing::Point(726, 226);
			this->OutputgroupBox->Name = L"OutputgroupBox";
			this->OutputgroupBox->Size = System::Drawing::Size(200, 70);
			this->OutputgroupBox->TabIndex = 5;
			this->OutputgroupBox->TabStop = false;
			this->OutputgroupBox->Text = L"Output";
			// 
			// progressBar
			// 
			this->progressBar->Location = System::Drawing::Point(6, 41);
			this->progressBar->Maximum = 600;
			this->progressBar->Name = L"progressBar";
			this->progressBar->Size = System::Drawing::Size(188, 23);
			this->progressBar->Step = 1;
			this->progressBar->TabIndex = 2;
			// 
			// TimeExecutionlabel
			// 
			this->TimeExecutionlabel->AutoSize = true;
			this->TimeExecutionlabel->Location = System::Drawing::Point(49, 20);
			this->TimeExecutionlabel->Name = L"TimeExecutionlabel";
			this->TimeExecutionlabel->Size = System::Drawing::Size(16, 13);
			this->TimeExecutionlabel->TabIndex = 1;
			this->TimeExecutionlabel->Text = L"---";
			// 
			// TIMElabel
			// 
			this->TIMElabel->AutoSize = true;
			this->TIMElabel->Location = System::Drawing::Point(7, 20);
			this->TIMElabel->Name = L"TIMElabel";
			this->TIMElabel->Size = System::Drawing::Size(36, 13);
			this->TIMElabel->TabIndex = 0;
			this->TIMElabel->Text = L"Time: ";
			// 
			// Errorgroupbox
			// 
			this->Errorgroupbox->Controls->Add(this->ErrorOutpulabel);
			this->Errorgroupbox->Location = System::Drawing::Point(726, 302);
			this->Errorgroupbox->Name = L"Errorgroupbox";
			this->Errorgroupbox->Size = System::Drawing::Size(200, 40);
			this->Errorgroupbox->TabIndex = 6;
			this->Errorgroupbox->TabStop = false;
			this->Errorgroupbox->Text = L"Error output";
			// 
			// ErrorOutpulabel
			// 
			this->ErrorOutpulabel->AutoSize = true;
			this->ErrorOutpulabel->ForeColor = System::Drawing::Color::Red;
			this->ErrorOutpulabel->Location = System::Drawing::Point(6, 16);
			this->ErrorOutpulabel->Name = L"ErrorOutpulabel";
			this->ErrorOutpulabel->Size = System::Drawing::Size(16, 13);
			this->ErrorOutpulabel->TabIndex = 0;
			this->ErrorOutpulabel->Text = L"---";
			// 
			// Creditlabel
			// 
			this->Creditlabel->AutoSize = true;
			this->Creditlabel->Location = System::Drawing::Point(822, 633);
			this->Creditlabel->Name = L"Creditlabel";
			this->Creditlabel->Size = System::Drawing::Size(104, 13);
			this->Creditlabel->TabIndex = 7;
			this->Creditlabel->Text = L"Marceli Janczy 2020";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(938, 655);
			this->Controls->Add(this->Creditlabel);
			this->Controls->Add(this->Errorgroupbox);
			this->Controls->Add(this->OutputgroupBox);
			this->Controls->Add(this->ParametersgroupBox);
			this->Controls->Add(this->ThreadsgroupBox);
			this->Controls->Add(this->Generatebutton);
			this->Controls->Add(this->PreviewgroupBox);
			this->Controls->Add(this->DLLgroupBox);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"Form1";
			this->Text = L"Julia_Set";
			this->DLLgroupBox->ResumeLayout(false);
			this->DLLgroupBox->PerformLayout();
			this->PreviewgroupBox->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ThreadsgroupBox->ResumeLayout(false);
			this->ThreadsgroupBox->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ThreadstrackBar))->EndInit();
			this->ParametersgroupBox->ResumeLayout(false);
			this->ParametersgroupBox->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->IMnumericUpDown))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->REnumericUpDown))->EndInit();
			this->OutputgroupBox->ResumeLayout(false);
			this->OutputgroupBox->PerformLayout();
			this->Errorgroupbox->ResumeLayout(false);
			this->Errorgroupbox->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	
	private: System::Void DLLradioButtonCPP_CheckedChanged(System::Object^ sender, System::EventArgs^ e) 
	{
		FreeLibrary(DLL_LIB);								//zwolnienie biblioteki DLL
		DLL_LIB = LoadLibrary(L"CPP_LIB.dll");				//zaladowanie DLL z C++
		fn = (fnptr)GetProcAddress(DLL_LIB, "inSet");		//wskaznik na funkcje
	}

	private: System::Void DLLradioButtonASM_CheckedChanged(System::Object^ sender, System::EventArgs^ e) 
	{
		FreeLibrary(DLL_LIB);								//zwolnienie biblioteki DLL
		DLL_LIB = LoadLibrary(L"ASMLIB.dll");				//zaladowanie DLL z ASM
		fn = (fnptr)GetProcAddress(DLL_LIB, "INSETproc1");	//wskaznik na funkcje
	}

	private: System::Void ThreadstrackBar_Scroll(System::Object^ sender, System::EventArgs^ e)
	{
		Threadslabel->Text = ThreadstrackBar->Value.ToString();
	}

	private: System::Void Generatebutton_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		progressBar->Value = 0;
		ErrorOutpulabel->Text = "---";

		if (DLL_LIB == NULL)	//Sprawdzenie DLL
		{
			ErrorOutpulabel->Text = "DLL not found.";
		}
		else if (!fn) //Sprawdzenie funkcji
		{
			ErrorOutpulabel->Text = "Failed to call DLL function.";
		}
		else
		{
			c.real((factor)+(double)REnumericUpDown->Value);
			c.imag((factor)+(double)IMnumericUpDown->Value);


			auto start = std::chrono::steady_clock::now();	//start pomiaru czasu

			fractal.draw(fn, c, progressBar);			//funkcja rysujaca fraktal, przyjmuje wskaznik na odpowiednia funkcje asm/cpp w zaleznosci od DLL

			auto end = std::chrono::steady_clock::now();	//koniec pomiaru czasu
			

			TimeExecutionlabel->Text = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count().ToString() + " ms";	//Wyswietlenie czasu wykonania

			pictureBox1->ImageLocation = "./julia.bmp";	//zaladowanie podgladu
		}
	}

};
}