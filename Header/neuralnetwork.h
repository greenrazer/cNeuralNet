#include "../Header/matrix.h"
#include <stack>

class NeuralNetwork{
	private:
		vector<int> netDef;
		vector<Matrix> weightMatricies, weightChanges;
		stack<Matrix> history;
		Matrix output, expectedOut, input;
		double sigmoid(double);
		double sigmoidPrime(double);
		Matrix activation(Matrix, int);
	public:
		NeuralNetwork(vector<int>, Matrix, Matrix);
		Matrix forward();
		void costFuncPrime();

};