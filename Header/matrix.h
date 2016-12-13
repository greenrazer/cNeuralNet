class Matrix{
	private:
		double** mat;
		double** make2dArray(int, int);
		Matrix doOperatorFunction(string, Matrix&);

	public:
		int height, width;
		double* at(int, int);
		void fillRandom();
		void inputData();
		void scale();
		string toString();
		string dimensions();
		Matrix transpose();
		Matrix operator+(Matrix&);
		Matrix operator-(Matrix&);
		Matrix operator-();
		Matrix operator*(Matrix&);
		Matrix(int, int);
		Matrix();
};
Matrix dotMatrices(Matrix, Matrix);