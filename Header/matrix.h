class Matrix{
	private:
		double** mat;
		void makeInitArray();

	public:
		int height, width;
		double at(int, int);
		void set(int, int, double);
		void add(int, int, double);
		void fillRandom();
		void inputData();
		string toString();
		string dimensions();
		Matrix(int, int);
		Matrix();
};
Matrix dotMatrices(Matrix, Matrix);