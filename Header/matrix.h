class Matrix{
	private:
		double** mat;
		double** make2dArray(int, int);
		Matrix doOperatorFunction(string, const Matrix&);
		Matrix doOperatorFunction(string, const double&);

	public:
		int height, width;
		double* at(int, int);
		double get(int, int) const;
		void fillRandom();
		void inputData(const vector<vector<double>>&);
		void scale();
		string toString();
		string dimensions() const;
		Matrix transpose();
		Matrix operator+(const Matrix&);
		Matrix operator+(const double&);
		Matrix operator-(const Matrix&);
		Matrix operator-(const double&);
		Matrix operator-();
		Matrix operator*(const Matrix&);
		Matrix operator*(const double&);
		double sumUp();
		Matrix(int, int);
		Matrix();
};
Matrix dotMatrices(const Matrix&, const Matrix&);
Matrix pow(const Matrix&, const double&);