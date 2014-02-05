//============================================================================
// Name        : BMatchingSolver.cpp
// Author      : Bert Huang
// Version     :
// Copyright   : Copyright 2010
// Description : main function for fast belief propagation b-matching
//============================================================================

#include <getopt.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
#include "BMatchingLibrary.h"
#include "utils.h"
#include "SparseMatrix.h"

using namespace std;
using namespace utils;
using namespace bmatchingLibrary;

/*!
 * Value for explicit matrix weight type
 */
#define MATRIX 0
/*!
 * Value for negative Euclidean distance weight type
 */
#define EUCLIDEAN 1
/*!
 * Value for inner product weight type
 */
#define INNER_PRODUCT 2

/*!
 * \file BMatchingSolver.cpp
 * \brief Main function for driver program
 * Contains an overly simple test function and the main command line
 * function for solving b-matchings read from disk.
 */

/*!
 * \mainpage Fast belief propagation b-matching solver
 *
 * Solves b-matching using fast belief propagation.
 * In addition to the main driver program, whose main function is located in BMatchingSolver.cpp,
 * this package includes library functions located in namespace bmatchingLibrary (in BMatchingLibrary.h) to solve
 * standard b-matching problems, such as problems with weight matrices, problems
 * with negative Euclidean weights, or inner product (linear kernel) valued weights
 * as well as the BMatchingProblem object, which can be manipulated to solve
 * custom b-matching problems.
 *
 * The algorithm used is based on research by Bert Huang and Tony Jebara
 * and this code is written by Bert Huang.
 *
 * Please cite the following paper if you use this, and stay tuned to the authors' websites for
 * updated papers on the latest algorithm included in this package.
 *
 *\verbatim
@inproceedings{HuaJeb07,
	Author = {Huang, B. and Jebara, T.},
	Booktitle = {Proceedings of the 11th International Conference on Artificial Intelligence and Statistics},
	Date-Added = {2010-02-22 12:52:26 -0500},
	Date-Modified = {2010-02-22 12:52:26 -0500},
	Editor = {Marina Meila and Xiaotong Shen},
	Month = {March},
	Title = {Loopy Belief Propagation for Bipartite Maximum Weight b-Matching},
	Volume = {2 of JMLR: W\&CP},
	Year = {2007}}
 \endverbatim
 *
 */


/*!
 * Creates a random symmetric weight matrix and runs belief propagation to solve the b-matching
 */
void testRandomMatrix() {
	// create a random weight matrix
	srand(time(NULL));


	int size = 200;

	double ** W = new double*[size];
	for (int i = 0; i < size; i++)
		W[i] = new double[size];

	for (int i = 0; i < size; i++) {
		W[i][i] = -INFINITY;
		for (int j = i+1; j < size; j++) {
			W[i][j] = ((double)rand()/(double)RAND_MAX);

			W[j][i] = W[i][j];
		}
	}

	// set target degrees of all nodes to 5

	int * degrees = new int[size];
	for (int i = 0; i < size; i++)
		degrees[i] = 5;

	int cacheSize = 4;
	int maxIter = 10000;
	bool verbose = true;

	bool ** solution;
	SparseMatrix<bool> * sm = bMatchMatrixCache(size, W, degrees, cacheSize, maxIter, verbose);

	solution = convertToBool(sm);
	delete(sm);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++)
			cout << solution[i][j] << " ";
		cout << endl;
	}
	for (int i = 0; i < size; i++)
		delete[](solution[i]);
	delete[](solution);
}

/*!
 * \fn main(int argc, char ** argv)
 * Main program reads data from files and takes command line input to use either
 * explicit weight matrix, implicit negative Euclidean weight, implicit inner product weight
 * for either bipartite or unipartite graphs
 */
int main(int argc, char ** argv) {
	// Process command line options
	int c;

	string * weightFile = 0, * degFile = 0, * dataFile = 0, * outputFile = 0;
	int n = 0, rows = 0, weightType = 0, maxIter = DEFAULT_MAX_ITERS, dimensions = 0, cacheSize = -1;
	bool binary = false;
	bool verbose = false;

	while (1)
	{
		static struct option long_options[] =
		{
				{"weights", required_argument, 0, 'w'},
				{"test", no_argument, 0, 'T'},
				{"degrees", required_argument, 0, 'd'},
				{"data", required_argument, 0, 'x'},
				{"output_file", required_argument, 0, 'o'},
				{"total", required_argument, 0, 'n'},
				{"bipartite", required_argument, 0, 'b'},
				{"weight_type", required_argument, 0, 't'},
				{"max_iter", required_argument, 0, 'i'},
				{"dimensions", required_argument, 0, 'D'},
				{"cacheSize", required_argument, 0, 'c'},
				{"verbose", no_argument, 0, 'v'},
				{"binary", no_argument, 0, 'B'},
				{0, 0, 0, 0}
		};
		/* getopt_long stores the option index here. */
		int option_index = 0;

		c = getopt_long (argc, argv, "w:d:x:n:b:t:i:o:D:Tc:v",
				long_options, &option_index);

		/* Detect the end of the options. */
		if (c == -1)
			break;

		switch (c) {
		case 'T':
			cout << "Starting test" << endl;
			testRandomMatrix();
			return 0;
		case 'w':
			weightFile = new string(optarg);
			break;
		case 'd':
			degFile = new string(optarg);
			break;
		case 'x':
			dataFile = new string(optarg);
			break;
		case 'o':
			outputFile = new string(optarg);
			break;
		case 'n':
			n = atoi(optarg);
			break;
		case 'v':
			verbose = true;
			break;
		case 'b':
			rows = atoi(optarg);
			break;
		case 't':
			weightType = atoi(optarg);
			break;
		case 'i':
			maxIter = atoi(optarg);
			break;
		case 'D':
			dimensions = atoi(optarg);
			break;
		case 'c':
			cacheSize = atoi(optarg);
			break;
		case 'B':
			binary = true;
			break;
		case '?':
			cout << "Usage: BMatchingSolver <options>" << endl <<
			"-w, --weights\tweight matrix file" << endl <<
			"-d, --degree\tdegree file" << endl <<
			"-x, --data\tnode descriptor file" << endl <<
			"-o, --output_file\toutput file" << endl <<
			"-n, --total\ttotal number of nodes" << endl <<
			"-D, --dimensions\tdimensionality of node descriptors" << endl <<
			"-c, --cacheSize\tnumber of cached weights per row" << endl <<
			"-b, --bipartite\tnumber of nodes in first bipartition" << endl <<
			"-t, --weight_type\tweight type (0 = matrix, 1 = negative Euclidean, 2 = inner product)" << endl <<
			"-i, --max_iter\tmaximum iterations of belief propagation to run" << endl <<
			"-B, --binary\tuse binary data files" << endl;
			break;

		default:
			abort ();
			break;
		}
	}

	// check options
	if ((degFile == 0) ||
			(weightType == MATRIX && weightFile == 0) ||
			(weightType != MATRIX && dataFile == 0) ||
			(weightType != MATRIX && dimensions == 0) ||
			(n == 0)) {
		cout << "Invalid options. Exiting..." << endl;
		return -1;
	} else if (binary == 1) {
		cout << "Error: Binary input files are unsupported." << endl;
		return -1;
	}

	SparseMatrix<bool> * solution = 0;
	int * b = new int[n];
	readIntArray(degFile->c_str(), b, n);

	double ** data = 0;

	switch (weightType) {

	case MATRIX:
		if (rows == 0) {
			// unipartite
			double ** W = new double*[n];
			allocateDoubleRows(W, n, n);
			readDoubleMatrix(weightFile->c_str(), W, n, n);

			solution = bMatchMatrixCache(n, W, b, cacheSize, maxIter, verbose);
		} else {
			// bipartite
			int cols = n - rows;

			double ** W = new double*[rows];
			allocateDoubleRows(W, rows, cols);

			readDoubleMatrix(weightFile->c_str(), W, rows, cols);

			solution = bMatchBipartiteMatrixCache(rows, cols, W, b, b + rows, cacheSize, maxIter, verbose);
		}

		break;

	case EUCLIDEAN:
		data = new double*[n];
		allocateDoubleRows(data, n, dimensions);
		readDoubleMatrix(dataFile->c_str(), data, n, dimensions);

		if (rows == 0) {
			// unipartite
			solution = bMatchEuclideanCache(n, dimensions, data, b, cacheSize, maxIter, verbose);
		} else {
			// bipartite
			solution = bMatchBipartiteEuclideanCache(rows, n - rows, dimensions, data, data + rows, b, b + rows, cacheSize, maxIter, verbose);
		}

		break;

	case INNER_PRODUCT:
		data = new double*[n];
		allocateDoubleRows(data, n, dimensions);
		readDoubleMatrix(dataFile->c_str(), data, n, dimensions);

		if (rows == 0) {
			// unipartite
			solution = bMatchInnerProductCache(n, dimensions, data, b, cacheSize, maxIter, verbose);
		} else {
			// bipartite
			solution = bMatchBipartiteInnerProductCache(rows, n - rows, dimensions, data, data + rows, b, b + rows, cacheSize, maxIter, verbose);
		}

		break;

	default:
		cout << "Unrecognized weight type" << endl;
		break;
	}

	if (solution) {
		// output solution as i j

		ofstream fout(outputFile->c_str());

		for (int i = 0; i < solution->getNNz(); i++) {
			fout << solution->getRows()[i] << " " << solution->getCols()[i] << endl;
		}

		fout.close();

	}

	return 0;
}
