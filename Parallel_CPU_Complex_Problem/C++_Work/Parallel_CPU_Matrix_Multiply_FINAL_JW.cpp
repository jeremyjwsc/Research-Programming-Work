// Parallel_CPU_Matrix_Multiply_FINAL_JW.cpp : Defines the entry point for the console application.

#include <stdio.h>
#include <time.h>
#include <complex>     // std::complex, std::real, std::imag
#include <iostream>   // std::cout
#include <string>
#include <sstream>

typedef std::complex<double> TYPE;

//function identifier
void set_dimension(TYPE** &Matrix, size_t Dimension);
void set_random_value(TYPE** &Matrix, size_t Dimension, TYPE MaxRndVal_JW);
void display_matrix(TYPE** Matrix, size_t Dimension);
double matrix_multiplication(TYPE** MatrixA, TYPE** MatrixB, TYPE** &MatrixC, size_t Dimension);
double matrix_parallel_multiplication(TYPE** MatrixA, TYPE** MatrixB, TYPE** &MatrixC, size_t Dimension);

using namespace std;

std::string DimVal;

//Validate Dimension Value if number or string
bool check_DIM_number(std::string DimVal) {
   for (int i = 0; i < DimVal.length(); i++)
   if (isdigit(DimVal[i]) == false)
      return false;
      return true;
}

std::string RealVal;

//Validate Real Value if number or string
bool check_REAL_number(std::string RealVal) {
   for (int i = 0; i < RealVal.length(); i++)
   if (isdigit(RealVal[i]) == false)
      return false;
      return true;
}

std::string ImagVal;

//Validate Imaginary Value if number or string
bool check_IMAG_number(std::string ImagVal) {
   for (int i = 0; i < ImagVal.length(); i++)
   if (isdigit(ImagVal[i]) == false)
      return false;
      return true;
}

int main()
{
	TYPE** MatrixA = NULL;
	TYPE** MatrixB = NULL;
	TYPE** MatrixC = NULL;
	size_t Dimension = 0;
	double _real = 0;
	double _imag = 0;
	TYPE MaxRndVal_JW = 0;
	double Elapsed = 0;
	double ParallelElapsed = 0;
	
    cout << "Parallel CPU Matrix Multiply Program" << "\n";
    cout << "\n";
	cout << "Hello and Thank You For Your Time" << "\n";
    cout << "\n";
    cout << "To Begin: Enter Your Matrix Dimension and Complex Values" << "\n";
    
CHECK_DIM:
    cout << "\n";
    cout << "Enter Matrix Dimension (minimum 4): ";
    cin >> DimVal;
    if (check_DIM_number(DimVal)){
      goto START_DIM;
    }
    else{
      cout << DimVal << " is a string. Please enter number (minimum 4)."<<endl;
      goto CHECK_DIM;
    }
    
START_DIM:
	Dimension = std::stoi(DimVal);
    if (Dimension < 4) {
		cout << "Invalid Matrix Dimension. Please re-enter minimum 4." << endl;
		goto CHECK_DIM;
	}
		// set the dimensions
	set_dimension(MatrixA, Dimension);
	set_dimension(MatrixB, Dimension);
	set_dimension(MatrixC, Dimension);

CHECK_REAL_VAL:
    cout << "\n";
    cout << "Enter Random Maximum Real Value (minimum 10): ";
    cin >> RealVal;
    if (check_DIM_number(RealVal)){
      goto START_REAL_VAL;
    }
    else{
      cout << RealVal << " is a string. Please enter number (minimum 10)."<<endl;
      goto CHECK_REAL_VAL;
    }

START_REAL_VAL:
    _real = std::stoi(RealVal);
	MaxRndVal_JW.real(_real);
	if (real(MaxRndVal_JW) < 10) {
		cout << "Invalid random maximum real value. Please re-enter minimum 10." << endl;
		goto CHECK_REAL_VAL;
	}

CHECK_IMAG_VAL:
    cout << "\n";
    cout << "Enter Random Maximum Imaginary Value (minimum 10): ";
    cin >> ImagVal;
    if (check_DIM_number(ImagVal)){
      goto START_IMAG_VAL;
    }
    else{
      cout << ImagVal << " is a string. Please enter number (minimum 10)."<<endl;
      goto CHECK_IMAG_VAL;
    }

START_IMAG_VAL:
    _imag = std::stoi(ImagVal);
	MaxRndVal_JW.imag(_imag);
	if (imag(MaxRndVal_JW) < 10) {
		cout << "Invalid random maximum imaginary value. Please re-enter minimum 10." << endl;
		goto CHECK_IMAG_VAL;
	}

	// set random value in the matrix
	set_random_value(MatrixA, Dimension, MaxRndVal_JW);
	set_random_value(MatrixB, Dimension, MaxRndVal_JW);
	set_random_value(MatrixC, Dimension, 0); // Set Result Matrix to zero 
	
	//display matrix
	cout << "\n";
	cout << "Display Matrix A" << endl;
	cout << "\n";
	display_matrix(MatrixA, Dimension);
	cout << "\n";
	cout << "Display Matrix B" << endl;
	cout << "\n";
	display_matrix(MatrixB, Dimension);

	// matrix non-parallel multiplication
	cout << "\n";
	cout << "Start non-parallel multiplication..." << endl;
	Elapsed = matrix_multiplication(MatrixA, MatrixB, MatrixC, Dimension);

	// Display non-parallel multiplication elapsed time
	cout << "\n";
	cout << "Non-parallel multiplication elapsed time: " << Elapsed << "ms" << endl;

	// matrix parallel multiplication
	cout << "\n";
	cout << "Start parallel multiplication..." << endl;
	ParallelElapsed = matrix_parallel_multiplication(MatrixA, MatrixB, MatrixC, Dimension);

	// Display parallel multiplication elapsed time
	cout << "\n";
	cout << "Parallel multiplication elapsed time: " << ParallelElapsed << "ms" << endl;

	//display result matrix
	cout << "\n";
	cout << "Display Result Matrix C" << endl;
	cout << "\n";
	display_matrix(MatrixC, Dimension);

	// difference of two processes
	cout << "\n";
	cout << "Difference of the two (2) processes: " << Elapsed - ParallelElapsed << "ms" << endl;
	cout << "\n";
	cout << "Difference of the two (2) processes: " << (Elapsed - ParallelElapsed)/1000 << "s" << endl;
    cout << "\n";
	system("PAUSE");
	cout << "\n";
	cout << "Parallel Processing Application Completed Successfully!" << "\n";
	cout << "\n";
	cout << "Good Bye and Thank You For Your Time" << "\n";
	cout << "\n";
	cout << "Exiting Parallel CPU Matrix Multiply Program..." << "\n";

    return 0;
}

double matrix_multiplication(TYPE** MatrixA, TYPE** MatrixB, TYPE** &MatrixC, size_t Dimension) {

	double start = clock();

	for (size_t i = 0; i < Dimension; i++) {
		for (size_t j = 0; j < Dimension; j++) {
			for (size_t k = 0; k < Dimension; k++) {
				MatrixC[i][j] += MatrixA[i][k] * MatrixB[k][j];
			}
		}
	}

	double end = clock();
	return end - start;
}

double matrix_parallel_multiplication(TYPE** MatrixA, TYPE** MatrixB, TYPE** &MatrixC, size_t Dimension) {

	double start = clock();

//#pragma omp parallel for
#pragma omp parallel shared(MatrixA,MatrixB,MatrixC) private(i,j,k)
	{
#pragma omp for schedule(static)
		for (size_t i = 0; i < Dimension; i++) {
		    #pragma omp for schedule(static)
			for (size_t j = 0; j < Dimension; j++) {
			    #pragma omp for schedule(static)
				for (size_t k = 0; k < Dimension; k++) {
				    #pragma omp atomic
					MatrixC[i][j] += MatrixA[i][k] * MatrixB[k][j];
				}
			}
		}
	}
	double end = clock();
	return end - start;
}

void set_dimension(TYPE** &Matrix, size_t Dimension) {

	Matrix = (TYPE**)malloc(Dimension * sizeof(TYPE*));

	for (size_t i = 0; i < Dimension; i++) {
		Matrix[i] = (TYPE*)malloc(Dimension * sizeof(TYPE));
	}
}

void set_random_value(TYPE** &Matrix, size_t Dimension, TYPE MaxRndVal_JW) {

	for (size_t i = 0; i < Dimension; i++) {
		for (size_t j = 0; j < Dimension; j++) {
			if (real(MaxRndVal_JW) < 1 || imag(MaxRndVal_JW) < 1) {
				Matrix[i][j].real(0);
				Matrix[i][j].imag(0);
			}
			else
			{
				double _real, _imag;
				_real = real(MaxRndVal_JW);
				_real = rand() % (size_t)_real;
				_imag = imag(MaxRndVal_JW);
				_imag = rand() & (size_t)_imag;
				Matrix[i][j].real(_real);
				Matrix[i][j].imag(_imag);
			}
			
		}
	}
}

void display_matrix(TYPE** Matrix,size_t Dimension) {

	if (Dimension > 30) {
		cout << "Display is not available. Matrix Dimension is more than 30." << endl;
		return;
	}
	for (size_t i = 0; i < Dimension; i++) {
		for (size_t j = 0; j < Dimension; j++) {
			cout << Matrix[i][j] << " ";
		}
		cout << endl;
	}
}


