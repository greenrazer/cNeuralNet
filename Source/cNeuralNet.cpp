// Author: Kyle Birnbaum
// 12/29/2016
// cNeuralNet.cpp : Defines the entry point for the console application.

#include "../Header/stdafx.h"
#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>
#include <time.h>
using namespace std;

#include "../Header/neuralnetwork.h"

int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(0));

	vector<vector<double>> anInput {
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 1 },
		{ 0, 0, 1, 0 },
		{ 0, 0, 1, 1 },
		{ 0, 1, 0, 0 },
		{ 0, 1, 0, 1 },
		{ 0, 1, 1, 0 },
		{ 0, 1, 1, 1 },
		{ 1, 0, 0, 0 },
		{ 1, 0, 0, 1 },
		{ 1, 0, 1, 0 },
		{ 1, 0, 1, 1 },
		{ 1, 1, 0, 0 },
		{ 1, 1, 0, 1 },
		{ 1, 1, 1, 0 },
		{ 1, 1, 1, 1 },
	};

	vector<vector<double>> anOutput {
		{ 0, 0, 0, 1 },
		{ 0, 0, 1, 0 },
		{ 0, 0, 1, 1 },
		{ 0, 1, 0, 0 },
		{ 0, 1, 0, 1 },
		{ 0, 1, 1, 0 },
		{ 0, 1, 1, 1 },
		{ 1, 0, 0, 0 },
		{ 1, 0, 0, 1 },
		{ 1, 0, 1, 0 },
		{ 1, 0, 1, 1 },
		{ 1, 1, 0, 0 },
		{ 1, 1, 0, 1 },
		{ 1, 1, 1, 0 },
		{ 1, 1, 1, 1 },
		{ 0, 0, 0, 0 },
	};
	vector<int> networkDefinition { 4, 5, 4 };
	Matrix in(16, 4);
	Matrix out(16, 4);
	in.inputData(anInput);
	cout << endl;
	out.inputData(anOutput);
	in.scale();
	out.scale();
	NeuralNetwork NN(networkDefinition);
	cout << endl << endl << endl;
	int a = 1;
	while (a == 1 || a == 2){
		NN.train(in, out, 100);
		cout << NN.forward(in).toString(a==2) << endl;
		cin >> a;
	}
}

