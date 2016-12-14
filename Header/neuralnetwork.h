#include "../Header/matrix.h"
#include <stack>

class NeuralNetwork{
	private:
		vector<int> netDef;
		vector<Matrix> weightMatricies, weightChanges;
		stack<Matrix> history;
		double scalar;
		Matrix output, expectedOut, input;
		double sigmoid(double);
		double sigmoidPrime(double);
		Matrix activation(Matrix, int);
		void costFuncPrime();
		void addToWeightMatricies();
	public:
		NeuralNetwork(vector<int>, Matrix, Matrix, double = 3);
		Matrix forward();
		void backProp();

};