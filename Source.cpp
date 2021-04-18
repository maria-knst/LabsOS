#include<iostream>
#include<fstream>
#include<ctime>
#include<thread>
#include<mutex>
#include<vector>
#include"Windows.h"
#include"Multiply21.h"

using namespace std;

const int NumberOfThreads = 3;

std::vector<std::vector<double>> blockMultiply
(std::vector<std::vector<double>>& A, std::vector<std::vector<double>>& B, int n1, int m1, int n2, int m2,
	int shift_x1, int shift_x2, int shift_y1, int shift_y2) {
	if (n1 == m2) {
		std::vector<double> row(m1, 0);
		std::vector<std::vector<double>> C(n2, row);
		
		for (int i = 0; i < m1; i++) {
			for (int j = 0; j < n2; j++) {
				for (int l = 0; l < n1; l++) {
					C[i][j] += A[i + shift_x1][l + shift_y1] * B[l + shift_x2][j + shift_y2];
				}
			}
		}
		return C;
	}
	else return A;
}


void multiply(Multiply21& p) {

	std::vector<double> row(p.sizeOfBlock, 0);
	std::vector<std::vector<double>> sizeBlock(p.sizeOfBlock, row);


	for (int i = 0; i < (p.n / p.sizeOfBlock); i++) {
		sizeBlock = blockMultiply(p.A_, p.B_, p.n, p.sizeOfBlock, p.sizeOfBlock, p.n, p.nubmerOfIt * p.sizeOfBlock, 0, 0, i * p.sizeOfBlock);

		for (int j = 0; j < p.sizeOfBlock; j++) {
			for (int k = 0; k < p.sizeOfBlock; k++) {
				p.result[j + p.sizeOfBlock * p.nubmerOfIt][k + p.sizeOfBlock * i] = sizeBlock[j][k];
			}
		}
	}

	return;
}


int main() {

	std::ifstream in("input.txt");
	int n, k;
	in >> n >> k;
	
	std::vector<double> row(n, 0);
	std::vector<std::vector<double>> A(n, row);
	std::vector<std::vector<double>> B(n, row);


	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			in >> A[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			in >> B[i][j];
		}
	}

	clock_t start = clock();
	std::vector<std::vector<double>> C = blockMultiply(A, B, n, n, n, n,0, 0, 0, 0);
	clock_t end = clock() - start;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			std::cout << C[i][j] << " ";
		}
		std::cout << '\n';
	}

	std::cout << (double)end / CLOCKS_PER_SEC << " sec." << '\n';


	std::vector<std::vector<double>> C1(n,row);
	
	HANDLE* threads1 = new HANDLE[NumberOfThreads];

	clock_t start1 = clock();
	for (int i = 0; i < NumberOfThreads; i++) {
		Multiply21 p(n, A, B, C1, n / NumberOfThreads, i);
		//multiply(p);
		threads1[i] = new thread(multiply,std::ref(p));
	}
	WaitForMultipleObjects(NumberOfThreads, threads1, true, INFINITE);
	clock_t end1 = clock() - start1;

	std::cout << (double)end1 / CLOCKS_PER_SEC << " sec." << '\n';

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			std::cout << C1[i][j] << " ";
		}
		std::cout << '\n';
	}


	//случай - первая матрица разбита на строки, вторая на столбцы
	/*start = clock();
	for (int i = 0; i < NumberOfThreads; i++) {
		void* p = new parameters_mult1(c, a, b, n / streams, i, n);
		handle1[i] = CreateThread(NULL, 0, &mult1, p, 0, NULL);
	}
	WaitForMultipleObjects(streams, handle1, true, INFINITE);
	end = clock();
	if (print_matricies)
		print_matrix(c, n);
	std::cout << (double)(end - start) * 1000 / (double)CLOCKS_PER_SEC << "ms\n\n";
	*/
	in.close();
	return 0;
	
}