#include "../Header/stdafx.h"
#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>
using namespace std;

#include "../Header/neuralnetwork.h"

NeuralNetwork::NeuralNetwork(const vector<int>& layers, const Matrix& outMat, const double& scl){
	netDef = layers;
	expectedOut = outMat;
	for (size_t i = 1; i < netDef.size(); i++){
		Matrix temp(netDef.at(i - 1), netDef.at(i));
		temp.fillRandom();
		weightMatricies.push_back(temp);
	}
	scalar = scl;
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

Matrix NeuralNetwork::forward(const Matrix& inMat){
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

Matrix NeuralNetwork::costFunc(){
	return pow(expectedOut - history.top(), 2);
}

void NeuralNetwork::costFuncPrime(){
	Matrix temp;
	temp = -(expectedOut - history.top());//works
	history.pop();
	temp = (temp * activation(history.top(), 1));//works
	history.pop();
	weightChanges.push_back(dotMatrices(history.top().transpose(), temp));//works
	history.pop();
	for (int i = netDef.size() - 3; i >= 0; i--){
		temp = (dotMatrices(temp, weightChanges.at(i).transpose()) * activation(history.top(), 1));//works
		history.pop();
		weightChanges.push_back(dotMatrices(history.top().transpose(), temp));//works
		history.pop();
	}
}

void NeuralNetwork::addToWeightMatricies(){
	for (size_t i = 0; i < weightMatricies.size(); i++){
		weightMatricies.at(i) = (weightMatricies.at(i) - (weightChanges.back() * scalar)); //works
		weightChanges.pop_back();
	}
}

void NeuralNetwork::backProp(){
	costFuncPrime();
	addToWeightMatricies();
}


