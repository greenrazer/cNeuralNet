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
	vector<int> v { 2, 3, 1 };
	Matrix in(4, 2);
	in.inputData();
	Matrix out(4, 1);
	out.inputData();
	NeuralNetwork NN(v,in,out);
	cout << NN.forward().toString() << endl;
	NN.costFuncPrime();
	int a;
	cin >> a;
}

