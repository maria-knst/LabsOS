#include<iostream>
#include<fstream>
#include<ctime>
#include<thread>
#include<mutex>
#include<vector>
#include<queue>
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

double threadMultiply(const std::vector<std::vector<double>>& first, const std::vector<std::vector<double>>& second,
	std::vector<std::vector<double>>& result, int i, int j) {
	double sum = 0;
	for (int s = 0; s < first.size(); s++)
	{
		sum += first[i][s] * second[s][j];
	}
	result[i][j] =  sum;
	ExitThread(0);
}

std::vector<std::vector<double>> Multiply2_1
(const std::vector<std::vector<double>>& first, const std::vector<std::vector<double>>& second,int n,int m) {
	std::queue<std::thread> threads;
	int count = 0;

	std::vector<double> row(m, 0);
	std::vector<std::vector<double>> result(n, row);
	for (int i = 0; i < first.size(); i++)
	{
		for (int j = 0; j < second[0].size(); j++)
		{
			if (count < NumberOfThreads) {
				threads.push(std::thread(threadMultiply, std::cref(first), std::cref(second), std::ref(result), i, j));
				count++;
			}
			else {
				threads.front().join();
				threads.pop();
				threads.push(std::thread(threadMultiply, std::cref(first), std::cref(second), std::ref(result), i, j));
			}
		}

	}
	while (!threads.empty()) {
		threads.front().join();
		threads.pop();
	}
	return result;

}


int main() {

	std::ifstream in("input.txt");
	int n, k;
	in >> n >> k;
	
	std::vector<double> row(n, 0);
	std::vector<std::vector<double>> A(n, row);
	std::vector<std::vector<double>> B(n, row);
	std::vector<std::vector<double>> res(n, row);


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
	Multiply21 p(n, A, B, res, n / NumberOfThreads);

	clock_t start1 = clock();
	std::vector<std::vector<double>> C1 = Multiply2_1(p.A_,p.B_,p.n,p.n);
	clock_t end1 = clock() - start1;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			std::cout << C1[i][j] << " ";
		}
		std::cout << '\n';
	}

	std::cout << (double)end / CLOCKS_PER_SEC << " sec." << '\n';
	
	in.close();
	return 0;
	
}