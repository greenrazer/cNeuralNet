#include "../Header/stdafx.h"
#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>
using namespace std;

#include "../Header/neuralnetwork.h"

NeuralNetwork::NeuralNetwork(vector<int> layers, Matrix inMat, Matrix outMat){
	if (layers.front() != inMat.width){
		throw invalid_argument("Network definition doesn't match input matrix");
	}
	netDef = layers;
	weightMatricies.push_back(inMat);
	expectedOut = outMat;
	for (int i = 1; i < netDef.size(); i++){
		Matrix temp(netDef.at(i - 1), netDef.at(i));
		temp.fillRandom();
		weightMatricies.push_back(temp);
	}
}

double NeuralNetwork::sigmoid(double z){
	return 1 / (1 + exp(-z));
}

void NeuralNetwork::activation(Matrix &x){
	for (int i = 0; i < x.height; i++){
		for (int j = 0; j < x.width; j++){
			x.set(i, j, sigmoid(x.at(i, j)));
		}
	}

}

Matrix NeuralNetwork::forward(){
	Matrix temp = dotMatrices(weightMatricies.at(0), weightMatricies.at(1));
	activation(temp);
	for (int i = 2; i < weightMatricies.size(); i++){
		temp = dotMatrices(temp, weightMatricies.at(i));
		activation(temp);
	}
	output = temp;
	return temp;
}


