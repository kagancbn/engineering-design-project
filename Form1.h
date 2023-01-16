#pragma once
#pragma once
#include "Process.h"
#include <iostream>
#include <fstream>
#include <string>
#include "NeuralNetwork.h"

namespace Bitirme {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	/// <summary>
	/// Zusammenfassung für Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			srand(time(0));
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
		}
	protected:
		~Form1()
		{
			if (components)
			{
				delete components;
			}
			delete[] testData;
			delete[] tag;
			delete[] Samples;
			delete[] targets;
		}

	private:
		/// <summary>
		/// User Defined Variables
		int  numClass = 0, numSample = 0;
		int inputDim;
		float* Samples, * targets;
		ANN* model = new ANN;
		float* mean;
		float* variance;
		bool initialized = false;
		bool read_first = false;
		// test
		float* testData;		// x-y Coord              
		float* tag;					// Class tag
		int numTestSample;


	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::SaveFileDialog^ saveFileDialog1;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::ComboBox^ LayerCountBox;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::ComboBox^ TrainTypeBox;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart1;
	private: System::Windows::Forms::GroupBox^ groupBox3;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::ToolStripMenuItem^ fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ readDataToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ readWeightsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ saveWeightsToolStripMenuItem;



		   /// </summary>
		   System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code

		   void InitializeComponent(void)
		   {
			   System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			   System::Windows::Forms::DataVisualization::Charting::Legend^ legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			   System::Windows::Forms::DataVisualization::Charting::Series^ series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			   this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			   this->label5 = (gcnew System::Windows::Forms::Label());
			   this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			   this->label4 = (gcnew System::Windows::Forms::Label());
			   this->LayerCountBox = (gcnew System::Windows::Forms::ComboBox());
			   this->button1 = (gcnew System::Windows::Forms::Button());
			   this->label6 = (gcnew System::Windows::Forms::Label());
			   this->TrainTypeBox = (gcnew System::Windows::Forms::ComboBox());
			   this->label3 = (gcnew System::Windows::Forms::Label());
			   this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			   this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->readDataToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->readWeightsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->saveWeightsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			   this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			   this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			   this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			   this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			   this->button3 = (gcnew System::Windows::Forms::Button());
			   this->button2 = (gcnew System::Windows::Forms::Button());
			   this->groupBox1->SuspendLayout();
			   this->menuStrip1->SuspendLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			   this->groupBox3->SuspendLayout();
			   this->SuspendLayout();
			   // 
			   // groupBox1
			   // 
			   this->groupBox1->Controls->Add(this->label5);
			   this->groupBox1->Controls->Add(this->textBox2);
			   this->groupBox1->Controls->Add(this->label4);
			   this->groupBox1->Controls->Add(this->LayerCountBox);
			   this->groupBox1->Controls->Add(this->button1);
			   this->groupBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(162)));
			   this->groupBox1->Location = System::Drawing::Point(502, 51);
			   this->groupBox1->Name = L"groupBox1";
			   this->groupBox1->Size = System::Drawing::Size(220, 139);
			   this->groupBox1->TabIndex = 1;
			   this->groupBox1->TabStop = false;
			   this->groupBox1->Text = L"Network Architecture";
			   // 
			   // label5
			   // 
			   this->label5->AutoSize = true;
			   this->label5->Location = System::Drawing::Point(105, 46);
			   this->label5->Name = L"label5";
			   this->label5->Size = System::Drawing::Size(86, 26);
			   this->label5->TabIndex = 6;
			   this->label5->Text = L"Gizli Katman \r\nNöron Sayýlarý";
			   // 
			   // textBox2
			   // 
			   this->textBox2->Location = System::Drawing::Point(6, 55);
			   this->textBox2->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			   this->textBox2->Name = L"textBox2";
			   this->textBox2->Size = System::Drawing::Size(82, 20);
			   this->textBox2->TabIndex = 5;
			   this->textBox2->Text = L"4 4";
			   // 
			   // label4
			   // 
			   this->label4->AutoSize = true;
			   this->label4->Location = System::Drawing::Point(104, 21);
			   this->label4->Name = L"label4";
			   this->label4->Size = System::Drawing::Size(114, 13);
			   this->label4->TabIndex = 4;
			   this->label4->Text = L"Gizli Katman Sayýsý";
			   // 
			   // LayerCountBox
			   // 
			   this->LayerCountBox->FormattingEnabled = true;
			   this->LayerCountBox->Items->AddRange(gcnew cli::array< System::Object^  >(6) { L"2", L"3", L"4", L"5", L"6", L"7" });
			   this->LayerCountBox->Location = System::Drawing::Point(6, 19);
			   this->LayerCountBox->Name = L"LayerCountBox";
			   this->LayerCountBox->Size = System::Drawing::Size(82, 21);
			   this->LayerCountBox->TabIndex = 3;
			   this->LayerCountBox->Text = L"2";
			   // 
			   // button1
			   // 
			   this->button1->Location = System::Drawing::Point(39, 91);
			   this->button1->Name = L"button1";
			   this->button1->Size = System::Drawing::Size(131, 33);
			   this->button1->TabIndex = 2;
			   this->button1->Text = L"Network Setting";
			   this->button1->UseVisualStyleBackColor = true;
			   this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			   // 
			   // label6
			   // 
			   this->label6->AutoSize = true;
			   this->label6->Location = System::Drawing::Point(110, 19);
			   this->label6->Name = L"label6";
			   this->label6->Size = System::Drawing::Size(81, 13);
			   this->label6->TabIndex = 8;
			   this->label6->Text = L"Optimizasyon";
			   // 
			   // TrainTypeBox
			   // 
			   this->TrainTypeBox->FormattingEnabled = true;
			   this->TrainTypeBox->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"SGD", L"SGDwMomentum" });
			   this->TrainTypeBox->Location = System::Drawing::Point(10, 19);
			   this->TrainTypeBox->Name = L"TrainTypeBox";
			   this->TrainTypeBox->Size = System::Drawing::Size(82, 21);
			   this->TrainTypeBox->TabIndex = 7;
			   this->TrainTypeBox->Text = L"SGD";
			   // 
			   // label3
			   // 
			   this->label3->AutoSize = true;
			   this->label3->Location = System::Drawing::Point(802, 51);
			   this->label3->Name = L"label3";
			   this->label3->Size = System::Drawing::Size(0, 13);
			   this->label3->TabIndex = 3;
			   // 
			   // menuStrip1
			   // 
			   this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			   this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->fileToolStripMenuItem });
			   this->menuStrip1->Location = System::Drawing::Point(0, 0);
			   this->menuStrip1->Name = L"menuStrip1";
			   this->menuStrip1->Size = System::Drawing::Size(1443, 24);
			   this->menuStrip1->TabIndex = 4;
			   this->menuStrip1->Text = L"menuStrip1";
			   // 
			   // fileToolStripMenuItem
			   // 
			   this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				   this->readDataToolStripMenuItem,
					   this->readWeightsToolStripMenuItem, this->saveWeightsToolStripMenuItem
			   });
			   this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			   this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			   this->fileToolStripMenuItem->Text = L"File";
			   // 
			   // readDataToolStripMenuItem
			   // 
			   this->readDataToolStripMenuItem->Name = L"readDataToolStripMenuItem";
			   this->readDataToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			   this->readDataToolStripMenuItem->Text = L"Read_Data";
			   this->readDataToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::readDataToolStripMenuItem_Click);
			   // 
			   // readWeightsToolStripMenuItem
			   // 
			   this->readWeightsToolStripMenuItem->Name = L"readWeightsToolStripMenuItem";
			   this->readWeightsToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			   this->readWeightsToolStripMenuItem->Text = L"Read_Weights";
			   this->readWeightsToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::readWeightsToolStripMenuItem_Click);
			   // 
			   // saveWeightsToolStripMenuItem
			   // 
			   this->saveWeightsToolStripMenuItem->Name = L"saveWeightsToolStripMenuItem";
			   this->saveWeightsToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			   this->saveWeightsToolStripMenuItem->Text = L"Save_Weights";
			   this->saveWeightsToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::saveWeightsToolStripMenuItem_Click);
			   // 
			   // openFileDialog1
			   // 
			   this->openFileDialog1->FileName = L"openFileDialog1";
			   // 
			   // textBox1
			   // 
			   this->textBox1->Location = System::Drawing::Point(20, 50);
			   this->textBox1->Multiline = true;
			   this->textBox1->Name = L"textBox1";
			   this->textBox1->Size = System::Drawing::Size(424, 480);
			   this->textBox1->TabIndex = 5;
			   // 
			   // chart1
			   // 
			   chartArea1->Name = L"ChartArea1";
			   this->chart1->ChartAreas->Add(chartArea1);
			   legend1->Name = L"Legend1";
			   this->chart1->Legends->Add(legend1);
			   this->chart1->Location = System::Drawing::Point(464, 295);
			   this->chart1->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			   this->chart1->Name = L"chart1";
			   series1->ChartArea = L"ChartArea1";
			   series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			   series1->Legend = L"Legend1";
			   series1->Name = L"Error";
			   this->chart1->Series->Add(series1);
			   this->chart1->Size = System::Drawing::Size(602, 306);
			   this->chart1->TabIndex = 6;
			   this->chart1->Text = L"chart1";
			   // 
			   // groupBox3
			   // 
			   this->groupBox3->Controls->Add(this->button3);
			   this->groupBox3->Controls->Add(this->button2);
			   this->groupBox3->Controls->Add(this->label6);
			   this->groupBox3->Controls->Add(this->TrainTypeBox);
			   this->groupBox3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold));
			   this->groupBox3->Location = System::Drawing::Point(502, 195);
			   this->groupBox3->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			   this->groupBox3->Name = L"groupBox3";
			   this->groupBox3->Padding = System::Windows::Forms::Padding(2, 2, 2, 2);
			   this->groupBox3->Size = System::Drawing::Size(220, 83);
			   this->groupBox3->TabIndex = 7;
			   this->groupBox3->TabStop = false;
			   this->groupBox3->Text = L"Train";
			   // 
			   // button3
			   // 
			   this->button3->Location = System::Drawing::Point(117, 46);
			   this->button3->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			   this->button3->Name = L"button3";
			   this->button3->Size = System::Drawing::Size(99, 37);
			   this->button3->TabIndex = 10;
			   this->button3->Text = L"test";
			   this->button3->UseVisualStyleBackColor = true;
			   this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			   // 
			   // button2
			   // 
			   this->button2->Location = System::Drawing::Point(10, 46);
			   this->button2->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			   this->button2->Name = L"button2";
			   this->button2->Size = System::Drawing::Size(103, 37);
			   this->button2->TabIndex = 9;
			   this->button2->Text = L"Train";
			   this->button2->UseVisualStyleBackColor = true;
			   this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			   // 
			   // Form1
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(1443, 731);
			   this->Controls->Add(this->groupBox3);
			   this->Controls->Add(this->chart1);
			   this->Controls->Add(this->textBox1);
			   this->Controls->Add(this->label3);
			   this->Controls->Add(this->groupBox1);
			   this->Controls->Add(this->menuStrip1);
			   this->MainMenuStrip = this->menuStrip1;
			   this->Name = L"Form1";
			   this->Text = L"Form1";
			   this->groupBox1->ResumeLayout(false);
			   this->groupBox1->PerformLayout();
			   this->menuStrip1->ResumeLayout(false);
			   this->menuStrip1->PerformLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			   this->groupBox3->ResumeLayout(false);
			   this->groupBox3->PerformLayout();
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }
		   void readTestSamples() {
			   // Reading Test Samples
			   char** c = new char* [1];
			   // Veri Kümesini okunacak 
			   c[0] = "../Data/TestSamples.txt";
			   std::ifstream file;
			   int num, Dim, label;
			   file.open(c[0]);
			   if (file.is_open()) {
				   file >> Dim >> num;
				   textBox1->Text += "Dimension: " + Convert::ToString(Dim) + " numClass: " + Convert::ToString(num) + "\r\n";
				   //Set network values
				   numClass = num;
				   inputDim = Dim;
				   numTestSample = 0;
				   float* x = new float[inputDim];
				   while (!file.eof())
				   {
					   if (numTestSample == 0) { //ilk örnek için sadece
						   numTestSample = 1;
						   testData = new float[inputDim]; tag = new float[numTestSample];
						   for (int i = 0; i < inputDim; i++)
							   file >> testData[i];
					   }
					   else {

						   for (int i = 0; i < inputDim; i++)
							   file >> x[i];
						   file >> label;
						   if (!file.eof()) {
							   numTestSample++;
							   testData = Add_Data(testData, numTestSample, x, inputDim);
						   }
					   }//else
				   } //while
				   delete[]x;
				   file.close();
				   for (int i = 0; i < numTestSample; i++) {
					   for (int j = 0; j < inputDim; j++)
						   textBox1->Text += Convert::ToString(testData[i * inputDim + j]) + " ";
				   }
				   //draw_sample(temp_x, temp_y, label);
				   label3->Text = "Samples Count: " + System::Convert::ToString(numTestSample);
				   MessageBox::Show("Dosya basari ile okundu");
			   }//file.is_open
			   else MessageBox::Show("Dosya acilamadi");
			   delete[]c;
		   }
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		if (read_first == true) {
			//Input convertion
			const int LAYER_COUNT = Convert::ToInt32(LayerCountBox->Text);
			int* NEURON_COUNT = new int[LAYER_COUNT];

			array<String^>^ StringArray = textBox2->Text->Split(' ');

			for (int i = 0; i < LAYER_COUNT; i++)
				NEURON_COUNT[i] = Convert::ToInt32(StringArray[i]);

			//Network and layers are constructed;

			model->Init(LAYER_COUNT, NEURON_COUNT, inputDim, numClass);

			button1->Text = " Network is Ready : ";
		}
		else MessageBox::Show("Please read data first");
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		// Batch Normalization
		if (initialized == false)
		{
			mean = new float[inputDim];
			variance = new float[inputDim];
		}

		float* normalizedSamples = Batch_Norm(Samples, numSample, inputDim, mean, variance);
		// Training
		int cycle = 0;
		if (TrainTypeBox->Text == "SGD")
			cycle = model->TrainSGD(normalizedSamples, targets, numSample);
		else if (TrainTypeBox->Text == "SGDwMomentum")
			cycle = model->TrainSGDwMoment(normalizedSamples, targets, numSample);
		else
			MessageBox::Show("Wrong Train Type");

		if (cycle == 0) {
			MessageBox::Show("Eðitim yapýlamadý");
			cycle = CYCLE_MAX;
		}
		label3->Text += "   Cycle:" + System::Convert::ToString(cycle);

		// Plotting chart

		for (int c = 0; c < cycle; c++)
			if (c % 100 == 0)
				chart1->Series["Error"]->Points->AddXY((int)c, model->Error_arr[c]);

		// Drawing chart
		chart1->Refresh();

		delete[] normalizedSamples;
	}

	private: System::Void readDataToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		char** c = new char* [1];
		// Veri Kümesini okunacak 
		c[0] = "Data/Features.txt";
		std::ifstream file;
		int num, samplenum, Dim, label;
		file.open(c[0]);
		if (file.is_open()) {
			file >> Dim >> samplenum >> num;
			textBox1->Text += "Dimension: " + Convert::ToString(Dim) + " samplenum: "
				+ Convert::ToString(samplenum) + " numClass: " + Convert::ToString(num) + "\r\n";
			//Set network values
			numClass = num;
			inputDim = Dim;
			numSample = 0;
			float* x = new float[inputDim];
			while (!file.eof())
			{
				if (numSample == 0) { //ilk örnek için sadece
					numSample = 1;
					Samples = new float[inputDim]; targets = new float[numSample];
					for (int i = 0; i < inputDim; i++)
						file >> Samples[i];
					file >> targets[0];
				}
				else {
					for (int i = 0; i < inputDim; i++)
						file >> x[i];
					file >> label;
					if (!file.eof()) {
						numSample++;
						Samples = Add_Data(Samples, numSample, x, inputDim);
						targets = Add_Labels(targets, numSample, label);
					}
				}//else
			} //while
			delete[]x;
			file.close();
			for (int i = 0; i < numSample; i++) {
				for (int j = 0; j < inputDim; j++)
					textBox1->Text += Convert::ToString(Samples[i * inputDim + j]) + " ";
				textBox1->Text += Convert::ToString(targets[i]) + "\r\n";
			}
			//draw_sample(temp_x, temp_y, label);
			label3->Text = "Samples Count: " + System::Convert::ToString(numSample + 1);
			MessageBox::Show("Dosya basari ile okundu");
			read_first = true;
		}//file.is_open
		else MessageBox::Show("Dosya acilamadi");
		delete[]c;
	}//Read_Data

	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
		readTestSamples();
		//// Testing
		float* normalizedTestData = Batch_Norm(testData, numTestSample, inputDim, mean, variance, false);
		int* tag_int = new int[numTestSample];
		model->Test(normalizedTestData, tag_int, numTestSample);
		for (int i = 0; i < numTestSample; i++)
		{
			textBox1->Text += "\r\n" + Convert::ToString(i + 1) + ". Sample Prediction is --> ";
			textBox1->Text += Convert::ToString(tag_int[i]);
		}

		delete[] tag_int;
		delete[] normalizedTestData;
	}
	private: System::Void readWeightsToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		model->InitFromFile();
		char** c = new char* [1];
		// Veri Kümesini okunacak 
		c[0] = "Data/MeanVariance.txt";
		std::ifstream file;
		int num, samplenum, Dim, label;
		file.open(c[0]);
		if (file.is_open()) {
			file >> Dim >> num;
			mean = new float[Dim];
			variance = new float[Dim];
			inputDim = Dim;
			for (int d = 0; d < inputDim; d++)
				file >> mean[d];
			for (int d = 0; d < inputDim; d++)
				file >> variance[d];
			file.close();
			textBox1->Text += "\r\n" + "Means's Are:" + "\r\n";
			for (int j = 0; j < inputDim; j++)
				textBox1->Text += Convert::ToString(mean[j]) + " ";
			textBox1->Text += "\r\n" + "Varianve's Are:" + "\r\n";
			for (int j = 0; j < inputDim; j++)
				textBox1->Text += Convert::ToString(variance[j]) + " ";
			MessageBox::Show("Dosya basari ile okundu");
			initialized = true;
		}//file.is_open
		else MessageBox::Show("Dosya acilamadi");
		delete[]c;
	}
	private: System::Void saveWeightsToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		model->SaveWeights();
		char** c = new char* [1];
		// Veri Kümesi yazýlacak
		c[0] = "Data/MeanVariance.txt";
		std::ofstream ofs(c[0]);
		if (!ofs.bad()) {
			// Width,  Height, number of Class, data+label
			ofs << inputDim << " " << numClass << std::endl;
			for (int d = 0; d < inputDim; d++)
				ofs << mean[d] << " ";
			ofs << std::endl;
			for (int d = 0; d < inputDim; d++)
				ofs << variance[d] << " ";
		}
		ofs.close();
	}

	};
}
