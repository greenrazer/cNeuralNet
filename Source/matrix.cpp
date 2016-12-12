#include "../Header/stdafx.h"
#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>
using namespace std;

#include "../Header/matrix.h"

void Matrix::makeInitArray(){
	mat = 0;
	mat = new double*[height];
	for (int h = 0; h < height; h++)
	{
		mat[h] = new double[width];
		for (int w = 0; w < width; w++)
		{
			// fill in some initial values
			mat[h][w] = 0.0;
		}
	}
}

double Matrix::at(int x, int y){
	return mat[x][y];
}

void Matrix::set(int x, int y, double z){
	mat[x][y] = z;
}

void Matrix::add(int x, int y, double z){
	mat[x][y] = z;
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

Matrix::Matrix(int h, int w){
	height = h;
	width = w;
	makeInitArray();
}

Matrix::Matrix(){

}

Matrix dotMatrices(Matrix a, Matrix b){
	if (a.width != b.height){
		throw invalid_argument("matrices not compatible for multiplication: " + a.dimensions() + " & " + b.dimensions());
	}
	Matrix out(a.height, b.width);
	for (int i = 0; i < a.height; i++){
		for (int j = 0; j < b.width; j++){
			for (int q = 0; q < a.width; q++){
				out.add(i, j, a.at(i, q) * b.at(q, j));
			}
		}
	}
	return out;
}