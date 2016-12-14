#include "../Header/stdafx.h"
#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>
using namespace std;

#include "../Header/neuralnetwork.h"

NeuralNetwork::NeuralNetwork(vector<int> layers, Matrix inMat, Matrix outMat, double scl){
	if (layers.front() != inMat.width){
		throw invalid_argument("Network definition doesn't match input matrix");
	}
	netDef = layers;
	inMat.scale();
	outMat.scale();
	input = inMat;
	history.push(inMat);
	expectedOut = outMat;
	for (int i = 1; i < netDef.size(); i++){
		Matrix temp(netDef.at(i - 1), netDef.at(i));
		temp.fillRandom();
		weightMatricies.push_back(temp);
	}
	scalar = scl;
}

double NeuralNetwork::sigmoidPrime(double z){
	return  exp(-z) / pow((1 + exp(-z)),2);
}

double NeuralNetwork::sigmoid(double z){
	return 1 / (1 + exp(-z));
}

Matrix NeuralNetwork::activation(Matrix x, int activate = 0){
	Matrix temp = x;
	for (int i = 0; i < temp.height; i++){
		for (int j = 0; j < temp.width; j++){
			*temp.at(i, j) = activate == 0 ? sigmoid(*temp.at(i, j)) : sigmoidPrime(*temp.at(i, j));
		}
	}
	return temp;
}

Matrix NeuralNetwork::forward(){
	history.push(dotMatrices(history.top(), weightMatricies.at(0)));
	history.push(activation(history.top()));
	for (int i = 1; i < weightMatricies.size(); i++){
		history.push(dotMatrices(history.top(), weightMatricies.at(i)));
		history.push(activation(history.top()));
	}
	output = history.top();
	return output;
}

void NeuralNetwork::costFuncPrime(){
	Matrix temp;
	temp = -(expectedOut - history.top());
	history.pop();
	temp = temp * activation(history.top(), 1);
	history.pop();
	weightChanges.push_back(dotMatrices(history.top().transpose(), temp));
	history.pop();
	for (int i = weightChanges.size() - 1; i >= 0; i--){
		temp = dotMatrices(temp, weightChanges.at(i).transpose()) * activation(history.top(), 0);
		history.pop();
		weightChanges.push_back(dotMatrices(history.top().transpose(), temp));
		history.pop();
	}
}

void NeuralNetwork::addToWeightMatricies(){
	cout << "assdmhaskl" << endl;
	for (int i = 0; i < weightMatricies.size(); i++){
		cout << weightMatricies.at(i).toString() << endl;
		weightMatricies.at(i) = weightMatricies.at(i) - (weightChanges.back() * scalar);
		weightChanges.pop_back();
	}
}

void NeuralNetwork::backProp(){
	costFuncPrime();
	addToWeightMatricies();
	history.push(input);
}


