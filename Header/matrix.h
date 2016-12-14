class Matrix{
	private:
		double** mat;
		double** make2dArray(int, int);
		Matrix doOperatorFunction(string, Matrix&);
		Matrix doOperatorFunction(string, double&);

	public:
		int height, width;
		double* at(int, int);
		void fillRandom();
		void inputData(vector<vector<double>>);
		void scale();
		string toString();
		string dimensions();
		Matrix transpose();
		Matrix operator+(Matrix&);
		Matrix operator+(double&);
		Matrix operator-(Matrix&);
		Matrix operator-(double&);
		Matrix operator-();
		Matrix operator*(Matrix&);
		Matrix operator*(double&);
		Matrix(int, int);
		Matrix();
};
Matrix dotMatrices(Matrix, Matrix);