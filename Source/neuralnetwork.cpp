// Author: Kyle Birnbaum
// 12/29/2016

#include "../Header/stdafx.h"
#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>
using namespace std;

#include "../Header/neuralnetwork.h"

// CONSTRUCTOR

// @param {vector<int>} layers - network definition (e.g. {2, 3, 1} would be a network with 2 nodes
//													 in its input layer, 3 nodes in its hidden
//													 layer, and one node in its output
//@param {Matrix} outMat - the output matrix for
NeuralNetwork::NeuralNetwork(const vector<int>& layers){
	netDef = layers;
	for (size_t i = 1; i < netDef.size(); i++){
		Matrix temp(netDef.at(i - 1), netDef.at(i));
		temp.fillRandom();
		weightMatricies.push_back(temp);
	}
}

double NeuralNetwork::sigmoidPrime(const double& z){
	return sigmoid(z) * (1 - sigmoid(z));
}

double NeuralNetwork::sigmoid(const double& z){
	return 1 / (1 + exp(-z));
}

Matrix NeuralNetwork::activation(const Matrix& x, int activate = 0){
	Matrix temp(x.height, x.width);
	double bias = 3;
	for (int i = 0; i < temp.height; i++){
		for (int j = 0; j < temp.width; j++){
			*temp.at(i, j) = ((activate == 0) ? sigmoid(x.get(i, j)+bias) : sigmoidPrime(x.get(i, j)+bias));
		}
	}
	return temp;
}

void NeuralNetwork::clearHistory(){
	while (history.size() != 0){
		history.pop();
	}
}

Matrix NeuralNetwork::forward(const Matrix& inMat){
	clearHistory();
	if (netDef.front() != inMat.width){
		throw invalid_argument("Network definition doesn't match input matrix");
	}
	history.push(inMat);
	history.push(dotMatrices(history.top(), weightMatricies.at(0)));
	history.push(activation(history.top()));
	for (size_t i = 1; i < weightMatricies.size(); i++){
		history.push(dotMatrices(history.top(), weightMatricies.at(i)));
		history.push(activation(history.top()));
	}
	return history.top();
}

double NeuralNetwork::costFunc(const Matrix& outMat){
	Matrix temp = outMat;
	return (pow(temp - history.top(), 2) * .5).sumUp();
}

void NeuralNetwork::costFuncPrime(const Matrix& outMat){
	Matrix temp = outMat;
	temp = -(temp - history.top());
	history.pop();
	temp = (temp * activation(history.top(), 1));
	history.pop();
	weightChanges.push_back(dotMatrices(history.top().transpose(), temp));
	history.pop();
	int weightSize = weightMatricies.size() - 1;
	for (int i = 0; i < weightSize; i++){
		temp = dotMatrices(temp, weightMatricies.at(weightSize - i).transpose());
		temp = (temp * activation(history.top(), 1));
		history.pop();
		weightChanges.push_back(dotMatrices(history.top().transpose(), temp));
		history.pop();
	}
}

void NeuralNetwork::addToWeightMatricies(const double& scl){
	for (size_t i = 0; i < weightMatricies.size(); i++){
		weightMatricies.at(i) = (weightMatricies.at(i) - (weightChanges.back() * scl));
		weightChanges.pop_back();
	}
}

void NeuralNetwork::backProp(const Matrix& outMat, const double& scl){
	costFuncPrime(outMat);
	addToWeightMatricies(scl);
}

void NeuralNetwork::train(const Matrix& inMat, const Matrix& outMat, unsigned int times, const double& scl, bool showCost){
	for (int i = 0; i < times; i++){
		forward(inMat);
		if (showCost){
			cout << costFunc(inMat) << endl;
		}
		backProp(outMat, scl);
	}
}

vector<Matrix> NeuralNetwork::numGradCheck(const Matrix& inMat, const Matrix& outMat, const double& epsi, const double& scl){
	vector<Matrix> checkMatricies;
	forward(inMat);
	costFuncPrime(outMat);
	for (size_t i = 0; i < weightMatricies.size(); i++){
		Matrix& temp = weightMatricies.at(i);
		Matrix numGrad(temp.height, temp.width);
		for (int j = 0; j < temp.height; j++){
			for (int q = 0; q < temp.width; q++){
				*temp.at(j, q) += epsi;
				forward(inMat);
				double lossH = costFunc(outMat);

				*temp.at(j, q) -= (2* epsi);
				forward(inMat);
				double lossL = costFunc(outMat);

				*temp.at(j, q) += epsi;
				*numGrad.at(j, q) = (lossH - lossL) / (2*epsi);
			}
		}
		checkMatricies.push_back(numGrad);
		checkMatricies.push_back(weightChanges.at(weightChanges.size() - 1 - i));
	}
	addToWeightMatricies(3);
	return checkMatricies;
}


