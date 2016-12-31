// Author: Kyle Birnbaum
// 12/29/2016
// function comments in neuralnetwork.cpp

#include "../Header/matrix.h"
#include <stack>

class NeuralNetwork{
	private:
		vector<int> netDef;
		vector<Matrix> weightMatricies, weightChanges;
		stack<Matrix> history;
		double scalar;
		Matrix output;
		double sigmoid(const double&);
		double sigmoidPrime(const double&);
		Matrix activation(const Matrix&, int);
		void costFuncPrime(const Matrix&);
		void addToWeightMatricies(const double&);
		void clearHistory();
	public:
		NeuralNetwork(const vector<int>&);
		Matrix forward(const Matrix&);
		Matrix costFunc(const Matrix&);
		void backProp(const Matrix&, const double& = 3);
		vector<Matrix> numGradCheck(const Matrix&, const Matrix&, const double& = 0.00001, const double& = 3);

};