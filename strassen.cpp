#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<int>> Matrix;

Matrix add(Matrix A, Matrix B) {
    int n = A.size();
    Matrix result(n, vector<int>(n));
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            result[i][j] = A[i][j] + B[i][j];
    return result;
}

Matrix subtract(Matrix A, Matrix B) {
    int n = A.size();
    Matrix result(n, vector<int>(n));
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            result[i][j] = A[i][j] - B[i][j];
    return result;
}

Matrix strassen(Matrix A, Matrix B) {
    int n = A.size();
    Matrix result(n, vector<int>(n));

    if (n == 1) {
        result[0][0] = A[0][0] * B[0][0];
    } else {
        int newSize = n / 2;
        Matrix A11(newSize, vector<int>(newSize)),
               A12(newSize, vector<int>(newSize)),
               A21(newSize, vector<int>(newSize)),
               A22(newSize, vector<int>(newSize)),
               B11(newSize, vector<int>(newSize)),
               B12(newSize, vector<int>(newSize)),
               B21(newSize, vector<int>(newSize)),
               B22(newSize, vector<int>(newSize));

        for (int i = 0; i < newSize; ++i) {
            for (int j = 0; j < newSize; ++j) {
                A11[i][j] = A[i][j];
                A12[i][j] = A[i][j + newSize];
                A21[i][j] = A[i + newSize][j];
                A22[i][j] = A[i + newSize][j + newSize];
                B11[i][j] = B[i][j];
                B12[i][j] = B[i][j + newSize];
                B21[i][j] = B[i + newSize][j];
                B22[i][j] = B[i + newSize][j + newSize];
            }
        }

        Matrix M1 = strassen(add(A11, A22), add(B11, B22));
        Matrix M2 = strassen(add(A21, A22), B11);
        Matrix M3 = strassen(A11, subtract(B12, B22));
        Matrix M4 = strassen(A22, subtract(B21, B11));
        Matrix M5 = strassen(add(A11, A12), B22);
        Matrix M6 = strassen(subtract(A21, A11), add(B11, B12));
        Matrix M7 = strassen(subtract(A12, A22), add(B21, B22));

        Matrix C12 = add(M3, M5);
        Matrix C21 = add(M2, M4);
        Matrix C22 = add(subtract(add(M1, M3), M2), M6);

        for (int i = 0; i < newSize; ++i) {
            for (int j = 0; j < newSize; ++j) {
                result[i][j] = C11[i][j];
                result[i][j + newSize] = C12[i][j];
                result[i + newSize][j] = C21[i][j];
                result[i + newSize][j + newSize] = C22[i][j];
            }
        }
    }
    return result;
}

void printMatrix(Matrix matrix) {
    int n = matrix.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            cout << matrix[i][j] << " ";
        cout << endl;
    }
}

int main() {
    Matrix A = {
        {1, 2},
        {3, 4}
    };

    Matrix B = {
        {5, 6},
        {7, 8}
    };

    cout << "Product of matrices A and B using Strassen's Algorithm:\n";
    Matrix C = strassen(A, B);
    printMatrix(C);

    return 0;
}
