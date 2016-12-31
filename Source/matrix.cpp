// Author: Kyle Birnbaum
// 12/29/2016

#include "../Header/stdafx.h"
#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>
using namespace std;

#include "../Header/matrix.h"

//CONSTRUCTORS

// @param {int} h - height of matrix
// @param {int} w - width of matrix
// constuctor that makes an empty matrix of height h and widith w
Matrix::Matrix(int h, int w){
	height = h;
	width = w;
	mat = make2dArray(height, width);
}

// constuctor that creates a matrix with no data
Matrix::Matrix(){

}

// @param {Matrix} x -  doesnt change original matrix
// makes new matrix as a copy of another matrix
Matrix::Matrix(const Matrix& x){
	initMatrix(x);
}

//DESTRUCTOR

//clears matrix from memory
Matrix::~Matrix(){
	for (int x = 0; x < height; x++){
		delete[] mat[x];
	}
	delete[] mat;
}

//HELPER FUNCTIONS

// @param {int} hei - height of matrix
// @param {int} wed - width of matrix
// @return {double**} - 2d double array
// returns an array(size height) of arrays(size width) of doubles
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

// @param {Matrix} x - doesnt change original matrix
// sets up current instance of matrix to be the same as another matrix
void Matrix::initMatrix(const Matrix& x){
	height = x.height;
	width = x.width;
	mat = make2dArray(height, width);
	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			mat[i][j] = x.get(i, j);
		}
	}
}

//PUBLIC METHODS

// @param {int} x - height index
// @param {int} y - width index
// @return {double*} - pointer to double at x,y
// takes an x and y coord and  returns a pointer to the double at x,y
double* Matrix::at(int x, int y){
	if (x < 0 || y < 0 || x > height - 1 || y > width - 1){
		throw invalid_argument("index out of bounds for matrix: " + dimensions());
	}
	return &mat[x][y];
}

// @param {int} x - height index
// @param {int} y - width index
// @return {double} - read only double at x,y
// takes an x and y coord and returns the read only double at x,y
double Matrix::get(int x, int y) const{
	if (x < 0 || y < 0 || x > height - 1 || y > width - 1){
		throw invalid_argument("index out of bounds for matrix: " + dimensions());
	}
	return mat[x][y];
}

// @param {vector<vector<int>>} a - a vector of vectors to represent a matrix
// fills the matrix with input data from a vector of vectors of ints
void Matrix::inputData(const vector<vector<double>>& a){
		for (int x = 0; x < height; x++){
			for (int y = 0; y < width; y++){
					mat[x][y] = a.at(x).at(y);
			}
		}
	//cout << toString();
}

// @param {bool} r - whether to round to nearest integer or not default no
// @return {string} - matrix that can be printed to console
// return a readable version of the matrix as a string
string Matrix::toString(bool r){
	string output = "";
	for (int x = 0; x < height; x++){
		output += "[ ";
		for (int y = 0; y < width; y++){
			output += to_string(r ? round(mat[x][y]) : mat[x][y]);
			output += " ";
		}
		output += "]\n";
	}
	return output;
}

// @return {string} - dimentions of the matrix in a "{int} x {int}" format
// returns the dementions of the array in a string
string Matrix::dimensions() const{
	return to_string(height) + "x" + to_string(width);
}

// @param {double} d - random bound between +/- this number
// fills the current matrix with random values between +/- d
void Matrix::fillRandom(const double& d){
	//double bound = 4/(sqrt(width));
	double bound = d;
	for (int x = 0; x < height; x++){
		for (int y = 0; y < width; y++){
			mat[x][y] = -bound + ((2 * bound) * rand()) / (RAND_MAX + 1.0);
		}
	}
}

// @return {double} - max value in the matrix
//divides all the values in the matrix by the max value
double Matrix::scale(){
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
	return max;
}

// @return {Matrix} - transposed matrix
// transposes current matrix
Matrix Matrix::transpose(){
	Matrix temp(width, height);
	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			*temp.at(j, i) = mat[i][j];
		}
	}
	return temp;
}

// @return {double} - sum of all values in the matrix
// returns the sum of all values in the matrix
double Matrix::sumUp(){
	double out = 0;
	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			out += get(i, j);
		}
	}
	return out;
}

//OPERATOR FUNCTIONS

// makes this matrix equal to another matrix
Matrix& Matrix::operator=(const Matrix& x){
	initMatrix(x);
	return *this;
}

// returns a Matrix multiplied by a Matrix
Matrix Matrix::operator*(const Matrix& b) {
	return doOperatorFunction("*", b);
}

// returns a Matrix multiplied by a double
Matrix Matrix::operator*(const double& b) {
	return doOperatorFunction("*", b);
}

// returns a Matrix added to a Matrix
Matrix Matrix::operator+(const Matrix& b) {
	return doOperatorFunction("+", b);
}

// returns a Matrix added to a double
Matrix Matrix::operator+(const double& b) {
	return doOperatorFunction("+", b);
}

// returns a Matrix subtracted by a Matrix
Matrix Matrix::operator-(const Matrix& b) {
	return doOperatorFunction("-", b);
}

// returns a Matrix subtracted by a double
Matrix Matrix::operator-(const double& b) {
	return doOperatorFunction("-", b);
}

//negates all values in matrix
Matrix Matrix::operator-() {
	Matrix out(height, width);
	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			*out.at(i, j) = 0 - *at(i, j);
		}
	}
	return out;
}

//OPERATOR HELPERS

// @param {string} anOper - an operator (e.g. "+", "-", "*");
// @param {double} b - value to change matrix by
// @return {Matrix} - matrix that has been changed by value in some operation
// takes a value and does an operation to it
Matrix Matrix::doOperatorFunction(string anOper, const double& b){
	Matrix out(height, width);
	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			if (anOper == "-"){
				*out.at(i, j) = get(i, j) - b;
			}
			else if (anOper == "+"){
				*out.at(i, j) = get(i, j) + b;
			}
			else if (anOper == "*"){
				*out.at(i, j) = get(i, j) * b;
			}
		}
	}
	return out;
}

// @param {string} anOper - an operator (e.g. "+", "-", "*");
// @param {Matrix} b - Matrix to change Matrix by
// @return {Matrix} - matrix that has been changed by value in some operation
// takes a Matrix and does an operation to it by another Matrix
Matrix Matrix::doOperatorFunction(string anOper,const Matrix& b){
	if (width != b.width || height != b.height){
		cout << "matrices not compatible for \"" + anOper + "\": " + dimensions() + " & " + b.dimensions();
		throw invalid_argument("matrices not compatible for \"" + anOper + "\": " + dimensions() + " & " + b.dimensions());
	}
	Matrix out(height, width);
	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			if (anOper == "-"){
				*out.at(i, j) = get(i, j) - b.get(i, j);
			}
			else if (anOper == "+"){
				*out.at(i, j) = get(i, j) + b.get(i, j);
			}
			else if (anOper == "*"){
				*out.at(i, j) = get(i, j) * b.get(i, j);
			}
		}
	}
	return out;
}

//MATRIX FUNCTIONS NOT INSIDE MATRIX CLASS

// @param {Matrix} a - first matrix
// @param {Matrix} b - second matrix
// @return {Matrix} - the dot product of the first and second 
// takes the dot product of two matricies
Matrix dotMatrices(const Matrix& a, const Matrix& b){
	if (a.width != b.height){
		cout << "matrices not compatible for dot multiplication: " + a.dimensions() + " & " + b.dimensions();
		throw invalid_argument("matrices not compatible for dot multiplication: " + a.dimensions() + " & " + b.dimensions());
	}

	Matrix out(a.height, b.width);

	for (int i = 0; i < a.height; i++){
		for (int j = 0; j < b.width; j++){
			for (int q = 0; q < a.width; q++){
				*out.at(i, j) += a.get(i, q) * b.get(q, j);
			}
		}
	}
	return out;
}

// @param {Matrix} a - Matrix to change
// @param {double} num - value to raise Matrix to
// @return {Matrix} - matrix that has been raised to value
// takes a Matrix and raises all elements to some power
Matrix pow(const Matrix& a, const double& num){
	Matrix out(a.height, a.width);
	for (int i = 0; i < a.height; i++){
		for (int j = 0; j < a.width; j++){
			*out.at(i, j) = pow(a.get(i, j), num);
		}
	}
	return out;
}