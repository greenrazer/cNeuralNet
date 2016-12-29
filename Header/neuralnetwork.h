#include "../Header/matrix.h"
#include <stack>

class NeuralNetwork{
	private:
		vector<int> netDef;
		vector<Matrix> weightMatricies, weightChanges;
		stack<Matrix> history;
		double scalar;
		Matrix output, expectedOut;
		double sigmoid(const double&);
		double sigmoidPrime(const double&);
		Matrix activation(const Matrix&, int);
		void costFuncPrime();
		void addToWeightMatricies();
	public:
		NeuralNetwork(const vector<int>&, const Matrix&, const double& = 3);
		Matrix forward(const Matrix& inMat);
		Matrix costFunc();
		void backProp();

};