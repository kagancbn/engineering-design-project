#pragma once
#include "image.h"
#include "NeuralNetwork.h"
#include "Process.h"
#include <iostream>
#include <fstream>
#include <atlstr.h>
#include "Form1.h"
namespace Bitirme {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
		}

	protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
			delete[] mean;
			delete[] variance;
			delete[] testData;
			delete[] tag;
			delete[] Samples;
			delete[] targets;
		}
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;


	protected:

	private:
		int  numClass = 0, numSample = 0;
		int inputDim;
		float* Samples, * targets;
		ANN* model = new ANN;
		float* mean;
		float* variance;
		bool initialized = false;
		// test
		float* testData;		// x-y Coord              
		float* tag;					// Class tag
		int numTestSample;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::ToolStripMenuItem^ openToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ openToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^ readWeightsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ extractFeaturesToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ predictToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ classificationToolStripMenuItem;

		   System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		   void ShowRGBImages(image im) {
			   pictureBox1->Width = im.w;
			   pictureBox1->Height = im.h;
			   pictureBox1->Refresh();
			   Bitmap^ surface = gcnew Bitmap(im.w, im.h);
			   pictureBox1->Image = surface;
			   Color c;
			   int psw, bufpos;
			   psw = im.w * 3;
			   for (int row = 0; row < im.h; row++)
				   for (int col = 0; col < im.w; col++) {
					   bufpos = row * psw + col * im.c;
					   c = Color::FromArgb(im.data[bufpos], im.data[bufpos + 1], im.data[bufpos + 2]);
					   surface->SetPixel(col, row, c);
				   }
		   }//ShowImages
		   void ShowGrayImages(image im) {
			   pictureBox1->Width = im.w;
			   pictureBox1->Height = im.h;
			   pictureBox1->Refresh();
			   Bitmap^ surface = gcnew Bitmap(im.w, im.h);
			   pictureBox1->Image = surface;
			   Color c;

			   int bufpos, psw1;
			   psw1 = im.w;
			   for (int row = 0; row < im.h; row++)
				   for (int col = 0; col < im.w; col++) {
					   bufpos = row * psw1 + col;
					   c = Color::FromArgb(im.data[bufpos], im.data[bufpos], im.data[bufpos]);
					   surface->SetPixel(col, row, c);
				   }
		   }
		   void drawB_box(Boxes* Bounding, int box_num) {
			   pictureBox1->Refresh();
			   Drawing::Graphics^ g;
			   g = pictureBox1->CreateGraphics();
			   Pen^ redPen = gcnew Pen(Color::Red);
			   for (int i = 0; i < box_num; i++)
			   {
				   Drawing::Rectangle rect(Bounding[i].left, Bounding[i].top, Bounding[i].right - Bounding[i].left, Bounding[i].bottom - Bounding[i].top);
				   g->DrawRectangle(redPen, rect);
			   }
		   }
		   void InitializeComponent(void)
		   {
			   this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			   this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			   this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->openToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->readWeightsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->extractFeaturesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->predictToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			   this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			   this->label1 = (gcnew System::Windows::Forms::Label());
			   this->classificationToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			   this->menuStrip1->SuspendLayout();
			   this->SuspendLayout();
			   // 
			   // pictureBox1
			   // 
			   this->pictureBox1->Location = System::Drawing::Point(0, 25);
			   this->pictureBox1->Margin = System::Windows::Forms::Padding(2);
			   this->pictureBox1->Name = L"pictureBox1";
			   this->pictureBox1->Size = System::Drawing::Size(538, 484);
			   this->pictureBox1->TabIndex = 0;
			   this->pictureBox1->TabStop = false;
			   // 
			   // menuStrip1
			   // 
			   this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			   this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->openToolStripMenuItem });
			   this->menuStrip1->Location = System::Drawing::Point(0, 0);
			   this->menuStrip1->Name = L"menuStrip1";
			   this->menuStrip1->Padding = System::Windows::Forms::Padding(4, 2, 0, 2);
			   this->menuStrip1->Size = System::Drawing::Size(1130, 24);
			   this->menuStrip1->TabIndex = 1;
			   this->menuStrip1->Text = L"menuStrip1";
			   // 
			   // openToolStripMenuItem
			   // 
			   this->openToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				   this->openToolStripMenuItem1,
					   this->readWeightsToolStripMenuItem, this->extractFeaturesToolStripMenuItem, this->classificationToolStripMenuItem, this->predictToolStripMenuItem
			   });
			   this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
			   this->openToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			   this->openToolStripMenuItem->Text = L"File";
			   // 
			   // openToolStripMenuItem1
			   // 
			   this->openToolStripMenuItem1->Name = L"openToolStripMenuItem1";
			   this->openToolStripMenuItem1->Size = System::Drawing::Size(180, 22);
			   this->openToolStripMenuItem1->Text = L"Object Detection";
			   this->openToolStripMenuItem1->Click += gcnew System::EventHandler(this, &MyForm::openToolStripMenuItem1_Click);
			   // 
			   // readWeightsToolStripMenuItem
			   // 
			   this->readWeightsToolStripMenuItem->Name = L"readWeightsToolStripMenuItem";
			   this->readWeightsToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			   this->readWeightsToolStripMenuItem->Text = L"Read Weights";
			   this->readWeightsToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::readWeightsToolStripMenuItem_Click);
			   // 
			   // extractFeaturesToolStripMenuItem
			   // 
			   this->extractFeaturesToolStripMenuItem->Name = L"extractFeaturesToolStripMenuItem";
			   this->extractFeaturesToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			   this->extractFeaturesToolStripMenuItem->Text = L"Extract Features";
			   this->extractFeaturesToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::extractFeaturesToolStripMenuItem_Click);
			   // 
			   // predictToolStripMenuItem
			   // 
			   this->predictToolStripMenuItem->Name = L"predictToolStripMenuItem";
			   this->predictToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			   this->predictToolStripMenuItem->Text = L"Predict";
			   this->predictToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::predictToolStripMenuItem_Click);
			   // 
			   // openFileDialog1
			   // 
			   this->openFileDialog1->FileName = L"openFileDialog1";
			   // 
			   // textBox1
			   // 
			   this->textBox1->Location = System::Drawing::Point(553, 53);
			   this->textBox1->Multiline = true;
			   this->textBox1->Name = L"textBox1";
			   this->textBox1->Size = System::Drawing::Size(494, 409);
			   this->textBox1->TabIndex = 5;
			   // 
			   // label1
			   // 
			   this->label1->Location = System::Drawing::Point(550, 36);
			   this->label1->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			   this->label1->Name = L"label1";
			   this->label1->Size = System::Drawing::Size(34, 14);
			   this->label1->TabIndex = 0;
			   // 
			   // classificationToolStripMenuItem
			   // 
			   this->classificationToolStripMenuItem->Name = L"classificationToolStripMenuItem";
			   this->classificationToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			   this->classificationToolStripMenuItem->Text = L"Classification";
			   this->classificationToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::classificationToolStripMenuItem_Click);
			   // 
			   // MyForm
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(1130, 558);
			   this->Controls->Add(this->label1);
			   this->Controls->Add(this->textBox1);
			   this->Controls->Add(this->pictureBox1);
			   this->Controls->Add(this->menuStrip1);
			   this->MainMenuStrip = this->menuStrip1;
			   this->Margin = System::Windows::Forms::Padding(2);
			   this->Name = L"MyForm";
			   this->Text = L"MyForm";
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			   this->menuStrip1->ResumeLayout(false);
			   this->menuStrip1->PerformLayout();
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }
#pragma endregion
	private: System::Void openToolStripMenuItem1_Click(System::Object^ sender, System::EventArgs^ e) {
		CString str;
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			//Load image
			str = openFileDialog1->FileName;
			CStringA s2(str);
			const char* input = s2;
			image im = load_image(input);
			//Segmentation - Background removing - Binary image
			im = rgb_to_gray(im.w, im.h, im.data);
			im = Smoothing(im, 5);
			int** histogram = Histogram(im);
			int* T_values; int T_number = 2;
			T_values = K_means(histogram, T_number, 1);
			im = gray_to_binary_image(im, T_values);
			im = Erosion(im);
			im = Dilation(im);
			//Drawing bounding box - Labeling objects-
			int* tagged_data = Connectivity(im);
			Boxes* bounding = bounding_box(tagged_data, im);
			ShowGrayImages(im);
			drawB_box(bounding, bounding->obj_num);
		}//		
	}
	private: System::Void readWeightsToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		char** c = new char* [1];
		// Veri Kümesini okunacak 
		c[0] = "Data/MeanVariance.txt";
		std::ifstream file;
		int num, samplenum, Dim, label;
		file.open(c[0]);
		if (file.is_open()) {
			textBox1->Text += " Trained Mean and Variance :  " + "\r\n";
			file >> Dim >> num;
			mean = new float[Dim];
			variance = new float[Dim];
			inputDim = Dim;
			for (int d = 0; d < inputDim; d++)
				file >> mean[d];
			for (int d = 0; d < inputDim; d++)
				file >> variance[d];
			file.close();
			for (int j = 0; j < inputDim; j++)
				textBox1->Text += Convert::ToString(mean[j]) + " ";
			for (int j = 0; j < inputDim; j++)
				textBox1->Text += Convert::ToString(variance[j]) + " ";
			MessageBox::Show("Dosya basari ile okundu");
			model->InitFromFile();
			initialized = true;
		}//file.is_open
		else MessageBox::Show("Mean Variance icin Dosya acilamadi");
		delete[]c;
	}

	private: System::Void extractFeaturesToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		CString str;

		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			//Load image
			str = openFileDialog1->FileName;
			CStringA s2(str);
			const char* input = s2;
			image im = load_image(input);
			//Segmentation - Background removing - Binary image
			im = rgb_to_gray(im.w, im.h, im.data);
			im = Smoothing(im, 5);
			int** histogram = Histogram(im);
			int* T_values; int T_number = 2;
			T_values = K_means(histogram, T_number, 1); // T values are piksel values that background and foreground
			im = gray_to_binary_image(im, T_values);
			im = Erosion(im);
			im = Dilation(im);
			ShowGrayImages(im);
			//Drawing bounding box - Numareting objects-
			int* tagged_data = Connectivity(im);
			Boxes* bounding = bounding_box(tagged_data, im);
			// Feature extraction
			FeatureExtraction(bounding, tagged_data, bounding->obj_num, im);
			drawB_box(bounding, bounding->obj_num);
		}//	
	}
	private: System::Void predictToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		CString str;
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			//Load image
			str = openFileDialog1->FileName;
			CStringA s2(str);
			const char* input = s2;
			image im = load_image(input);
			//Segmentation - Background removing - Binary image
			im = rgb_to_gray(im.w, im.h, im.data);
			im = Smoothing(im, 5);
			int** histogram = Histogram(im);
			int* T_values; int T_number = 2;
			T_values = K_means(histogram, T_number, 1); // T values are piksel values that background and foreground
			im = gray_to_binary_image(im, T_values);
			im = Erosion(im);
			im = Dilation(im);
			//Drawing bounding box - Numareting objects-
			int* tagged_data = Connectivity(im);
			Boxes* bounding = bounding_box(tagged_data, im);
			//Prediction
			image im1 = make_empty_image(im.w, im.h, 3);
			im1 = Prediction(bounding, tagged_data, im1, model, mean, variance);
			ShowRGBImages(im1);
			drawB_box(bounding, bounding->obj_num);
			MessageBox::Show("Yeþil Renk : Ürün " + "\r\n"
				+ " Kýrmýzý Renk : 1 Numaralý Yabani ot" + "\r\n"
				+ " Mavi Renk : 2 Numaralý yabani ot");
		}//	

	}

	private: System::Void classificationToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		Form1^ frm = gcnew Form1;
		frm->Show();
	}
		   //	   private: System::Void readTestSamplesToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		   //	// Reading Test Samples
		   //	char** c = new char* [1];
		   //	// Veri Kümesini okunacak 
		   //	c[0] = "Data/TestSamples.txt";
		   //	std::ifstream file;
		   //	int num, Dim, label;
		   //	file.open(c[0]);
		   //	if (file.is_open()) {
		   //		file >> Dim >> num;
		   //		textBox1->Text +="\r\n"+ "Test Samples:" +"\r\n" + "Dimension: " + Convert::ToString(Dim) + " numClass: " + Convert::ToString(num) + "\r\n";
		   //		//Set network values
		   //		numClass = num;
		   //		inputDim = Dim;
		   //		numTestSample = 0;
		   //		float* x = new float[inputDim];
		   //		while (!file.eof())
		   //		{
		   //			if (numTestSample == 0) { //ilk örnek için sadece
		   //				numTestSample = 1;
		   //				testData = new float[inputDim]; tag = new float[numTestSample];
		   //				for (int i = 0; i < inputDim; i++)
		   //					file >> testData[i];
		   //				file >> tag[0];
		   //			}
		   //			else {
		   //
		   //				for (int i = 0; i < inputDim; i++)
		   //					file >> x[i];
		   //				file >> label;
		   //				if (!file.eof()) {
		   //					numTestSample++;
		   //					testData = Add_Data(testData, numTestSample, x, inputDim);
		   //					tag = Add_Labels(tag, numTestSample, label);
		   //				}
		   //			}//else
		   //		} //while
		   //		delete[]x;
		   //		file.close();
		   //		for (int i = 0; i < numTestSample; i++) {
		   //			for (int j = 0; j < inputDim; j++)
		   //				textBox1->Text += Convert::ToString(testData[i * inputDim + j]) + " ";
		   //			textBox1->Text += Convert::ToString(tag[i]) + "\r\n";
		   //		}
		   //		//draw_sample(temp_x, temp_y, label);
		   //		label1->Text = "Samples Count: " + System::Convert::ToString(numTestSample);
		   //		MessageBox::Show("Dosya basari ile okundu");
		   //	}//file.is_open
		   //	else MessageBox::Show("Test Samples icin Dosya acilamadi");
		   //	delete[]c;
		   //	/*		float* normalizedTestData = Batch_Norm(testData, numTestSample, inputDim, mean, variance, false);
		   //			int* tag_int = new int[numTestSample];
		   //			for (int i = 0; i < numTestSample; i++)
		   //				tag_int[i] = tag[i];
		   //
		   //			model->Test(normalizedTestData, tag_int, numTestSample);
		   //			for (int i = 0; i < numTestSample; i++)
		   //			{
		   //				textBox1->Text += Convert::ToString(i + 1) + ". Sample Prediction is --> ";
		   //				textBox1->Text += Convert::ToString(tag[i]) + "\r\n";
		   //			}
		   //
		   //			delete[] tag_int;
		   //			delete[] normalizedTestData;*/
		   //}
	};
}

