/// Dibuat oleh ANNAS TRI WIDAGDO
/// 21120122140112 - TEKKOM UNDIP

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Fungsi untuk melakukan eliminasi Gauss
void gaussianElimination(vector<vector<double>>& A, vector<double>& B, int n) {
    for (int i = 0; i < n - 1; ++i) {
        // Pivoting
        int maxIdx = i;
        double maxVal = abs(A[i][i]);
        for (int k = i + 1; k < n; ++k) {
            if (abs(A[k][i]) > maxVal) {
                maxVal = abs(A[k][i]);
                maxIdx = k;
            }
        }
        // Menukar baris
        if (maxIdx != i) {
            swap(A[i], A[maxIdx]);
            swap(B[i], B[maxIdx]);
        }

        // Eliminasi
        for (int j = i + 1; j < n; ++j) {
            double factor = A[j][i] / A[i][i];
            for (int k = i; k < n; ++k) {
                A[j][k] -= factor * A[i][k];
            }
            B[j] -= factor * B[i];
        }
    }
}

// Fungsi untuk mendekomposisi matriks A menjadi matriks L dan U
void decomposeLU(const vector<vector<double>>& A, vector<vector<double>>& L, vector<vector<double>>& U, int n) {
    for (int i = 0; i < n; ++i) {
        // Matriks U
        for (int j = i; j < n; ++j) {
            double sum = 0.0;
            for (int k = 0; k < i; ++k) {
                sum += L[i][k] * U[k][j];
            }
            U[i][j] = A[i][j] - sum;
        }

        // Matriks L
        L[i][i] = 1;
        for (int j = i + 1; j < n; ++j) {
            double sum = 0.0;
            for (int k = 0; k < i; ++k) {
                sum += L[j][k] * U[k][i];
            }
            L[j][i] = (A[j][i] - sum) / U[i][i];
        }
    }
}

// Fungsi untuk melakukan substitusi maju
vector<double> forwardSubstitution(const vector<vector<double>>& L, const vector<double>& B, int n) {
    vector<double> Y(n, 0.0);
    for (int i = 0; i < n; ++i) {
        double sum = 0.0;
        for (int j = 0; j < i; ++j) {
            sum += L[i][j] * Y[j];
        }
        Y[i] = (B[i] - sum) / L[i][i];
    }
    return Y;
}

// Fungsi untuk melakukan substitusi mundur
vector<double> backwardSubstitution(const vector<vector<double>>& U, const vector<double>& Y, int n) {
    vector<double> X(n, 0.0);
    for (int i = n - 1; i >= 0; --i) {
        double sum = 0.0;
        for (int j = i + 1; j < n; ++j) {
            sum += U[i][j] * X[j];
        }
        X[i] = (Y[i] - sum) / U[i][i];
    }
    return X;
}

int main() {
    // 1) Inputan manual dari user untuk 3 buah Persamaan Linear
    double a11, a12, a13, b1, a21, a22, a23, b2, a31, a32, a33, b3;
    cout << "\n";
    cout << ">>>Masukkan persamaan linear dalam bentuk [a11]X1 + [a12]X2 + [a13]X3 = [b1]:" << endl;
    cout << "Masukkan nilai a11: ";
    cin >> a11;
    cout << "Masukkan nilai a12: ";
    cin >> a12;
    cout << "Masukkan nilai a13: ";
    cin >> a13;
    cout << "Masukkan nilai b1: ";
    cin >> b1;

    cout << ">>>Masukkan persamaan linear dalam bentuk [a21]X1 + [a22]X2 + [a23]X3 = [b2]:" << endl;
    cout << "Masukkan nilai a21: ";
    cin >> a21;
    cout << "Masukkan nilai a22: ";
    cin >> a22;
    cout << "Masukkan nilai a23: ";
    cin >> a23;
    cout << "Masukkan nilai b2: ";
    cin >> b2;

    cout << ">>>Masukkan persamaan linear dalam bentuk [a31]X1 + [a32]X2 + [a33]X3 = [b3]:" << endl;
    cout << "Masukkan nilai a31: ";
    cin >> a31;
    cout << "Masukkan nilai a32: ";
    cin >> a32;
    cout << "Masukkan nilai a33: ";
    cin >> a33;
    cout << "Masukkan nilai b3: ";
    cin >> b3;

    // 2) Konversi Persamaan linear dalam bentuk matriks A dan vektor B
    vector<vector<double>> A_matrix = {{a11, a12, a13}, {a21, a22, a23}, {a31, a32, a33}};
    vector<double> B_vector = {b1, b2, b3};
    int n = A_matrix.size();

    // 3) Menampilkan Output Matriks A
    cout << "\n>>>Matriks A:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << A_matrix[i][j] << " ";
        }
        cout << endl;
    }

    // 4) Menampilkan Output Matriks B
    cout << "\n>>>Matriks B:" << endl;
    for (int i = 0; i < n; ++i) {
        cout << B_vector[i] << endl;
    }

    // 5) Eliminasi Gauss dengan pivoting
    vector<vector<double>> A_pivoted = A_matrix; 
    gaussianElimination(A_matrix, B_vector, n);

    // 6) Output Matriks A setelah Eliminasi Gauss dengan pivoting
    cout << "\n>>>Matriks A setelah Eliminasi Gauss dengan pivoting:" << endl;
    cout << ">>>Matriks A':" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << A_matrix[i][j] << " ";
        }
        cout << endl;
    }

    // 7) Output Matriks B setelah Eliminasi Gauss dengan pivoting
    cout << "\n>>>Matriks B setelah Eliminasi Gauss dengan pivoting:" << endl;
    cout << ">>>Matriks B':" << endl;
    for (int i = 0; i < n; ++i) {
        cout << B_vector[i] << endl;
    }

    // 8) Inisialisasi matriks L dan U dengan ukuran yang sesuai
    vector<vector<double>> L(n, vector<double>(n, 0.0));
    vector<vector<double>> U(n, vector<double>(n, 0.0));

    // 9) Dekomposisi matriks A menjadi matriks L dan U
    decomposeLU(A_matrix, L, U, n);

    // 10) Output Matriks L
    cout << "\n>>>Matriks L:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << L[i][j] << " ";
        }
        cout << endl;
    }

    // 11) Output Matriks U
    cout << "\n>>>Matriks U:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << U[i][j] << " ";
        }
        cout << endl;
    }

    // 12) Output rumus substitusi maju
    cout << "\n>>>Lakukan substitusi maju untuk mencari Y, dengan rumus L.Y = B'" << endl;

    // 13) Proses Substitusi maju
    vector<double> Y = forwardSubstitution(L, B_vector, n);

    // 14) Output matriks Y
    cout << ">>>Matriks Y setelah substitusi maju:" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "y" << i + 1 << " = " << Y[i] << endl;
    }

    // 15) Output rumus substitusi mundur
    cout << "\n>>>Lakukan substitusi mundur untuk mencari X, dengan rumus U.X = Y" << endl;

    // 16) Proses Substitusi mundur
    vector<double> X = backwardSubstitution(U, Y, n);

    // 17) Print solusi persamaan linear (X)
    cout << ">>>Solusi dari persamaan linear (X):" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "x" << i + 1 << " = " << X[i] << endl;
    }
    cout << "\n";

    return 0;
}