#pragma once

class Multiply21
{
public:
	int n;

	std::vector<std::vector<double>> A_;
	std::vector<std::vector<double>> B_;
	std::vector<std::vector<double>> result;
	int sizeOfBlock;
	int nubmerOfIt;

	Multiply21(int n_,
		std::vector<std::vector<double>> A, std::vector<std::vector<double>> B, std::vector<std::vector<double>>& result_, int sizeOfBlock_, int numbOfIt) {
		this->n = n_;
		this->A_ = A;
		this->B_ = B;
		this->result = result_;
		this->sizeOfBlock = sizeOfBlock_;
		this->nubmerOfIt = numbOfIt;
	}

};
