// cNeuralNet.cpp : Defines the entry point for the console application.
//

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
	NeuralNetwork NN(networkDefinition,out,1);
	cout << endl << endl << endl;
	int a = 1;
	while (a == 1 || NN.costFunc().sumUp() > 5){
		for (int i = 0; i < 1000; i++){
			//cout << "forward" << endl << NN.forward(in).toString() << endl;
			NN.forward(in);
			cout << NN.costFunc().sumUp() << endl;
			NN.backProp();
		}
		cout << NN.forward(in).toString(true) << endl;
		cout << NN.forward(in).toString() << endl;
		cin >> a;
	}
}

