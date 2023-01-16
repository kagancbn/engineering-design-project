#include "image.h"
#include "humoments.h"
#include "MyForm.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/include/stb_image.h"
#include <iostream>
#include <vector>
#include <fstream>

image load_image(const char* filename)
{
	int w, h, c;
	int channel = 3;
	//w = width, h = height, c = # 8 - bit components per pixel ...
	unsigned char* data = stbi_load(filename, &w, &h, &c, channel);// without OpenCV

	if (!data) {
		exit(EXIT_FAILURE);
	}

	image out;
	out.data = data;
	out.h = h;
	out.w = w;
	out.c = c;
	return out;
}//load_image

image make_empty_image(int w, int h, int c)
{
	int size = w * h * c;
	image out;
	out.data = new unsigned char[size];
	for (int i = 0; i < size; i++)
		out.data[i] = 255;
	out.h = h;
	out.w = w;
	out.c = c;
	return out;
}
image make_image(int w, int h, int c, unsigned char* data)
{
	image out;
	out.data = data;
	out.h = h;
	out.w = w;
	out.c = c;
	return out;
}
image rgb_to_gray(int w, int h, unsigned char* data)
{
	image out = make_empty_image(w, h, 1);

	int psw, psw1, bufpos = 0, bufpos1 = 0;
	psw = w * 3;
	psw1 = w;

	for (int row = 0; row < h; row++)
		for (int col = 0; col < w; col++) {
			bufpos = row * psw + col * 3;
			bufpos1 = row * psw1 + col;
			out.data[bufpos1] = (data[bufpos] * 0.299 + data[bufpos + 1] * 0.587 + data[bufpos + 2] * 0.114);
		}
	return out;
}
int** Histogram(image im) {
	int** hist = new int* [im.c];
	for (int i = 0; i < im.c; i++) // initializing each chanels 256 bit histogram array
		hist[i] = new int[256];

	for (int i = 0; i < im.c; i++)
		for (int j = 0; j < 256; j++)
			hist[i][j] = 0;

	int psw = im.w * im.c;
	int bufpos;
	for (int row = 0; row < im.h; row++)
		for (int col = 0; col < im.w; col++) {
			bufpos = row * psw + col * im.c;
			for (int i = 0; i < im.c; i++) {
				int k = (int)im.data[bufpos + i];
				hist[i][k]++;
			}
		}
	return hist;
}
image Erosion(image im)
{
	image out = make_empty_image(im.w + 2, im.h + 2, im.c);

	for (int row = 0; row < im.h; row++)
		for (int col = 0; col < im.w; col++) {
			out.data[(row + 1) * (im.w + 2) + col + 1] = im.data[row * im.w + col];
		}

	for (int row = 0; row < im.h; row++)
		for (int col = 0; col < im.w; col++) {
			int psw = row * im.w + col; // binary image position
			int outPos = (row + 1) * (im.w + 2) + col + 1; // paddedLabeledImage matrix position

			if (out.data[outPos] == 255)
				if (out.data[outPos - (im.w + 2) - 1] == 255 &&
					out.data[outPos - (im.w + 2)] == 255 &&
					out.data[outPos - (im.w + 2) + 1] == 255 &&
					out.data[outPos - 1] == 1 &&
					out.data[outPos + 1] == 1 &&
					out.data[outPos + (im.w + 2) - 1] == 255 &&
					out.data[outPos + (im.w + 2)] == 255 &&
					out.data[outPos + (im.w + 2) + 1] == 255)
					im.data[psw] = 0;
				else
					im.data[psw] = 255;
		}
	//delete out
	return im;
}
image Dilation(image im)
{
	image out = make_empty_image(im.w + 2, im.h + 2, im.c);

	for (int row = 0; row < im.h; row++)
		for (int col = 0; col < im.w; col++) {
			out.data[(row + 1) * (im.w + 2) + col + 1] = im.data[row * im.w + col];
		}

	for (int row = 0; row < im.h; row++)
		for (int col = 0; col < im.w; col++) {
			int psw = row * im.w + col; // binary image position
			int outPos = (row + 1) * (im.w + 2) + col + 1; // paddedLabeledImage matrix position

			if (out.data[outPos] == 255)
			{
				im.data[psw - im.w - 1] = 255;
				im.data[psw - im.w] = 255;
				im.data[psw - im.w + 1] = 255;
				im.data[psw - 1] = 255;
				im.data[psw + 1] = 255;
				im.data[psw + im.w - 1] = 255;
				im.data[psw + im.w] = 255;
				im.data[psw + im.w + 1] = 255;
			}
			else
				im.data[psw] = 0;
		}
	//delete out
	return im;
}

image gray_to_binary_image(image im, int* T_values) {

	if(T_values[1]>T_values[0])
		for (int i = 0; i < im.w * im.h; i++)
		{
			int distance = labs(im.data[i] - T_values[1]);
			if (distance < labs(im.data[i] - T_values[0]))
				im.data[i] = 255;// beyaz
			else
				im.data[i] = 0;//siyah
		}
	else
		for (int i = 0; i < im.w * im.h; i++)
		{
			int distance = labs(im.data[i] - T_values[1]);
			if (distance < labs(im.data[i] - T_values[0]))
				im.data[i] = 0;// beyaz
			else
				im.data[i] = 255;//siyah
		}

	return im;
}
image rgb_to_binary_image(image im, int* T_values, int T_num) {
	int psw = im.w * im.c;
	int bufpos;
	for (int row = 0; row < im.h; row++)
		for (int col = 0; col < im.w; col++)
		{
			bufpos = row * psw + col * im.c;
			int* pixel = new int[im.c];
			for (int i = 0; i < im.c; i++)
				pixel[i] = (int)im.data[bufpos + i];

			int temp_dist = Euclidean_distance(im.c, pixel, 0, T_values, 0); // pixelin ilk T deðerine olan uzaklýðýný ilk deðer olarak ata
			int temp_index = 0;;
			int distance;
			for (int j = im.c; j < T_num * im.c; j += im.c)
			{
				distance = Euclidean_distance(im.c, pixel, 0, T_values, j); // pixelin bütün T deðerlerine olan uzaklýðýna abak
				if (distance < temp_dist)
				{
					temp_dist = distance;
					temp_index = j; // Bu satýrda 2 den fazla T deðeri varsa o T deðerinin indisini bulmak amaçlandý
				}
				for (int i = 0; i < im.c; i++)
					im.data[bufpos + i] = T_values[temp_index + i]; // 0 yada 255 deðerini deðilde T intensity deðerini buffer a atamak
			}
		}
	return im;
}
image Smoothing(image input, int kernelSize)
{
	int out_w = (input.w - kernelSize + 1);
	int out_h = (input.h - kernelSize + 1);

	image out = make_empty_image(out_w, out_h, 1);

	int kernel3x[9] = { 1,2,1,
						2,4,2,
						1,2,1 };

	int kernel5x[25] = { 1,4,7,4,1,
						4,16,26,16,4,
						7,26,41,26,7,
						4,16,26,16,4,
						1,4,7,4,1 };
	int* kernel;
	int div;
	switch (kernelSize)
	{
	case 5:
		kernel = kernel5x;
		div = 273;
		break;
	default:
		kernel = kernel3x;
		div = 16;
		break;
	}

	for (int row = 0; row < out.h; row++)
		for (int col = 0; col < out.w; col++) {
			int sum = 0;
			for (int krow = 0; krow < kernelSize; krow++)
				for (int kcol = 0; kcol < kernelSize; kcol++) {

					sum += input.data[(row + krow) * input.w + (col + kcol)] * kernel[krow * kernelSize + kcol];
				}
			out.data[row * out.w + col] = (int)sum / div;
		}
	return out;
}
int* K_means(int** hist, int T_num, int c) {
	int* T_vals = new int[T_num * c];
	int* T_vals_temp = new int[T_num * c];
	int totalpix_val = 1;
	int means = 0;

	for (int i = 0; i < T_num * c; i++)
	{
		T_vals[i] = rand() % 256;
		T_vals_temp[i] = 0;
	}
	int* T_tagged = new int[256];

	for (int i = 0; i < 256; i++)
		T_tagged[i] = -1;

	while (true)
	{
		for (int i = 0; i < 256; i++)
		{
			int distance = 0;
			int temp_dist = Euclidean_distance(c, T_vals, 0, i);
			int temp_indx = 0;
			for (int j = c; j < T_num * c; j += c)
			{
				distance = Euclidean_distance(c, T_vals, j, i); // indis deðerine olan uzaklýðý ölçtük
				if (distance < temp_dist)
				{
					temp_dist = distance;
					temp_indx = j;
				}
				T_tagged[i] = temp_indx;
			}
		}
		int counter = 0;
		int newT_dist;

		for (int j = 0; j < T_num * c; j += c)
		{
			newT_dist = 0;
			for (int k = 0; k < c; k++)
			{
				for (int i = 0; i < 256; i++)
				{
					if (T_tagged[i] == j) {
						totalpix_val += hist[k][i];
						means += i * hist[k][i];
					}
				}
				means = means / totalpix_val;
				T_vals_temp[j + k] = T_vals[j + k];
				T_vals[j + k] = means;
				means = 0;
				totalpix_val = 1;
			}
			newT_dist = Euclidean_distance(c, T_vals, j, T_vals_temp, j);
			if (labs(newT_dist) == 0)
				counter++;
		}
		if (counter == T_num) {
			delete[] T_vals_temp;
			delete[] T_tagged;
			return T_vals;
		}
	}
}
int Euclidean_distance(int space_size, int* x, int buffer_x, int* y, int buffer_y) {
	// ilk parametre uzay boyutu,
	// ikinci parametre ilk Noktanýn tutulduðu dizi, üçüncü parametre ilk noktanýn kaçýncý indiste tutulduðu deðer
	// dördüncü parametre ikinci Noktanýn tutulduðu dizi, beþinci parametre ikinci noktanýn kaçýncý indiste tutulduðu deðer
	// Tek boyutlu dizilerde çalýþýlýldýðý için 5 parametreli fonksiyon oldu
	int distance = 0;
	int sum = 0;
	for (int i = 0; i < space_size; i++) // uzay boyutu kadar dizi de ilerle
		sum += pow(labs(x[buffer_x + i] - y[buffer_y + i]), 2);

	distance = sqrt(sum);
	return distance;
}
int Euclidean_distance(int space_size, int* x, int buffer_x, int y) {
	//Noktanýn herhangi bir intensity deðerine olan uzaklýðý
	int distance = 0;
	int sum = 0;
	for (int i = 0; i < space_size; i++)
		sum += pow(labs(x[buffer_x + i] - y), 2);

	distance = sqrt(sum);
	return distance;
}
float Euclidean_Distance(float* arr1, float* arr2, int size)
{
	float distance = 0;
	float sum = 0;
	for (int i = 0; i < size; i++)
		sum += pow((arr1[i] - arr2[i]), 2);

	distance = sqrt(sum);
	return distance;
}
int* Connectivity(image im) {//8 komþu deðere göre connectivity

	int* tagged_data = new int[im.w * im.h];
	int* collision = new int[im.w * im.h];
	int psw = im.w;
	for (int i = 0; i < im.w * im.h; i++)
	{
		tagged_data[i] = 0;
		collision[i] = 0;
	}
	int counter = 2;
	for (int row = 1; row < im.h; row++)
		for (int col = 0; col < im.w; col++)
		{
			int bufpos = row * psw + col;
			int bufpos_rowup = (row - 1) * psw + col;
			if (im.data[bufpos] == 255) {
				if (col >= 1 && col + 1 <= im.w) // sýnýr deðerleri
				{
					int temp[4] = { 0,0,0,0 };
					temp[0] = tagged_data[bufpos_rowup - 1];
					temp[1] = tagged_data[bufpos_rowup];
					temp[2] = tagged_data[bufpos_rowup + 1];
					temp[3] = tagged_data[bufpos - 1];

					if (!(temp[0] || temp[1] || temp[2] || temp[3]))
						//komþularýndan etiket alan yoksa yeni deðer
					{
						tagged_data[bufpos] = counter; // yeni deðer
						counter++;
					}
					//else if((temp[0]==temp[1]==temp[2]==temp[3]) && temp [0] != 0)// komþularýnýn hepsi ayný deðerse 
					//{
					//	tagged_data[bufpos] = temp[0]; // tekdeðer
					//}
					else
					{
						int count = 0;
						int val = 0;
						for (int i = 0; i < 4; i++)
						{
							if (temp[i] != 0) val = temp[i];
						}
						for (int i = 0; i < 4; i++)
						{
							if ((temp[i] != 0) && (temp[i] != val) && (val != 0)) count++;//collision varsa counter i arttýr
						}
						if (count == 0) { // tek deðer alan komþu varsa o deðeri ata
							tagged_data[bufpos] = val;// tek deðer
						}
						else {
							int min_val = val;
							for (int i = 0; i < 4; i++)
							{
								if (temp[i] != 0 && min_val >= temp[i])  min_val = temp[i];
							}
							tagged_data[bufpos] = min_val; // küçük deðeri ata
							collision[bufpos] = 1;;// ikinci iterasyonda collision olan deðerler den büyük olanýn tüm deðerlerini küçük olana çevir
						}
					}
				}
			}
		}
	int num = 0;
	for (int i = 0; i < im.w * im.h; i++)
	{
		if (collision[i] == 1) {
			num++;
		}
	}
	num = 0;
	for (int row = im.h - 1; row > 1; --row)
	{
		for (int col = im.w - 1; col > 0; --col)
		{
			int bufpos = row * psw + col;
			int bufpos_rowup = (row - 1) * psw + col;
			if (collision[bufpos] == 1) {
				num++;
				if (col >= 1 && col + 1 <= im.w) // sýnýr deðerleri
				{
					int temp[4] = { 0,0,0,0 };
					temp[0] = tagged_data[bufpos_rowup - 1];
					temp[1] = tagged_data[bufpos_rowup];
					temp[2] = tagged_data[bufpos_rowup + 1];
					temp[3] = tagged_data[bufpos - 1];

					int count = 0;
					int val = 0;
					for (int i = 0; i < 4; i++)
					{
						if (temp[i] != 0 && temp[i] > val) val = temp[i];
					}
					for (int i = 0; i < 4; i++)
					{
						if ((temp[i] != 0) && (temp[i] != val) && (val != 0)) {
							count++;
						} //collision varsa counter i arttýr
					}
					if (count != 0) { // tek deðer alan komþu varsa o deðeri ata
						int min_val = val;
						for (int i = 0; i < 4; i++)
						{
							if (temp[i] != 0 && min_val >= temp[i])  min_val = temp[i];
						}
						int z = 0;
						while (z < im.w * im.h) {
							if (tagged_data[z] == val)//Eðer bütün pikseller içerisinden collisiondaki büyük deðer varsa
							{
								tagged_data[z] = min_val;// küçük deðeri ata
							}
							z++;
						}
					}
				}
			}
		}
	}
	delete[] collision;
	return tagged_data;
}
Boxes* bounding_box(int* tagged_data, image im) {
	int counter = 5000;//
	int psw = im.w;
	int a = 0;
	int* area_obj = new int[counter];
	for (int i = 0; i < counter; i++)
		area_obj[i] = 0;

	while (a < im.w * im.h)
	{
		if (tagged_data[a] != 0)
		{
			area_obj[tagged_data[a]]++;
		}
		a++;
	}
	int countobjts = 0;
	int* objects = new int[counter];
	for (int i = 0; i < counter; i++)
	{
		if (area_obj[i] > 100) {
			objects[countobjts] = i;
			countobjts++;
		}
	}
	int flag = 0;
	int top = 0, bottom = 0, left = 4000, right = 0;
	Boxes* Bounding = new Boxes[countobjts];
	Bounding->obj_num = countobjts;
	for (int i = 0; i < countobjts; i++)
	{
		int bufpos;
		for (int row = 0; row < im.h; row++)
		{
			for (int col = 0; col < im.w; col++)
			{
				bufpos = psw * row + col;
				if (tagged_data[bufpos] == objects[i])
				{
					if (flag == 0) {//first row is top
						top = row;
						flag++;
					}
					if (col < left)left = col;
					if (col > right) right = col;
					if (row > bottom) bottom = row;
				}
			}
		}
		Bounding[i].top = top;
		Bounding[i].bottom = bottom;
		Bounding[i].right = right;
		Bounding[i].left = left;
		top = 0;
		bottom = 0;
		right = 0;
		left = 4000;
		flag = 0;
	}
	delete[] area_obj;
	delete[] objects;
	return Bounding;
}
image ConnectivityColor(image im) {//8 komþu deðere göre connectivity

	int* tagged_data = new int[im.w * im.h];
	int* collision = new int[im.w * im.h];
	int psw = im.w;
	for (int i = 0; i < im.w * im.h; i++)
	{
		tagged_data[i] = 0;
		collision[i] = 0;
	}
	int counter = 2;
	for (int row = 1; row < im.h; row++)
	{
		for (int col = 0; col < im.w; col++)
		{
			int bufpos = row * psw + col;
			int bufpos_rowup = (row - 1) * psw + col;
			if (im.data[bufpos] == 255) {
				if (col >= 1 && col + 1 <= im.w) // sýnýr deðerleri
				{
					int temp[4] = { 0,0,0,0 };
					temp[0] = tagged_data[bufpos_rowup - 1];
					temp[1] = tagged_data[bufpos_rowup];
					temp[2] = tagged_data[bufpos_rowup + 1];
					temp[3] = tagged_data[bufpos - 1];

					if (!(temp[0] || temp[1] || temp[2] || temp[3]))
						//komþularýndan etiket alan yoksa yeni deðer
					{
						tagged_data[bufpos] = counter; // yeni deðer
						counter++;
					}
					//else if((temp[0]==temp[1]==temp[2]==temp[3]) && temp [0] != 0)// komþularýnýn hepsi ayný deðerse 
					//{
					//	tagged_data[bufpos] = temp[0]; // tekdeðer
					//}
					else
					{
						int count = 0;
						int val = 0;
						for (int i = 0; i < 4; i++)
						{
							if (temp[i] != 0) val = temp[i];
						}
						for (int i = 0; i < 4; i++)
						{
							if ((temp[i] != 0) && (temp[i] != val) && (val != 0)) count++;//collision varsa counter i arttýr
						}
						if (count == 0) { // tek deðer alan komþu varsa o deðeri ata
							tagged_data[bufpos] = val;// tek deðer
						}
						else {
							int min_val = val;
							for (int i = 0; i < 4; i++)
							{
								if (temp[i] != 0 && min_val >= temp[i])  min_val = temp[i];
							}
							tagged_data[bufpos] = min_val; // küçük deðeri ata
							collision[bufpos] = 1;;// ikinci iterasyonda collision olan deðerler den büyük olanýn tüm deðerlerini küçük olana çevir
						}
					}
				}
			}
		}
	}
	int num = 0;
	for (int i = 0; i < im.w * im.h; i++)
	{
		if (collision[i] == 1) {
			num++;
		}
	}
	num = 0;
	for (int row = im.h; row > 1; --row)
	{
		for (int col = im.w; col > 0; --col)
		{
			int bufpos = row * psw + col;
			int bufpos_rowup = (row - 1) * psw + col;
			if (collision[bufpos] == 1) {
				num++;
				if (col >= 1 && col + 1 <= im.w) // sýnýr deðerleri
				{
					int temp[4] = { 0,0,0,0 };
					temp[0] = tagged_data[bufpos_rowup - 1];
					temp[1] = tagged_data[bufpos_rowup];
					temp[2] = tagged_data[bufpos_rowup + 1];
					temp[3] = tagged_data[bufpos - 1];

					int count = 0;
					int val = 0;
					for (int i = 0; i < 4; i++)
					{
						if (temp[i] != 0 && temp[i] > val) val = temp[i];
					}
					for (int i = 0; i < 4; i++)
					{
						if ((temp[i] != 0) && (temp[i] != val) && (val != 0)) {
							count++;
						} //collision varsa counter i arttýr
					}
					if (count != 0) { // tek deðer alan komþu varsa o deðeri ata
						int min_val = val;
						for (int i = 0; i < 4; i++)
						{
							if (temp[i] != 0 && min_val >= temp[i])  min_val = temp[i];
						}
						int z = 0;
						while (z < im.w * im.h) {
							if (tagged_data[z] == val)//Eðer bütün pikseller içerisinden collisiondaki büyük deðer varsa
							{
								tagged_data[z] = min_val;// küçük deðeri ata
							}
							z++;
						}
					}
				}
			}
		}
	}
	int a = 0;
	int* hist_obj = new int[counter];
	for (int i = 0; i < counter; i++)
	{
		hist_obj[i] = 0;
	}
	while (a < im.w * im.h)
	{
		if (tagged_data[a] != 0)
		{
			hist_obj[tagged_data[a]]++;
		}
		a++;
	}
	int countobjts = 0;
	int* objects = new int[counter];
	for (int i = 0; i < counter; i++)
	{
		if (hist_obj[i] > 5) {
			objects[countobjts] = i;
			countobjts++;
		}
	}
	int flag = 0;
	int top = 0, bottom = 0, left = 1500, right = 0;
	for (int i = 0; i < countobjts; i++)
	{
		int bufpos;
		for (int row = 0; row < im.h; row++)
		{
			for (int col = 0; col < im.w; col++)
			{
				bufpos = psw * row + col;
				if (tagged_data[bufpos] == objects[i])
				{
					if (flag == 0) {
						top = row;
						flag++;
					}
					if (col < left)left = col;
					if (col > right) right = col;
					if (row > bottom) bottom = row;
				}
			}
		}
		top = 0;
		bottom = 0;
		right = 0;
		left = 0;
		flag = 0;
	}

	image im_out = make_empty_image(im.w, im.h, 3);

	int bufpos1;
	int psw_rgb = im.w * 3;
	int bufpos_gray;
	srand((unsigned)time(NULL));
	for (int i = 0; i < counter; i++)
	{
		if (hist_obj[i] > 5)// Küçük nesneler için eleme
		{
			int rand_val = rand() % 256;
			for (int row = 0; row < im.h; row++)
			{
				for (int col = 0; col < im.w; col++)
				{
					bufpos1 = row * psw_rgb + col * im_out.c;
					bufpos_gray = row * psw + col;

					if (tagged_data[bufpos_gray] == i)
					{
						im_out.data[bufpos1] = rand_val;
						im_out.data[bufpos1 + 1] = rand_val;
						im_out.data[bufpos1 + 2] = rand_val;;
					}
				}
			}
		}
	}
	return im_out;
}
image Prediction(Boxes* Bounding, int* tagged_data, image im, ANN* model, float* mean, float* variance) {

	int psw = im.w;
	image im_out = make_empty_image(im.w, im.h, 3);
	for (int i = 0; i < Bounding->obj_num; i++)
	{
		int* obj_data = new int[(Bounding[i].bottom - Bounding[i].top + 1) * (Bounding[i].right - Bounding[i].left + 1)];
		int h = 0;
		for (int row = Bounding[i].top; row < Bounding[i].bottom; row++)
		{
			for (int col = Bounding[i].left; col < Bounding[i].right; col++)
			{
				obj_data[h] = tagged_data[psw * row + col];
				h++;
			}
		}
		HuMoments obje(obj_data, (Bounding[i].bottom - Bounding[i].top + 1), (Bounding[i].right - Bounding[i].left + 1));
		obje.calcOrgins();
		obje.calcInvariantMoments();
		obje.logTransform();
		float* moments = obje.getInvariantMoments();
		float* normalizedTestData = Batch_Norm(moments, 1, 7, mean, variance, false);
		int object;
		model->Test(normalizedTestData, object);
		int r, g, b;
		if (object == 0) { // mahsul

			r = 0;g = 255;b = 0;
		}
		else if (object == 1)// yabani ot 1
		{
			r = 255;g = 0;b = 0;
		}
		else if (object == 2) // yabani ot 2
		{
			r = 0;g = 0;b = 255;
		}
		printf("prediction is - > %d\n", object);
		int bufpos = 0;
		for (int row = Bounding[i].top; row < Bounding[i].bottom; row++)
			for (int col = Bounding[i].left; col < Bounding[i].right; col++)
			{
				bufpos = row * psw * 3 + col * 3;
				if (tagged_data[psw * row + col] != 0) {
					im_out.data[bufpos] = r;
					im_out.data[bufpos + 1] = g;
					im_out.data[bufpos + 2] = b;
				}
			}
		delete[] obj_data;
	}

	return im_out;
}
using namespace System::Windows::Forms;

void FeatureExtraction(Boxes* Bounding, int* tagged_data, int box_num, image im) {
	int featureDim = 7;
	char** c = new char* [1];
	// Veri Kümesi yazýlacak
	c[0] = "Data/Features.txt";
	std::ofstream ofs(c[0], std::ios_base::app);
	if (!ofs.bad()) {
		ofs << featureDim << " " << box_num << std::endl;
		int psw = im.w;
		for (int i = 0; i < box_num; i++)
		{
			int* obj_data = new int[(Bounding[i].bottom - Bounding[i].top + 1) * (Bounding[i].right - Bounding[i].left + 1)];
			int h = 0;
			for (int row = Bounding[i].top; row < Bounding[i].bottom; row++)
				for (int col = Bounding[i].left; col < Bounding[i].right; col++)
				{
					obj_data[h] = tagged_data[psw * row + col];// Burada Bounding box içindeki verini obj_data dizisine kopyalandý
					h++;
				}
			HuMoments obje(obj_data, (Bounding[i].bottom - Bounding[i].top + 1), (Bounding[i].right - Bounding[i].left + 1));
			obje.calcOrgins();
			obje.calcInvariantMoments();
			obje.logTransform();
			float* data = obje.getInvariantMoments();
			for (int d = 0; d < featureDim; d++)
				ofs << data[d] << " ";
			ofs << std::endl;
		}
		ofs.close();
		MessageBox::Show("Oznitelikler Dosyaya Yazildi");
	}
	else MessageBox::Show("Dosya acilamadi");
}