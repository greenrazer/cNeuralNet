#include "../Header/matrix.h"

class NeuralNetwork{
	private:
		vector<int> netDef;
		vector<Matrix> weightMatricies;
		Matrix output, expectedOut;
		double sigmoid(double);
		void activation(Matrix&);
	public:
		NeuralNetwork(vector<int>, Matrix, Matrix);
		Matrix forward();

};