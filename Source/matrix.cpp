#include "../Header/stdafx.h"
#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>
using namespace std;

#include "../Header/matrix.h"

double** Matrix::make2dArray(int hei, int wid){
	double** temp = 0;
	temp = new double*[hei];
	for (int h = 0; h < hei; h++)
	{
		temp[h] = new double[wid];
		for (int w = 0; w < wid; w++)
		{
			// fill in some initial values
			temp[h][w] = 0.0;
		}
	}
	return temp;
}

double* Matrix::at(int x, int y){
	if (x < 0 || y < 0 || x > height - 1 || y > width - 1){
		throw invalid_argument("index out of bounds for matrix: " + dimensions());
	}
	return &mat[x][y];
}

void Matrix::inputData(){
	for (int x = 0; x < height; x++){
		for (int y = 0; y < width; y++){
			cin >> mat[x][y];
		}
	}
	cout << toString();
}

string Matrix::toString(){
	string output = "";
	for (int x = 0; x < height; x++){
		output += "[ ";
		for (int y = 0; y < width; y++){
			output += to_string(mat[x][y]);
			output += " ";
		}
		output += "]\n";
	}
	return output;
}

string Matrix::dimensions(){
	return to_string(height) + "x" + to_string(width);
}

void Matrix::fillRandom(){
	double d = 1/(sqrt(width));
	double rnd;
	for (int x = 0; x < height; x++){
		for (int y = 0; y < width; y++){
			rnd = -d + ((2*d) * rand()) / (RAND_MAX + 1.0);
			mat[x][y] = rnd;
		}
	}
}

void Matrix::scale(){
	double max = mat[0][0];
	for (int x = 0; x < height; x++){
		for (int y = 0; y < width; y++){
			if (mat[x][y] > max){
				max = mat[x][y];
			}
		}
	}
	for (int x = 0; x < height; x++){
		for (int y = 0; y < width; y++){
			mat[x][y] /= max;
		}
	}
}

Matrix Matrix::transpose(){
	double** temp = make2dArray(width, height);
	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			temp[j][i] = mat[i][j];
		}
	}
	mat = temp;
	int save = height;
	height = width;
	width = save;
	return *this;
}

Matrix::Matrix(int h, int w){
	height = h;
	width = w;
	mat = make2dArray(height, width);
}

Matrix::Matrix(){

}

Matrix Matrix::operator*(Matrix& b) {
	return doOperatorFunction("*", b);
}

Matrix Matrix::operator+(Matrix& b) {
	return doOperatorFunction("+", b);
}

Matrix Matrix::operator-(Matrix& b) {
	return doOperatorFunction("-", b);
}

Matrix Matrix::operator-() {
	Matrix out(height, width);
	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			*out.at(i, j) = 0 - *at(i, j);
		}
	}
	return out;
}

Matrix Matrix::doOperatorFunction(string anOper, Matrix& b){
	if (width != b.width || height != b.height){
		throw invalid_argument("matrices not compatible for multiplication: " + dimensions() + " & " + b.dimensions());
	}
	Matrix out(height, width);
	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			if (anOper == "-"){
				*out.at(i, j) = *at(i, j) - *b.at(i, j);
			}
			else if (anOper == "+"){
				*out.at(i, j) = *at(i, j) + *b.at(i, j);
			}
			else if (anOper == "*"){
				*out.at(i, j) = *at(i, j) * *b.at(i, j);
			}
		}
	}
	return out;
}

Matrix dotMatrices(Matrix a, Matrix b)
	if (a.width != b.height){
		cout << "matrices not compatible for dot multiplication: " + a.dimensions() + " & " + b.dimensions();
		throw invalid_argument("matrices not compatible for dot multiplication: " + a.dimensions() + " & " + b.dimensions());
	}
	Matrix out(a.height, b.width);
	for (int i = 0; i < a.height; i++){
		for (int j = 0; j < b.width; j++){
			for (int q = 0; q < a.width; q++){
				*out.at(i, j) = *a.at(i, q) * *b.at(q, j);
			}
		}
	}
	return out;
}

//Matrix operator+(const Matrix&);