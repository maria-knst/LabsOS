#include "iostream"
#include "vector"

using namespace std;

class Matrix {
public:
    vector<vector<double>> matrix;
    int n;


    Matrix() : matrix(vector<vector<double>>(0)), n(0) {};
    Matrix(int newN){
        n = newN;
        matrix = vector<vector<double>>(n);
        for (int i = 0; i < n; i++) {
            matrix[i].resize(n);
        }
    };

   
    vector<vector<Matrix>> makeBlocks(int value) {
        int bl = n / value;
        Matrix res(value);

        vector<vector<Matrix>> answer(bl);
        for (int i = 0; i < bl; i++) {
            for (int j = 0; j < bl; j++) {
               
                for (int r = i * value; r < (i + 1) * value; r++) {
                    for (int c = j * value; c < (j + 1) * value; c++) {
                        res.matrix[r - i * value][c - j * value] = matrix[r][c];
                    }
                }
                answer[i].push_back(res);
            }
        }
        return answer;
    }
};
