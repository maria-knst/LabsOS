#include <iostream>
#include<fstream>
#include<vector>
#include<queue>
#include<chrono>
#include <windows.h>
#include<mutex>
#include "Matrix.h"

typedef std::chrono::high_resolution_clock Clock;

Matrix A;
Matrix B;
Matrix answer;
int NumberOfThreads = 3;
std::vector<std::vector<Matrix>> aBlocks;
std::vector<std::vector<Matrix>> bBlocks;

Matrix simpleMultiply(Matrix& matrix1, Matrix& matrix2) {
    Matrix matrix3(matrix1.n);
    for (int i = 0; i < matrix1.n; i++) {
        for (int j = 0; j < matrix2.n; j++) {
            double answer = 0;
            for (int k = 0; k < matrix1.n; k++) {
                answer += matrix1.matrix[i][k] * matrix2.matrix[k][j];
            }
            matrix3.matrix[i][j] = answer;
        }
    }
    return matrix3;
}

DWORD WINAPI threadMultiply1(LPVOID lpParam) {
    int* params = (int*)lpParam;
    double ans = 0;
    for (int i = 0; i < A.n; i++) {
        ans += A.matrix[params[0]][i] * B.matrix[i][params[1]];
    }
    answer.matrix[params[0]][params[1]] = ans;
    ExitThread(0);

}

std::mutex mutexes;
DWORD WINAPI threadMultiply2(LPVOID lpParam) {
    int* params = (int*)lpParam;
    Matrix buffer(A.n);
    for (int i = 0; i < A.n; i++) {
        for (int j = 0; j < B.n; j++) {
            buffer.matrix[i][j] = A.matrix[i][params[0]] * B.matrix[params[1]][j];
        }
    }
    mutexes.lock();
    for (int i = 0; i < answer.n; i++) {
        for (int j = 0; j < answer.n; j++) {
            answer.matrix[i][j] += buffer.matrix[i][j];
        }
    }
    mutexes.unlock();
    ExitThread(0);

}


DWORD WINAPI threadMultiply3(LPVOID lpParam) {
    int* params = (int*)lpParam;
    int row = params[0];
    int col = params[1];

    Matrix res(aBlocks[row][0].n);
    std::vector<Matrix> bufferBlocks;
    for (int i = 0; i < bBlocks.size(); i++) {
        bufferBlocks.push_back(bBlocks[i][col]);
    }
    
    for (int i = 0; i < aBlocks[row].size(); i++) {
        Matrix buffer = simpleMultiply(aBlocks[row][i],bufferBlocks[i]);

        for (int i = 0; i < buffer.n; i++) {
            for (int j = 0; j < buffer.n; j++) {
                res.matrix[i][j] += buffer.matrix[i][j];
            }
        }
    }

   
    for (int i = 0; i < res.n; i++) {
        for (int j = 0; j < res.n; j++) {
            answer.matrix[row * res.n + i][col * res.n + j] = res.matrix[i][j];
        }
    }


    ExitThread(0);
}

Matrix multiply1() {
    std::queue<HANDLE> threads;
    int count = 0;
    
    for (int i = 0; i < A.n; i++) {
        for (int j = 0; j < B.n; j++) {
        
            if (count < NumberOfThreads) {
                count++;
                int* params = new int[2];
                params[0] = i;
                params[1] = j;
                void* gettingParams = params;
                threads.push(CreateThread(NULL, 0, &threadMultiply1, gettingParams, 0, NULL));
            }
            else {
                WaitForSingleObject(threads.front(), INFINITE);
                threads.pop();
                int* params = new int[2];
                params[0] = i;
                params[1] = j;
                void* gettingParams = params;
                threads.push(CreateThread(NULL, 0, &threadMultiply1, gettingParams, 0, NULL));
            }
        }
    }

    HANDLE vectorOfTreads[40];
    for (int i = 0; i < count; i++) {
        vectorOfTreads[i] = threads.front();
        threads.pop();
    }
    WaitForMultipleObjects(count, vectorOfTreads, TRUE, INFINITE);
    return answer;
}

Matrix multiply2() {
    std::queue<HANDLE> threads;
    int count = 0;

    for (int i = 0; i < A.n; i++) {
        for (int j = 0; j < B.n; j++) {

            if (count < NumberOfThreads) {
                count++;
                int* params = new int[2];
                params[0] = i;
                params[1] = j;
                void* gettingParams = params;
                threads.push(CreateThread(NULL, 0, &threadMultiply1, gettingParams, 0, NULL));
            }
            else {
                WaitForSingleObject(threads.front(), INFINITE);
                threads.pop();
                int* params = new int[2];
                params[0] = i;
                params[1] = j;
                void* gettingParams = params;
                threads.push(CreateThread(NULL, 0, &threadMultiply1, gettingParams, 0, NULL));
            }
        }
    }

    HANDLE vectorOfTreads[40];
    for (int i = 0; i < count; i++) {
        vectorOfTreads[i] = threads.front();
        threads.pop();
    }
    WaitForMultipleObjects(count, vectorOfTreads, TRUE, INFINITE);
    return answer;
}

Matrix multiply3() {
    aBlocks = A.makeBlocks(2);
    bBlocks = B.makeBlocks(2);

    std::queue<HANDLE> threads;
    int count = 0;

    for (int i = 0; i < aBlocks.size(); i++) {
        for (int j = 0; j < bBlocks[0].size(); j++) {

            if (count < NumberOfThreads) {
                count++;
                int* params = new int[2];
                params[0] = i;
                params[1] = j;
                void* gettingParams = params;
                threads.push(CreateThread(NULL, 0, &threadMultiply3, gettingParams, 0, NULL));
            }
            else {
                WaitForSingleObject(threads.front(), INFINITE);
                threads.pop();
                int* elems = new int[2];
                elems[0] = i;
                elems[1] = j;
                void* arr = elems;
                threads.push(CreateThread(NULL, 0, &threadMultiply3, arr, 0, NULL));
            }
        }
    }
    HANDLE vectorOfTreads[40];
    for (int i = 0; i < count; i++) {
        vectorOfTreads[i] = threads.front();
        threads.pop();
    }
    WaitForMultipleObjects(count, vectorOfTreads, TRUE, INFINITE);
    return answer;
}


int main() {

    std::ifstream in("input.txt");
    std::ifstream inA("inputA.txt");
    std::ifstream inB("inputB.txt");

    int n;
    in >> n;

    Matrix mA(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            inA >> mA.matrix[i][j];
        }
    }
 
    Matrix mB(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            inB >> mB.matrix[i][j];
        }
    }

    A = mA;
    B = mB;
    answer = Matrix(n);
  


    std::cout << "Simple mult\n";
    auto t1 = Clock::now();
    Matrix C = simpleMultiply(A, B);
    auto t2 = Clock::now();
    for (int i = 0; i < C.matrix.size(); i++) {
        for (int j = 0; j < C.matrix[i].size(); j++) {
            std::cout << C.matrix[i][j] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << "time of work: "
        << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count()
        << " nanoseconds" << std::endl;

  

    std::cout << "Thread multiply 1\n";
    t1 = Clock::now();
    Matrix C1 = multiply1();
    t2 = Clock::now();
    for (int i = 0; i < C1.matrix.size(); i++) {
        for (int j = 0; j < C1.matrix[i].size(); j++) {
            std::cout << C1.matrix[i][j] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << "time of work: "
        << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count()
        << " nanoseconds" << std::endl;



    std::cout << "Thread multiply 2\n";
    t1 = Clock::now();
    Matrix C2 = multiply2();
    t2 = Clock::now();
    for (int i = 0; i < C2.matrix.size(); i++) {
        for (int j = 0; j < C2.matrix[i].size(); j++) {
            std::cout << C2.matrix[i][j] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << "time of work: "
        << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count()
        << " nanoseconds" << std::endl;



    std::cout << "Thread block multiply\n";
    t1 = Clock::now();
    Matrix C3 = multiply3();
    t2 = Clock::now();
    for (int i = 0; i < C3.matrix.size(); i++) {
        for (int j = 0; j < C3.matrix[i].size(); j++) {
            std::cout << C3.matrix[i][j] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << "time of work: "
        << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count()
        << " nanoseconds" << std::endl;
    return 0;
}