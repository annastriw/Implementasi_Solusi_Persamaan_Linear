/// Dibuat oleh ANNAS TRI WIDAGDO
/// 21120122140112 - TEKKOM UNDIP

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Fungsi untuk melakukan dekomposisi LU menggunakan Metode Crout
void croutDecomposition(const vector<vector<double>>& A, vector<vector<double>>& L, vector<vector<double>>& U, int n) {
    for (int q = 0; q < n; ++q) {
        // Bagian U
        for (int j = q; j < n; ++j) {
            double sum = 0.0;
            for (int k = 0; k < q; ++k) {
                sum += L[q][k] * U[k][j];
            }
            U[q][j] = A[q][j] - sum;
        }

        // Bagian L
        for (int i = q; i < n; ++i) {
            if (i == q) {
                if (U[q][q] == 0) {
                    cout << "\n";
                    cout << ">>>Dekomposisi gagal karena U[q][q]=0. Matriks tidak bisa didekomposisi dengan metode ini!" << endl;
                    cout << ">>>Coba inputkan SPL kembali, dengan melakukan pertukaran baris!" << endl;
                    return;
                }
                L[q][q] = 1;
            } else {
                double sum = 0.0;
                for (int k = 0; k < q; ++k) {
                    sum += L[i][k] * U[k][q];
                }
                L[i][q] = (A[i][q] - sum) / U[q][q];
            }
        }
    }
}

// Fungsi untuk melakukan substitusi maju
vector<double> forwardSubstitution(const vector<vector<double>>& L, const vector<double>& B, int n) {
    vector<double> Y(n, 0.0);
    for (int row = 0; row < n; ++row) {
        double sum = 0.0;
        for (int col = 0; col < row; ++col) {
            sum += L[row][col] * Y[col];
        }
        Y[row] = (B[row] - sum) / L[row][row];
    }
    return Y;
}

// Fungsi untuk melakukan substitusi mundur
vector<double> backwardSubstitution(const vector<vector<double>>& U, const vector<double>& Y, int n) {
    vector<double> X(n, 0.0);
    for (int row = n - 1; row >= 0; --row) {
        double sum = 0.0;
        for (int col = row + 1; col < n; ++col) {
            sum += U[row][col] * X[col];
        }
        X[row] = (Y[row] - sum) / U[row][row];
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
    vector<vector<double>> A = {{a11, a12, a13}, {a21, a22, a23}, {a31, a32, a33}};
    vector<double> B = {b1, b2, b3};
    int n = A.size();

    // 3) Menampilkan Output Matriks A
    cout << "\n>>>Matriks A:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }

    // 4) Menampilkan Output Matriks B
    cout << "\n>>>Matriks B:" << endl;
    for (int i = 0; i < n; ++i) {
        cout << B[i] << endl;
    }

    // 5) Inisialisasi matriks L dan U
    vector<vector<double>> L(n, vector<double>(n, 0.0));
    vector<vector<double>> U(n, vector<double>(n, 0.0));

    // 6) Proses Dekomposisi matriks A menjadi matriks L dan U menggunakan Metode Crout
    croutDecomposition(A, L, U, n);

    // 7) Menampilkan semua hasil hitung rumus L[i][q], untuk membuat Matriks L
    cout << "\n>>>Hasil hitung rumus L[i][q], untuk membuat Matriks L:" << endl;
    cout << "Nilai L[1][1]: " << L[0][0] << endl;
    cout << "Nilai L[1][2]: " << L[0][1] << endl;
    cout << "Nilai L[1][3]: " << L[0][2] << endl;
    cout << "Nilai L[2][1]: " << L[1][0] << endl;
    cout << "Nilai L[2][2]: " << L[1][1] << endl;
    cout << "Nilai L[2][3]: " << L[1][2] << endl;
    cout << "Nilai L[3][1]: " << L[2][0] << endl;
    cout << "Nilai L[3][2]: " << L[2][1] << endl;
    cout << "Nilai L[3][3]: " << L[2][2] << endl;

    // 8) Output Matriks L
    cout << ">>>Matriks L:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << L[i][j] << " ";
        }
        cout << endl;
    }

    // 9) Menampilkan semua hasil hitung rumus U[q][j], untuk membuat Matriks U
    cout << "\n>>>Hasil hitung rumus U[q][j], untuk membuat Matriks U:" << endl;
    cout << "Nilai U[1][1]: " << U[0][0] << endl;
    cout << "Nilai U[1][2]: " << U[0][1] << endl;
    cout << "Nilai U[1][3]: " << U[0][2] << endl;
    cout << "Nilai U[2][1]: " << U[1][0] << endl;
    cout << "Nilai U[2][2]: " << U[1][1] << endl;
    cout << "Nilai U[2][3]: " << U[1][2] << endl;
    cout << "Nilai U[3][1]: " << U[2][0] << endl;
    cout << "Nilai U[3][2]: " << U[2][1] << endl;
    cout << "Nilai U[3][3]: " << U[2][2] << endl;

    // 10) Output Matriks U
    cout << ">>>Matriks U:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << U[i][j] << " ";
        }
        cout << endl;
    }

    // 11) Output rumus substitusi maju
    cout << "\n>>>Lakukan substitusi maju untuk mencari Y, dengan rumus L.Y = B" << endl;

    // 12) Proses Substitusi maju
    vector<double> Y = forwardSubstitution(L, B, n);

    // 13) Output matriks Y
    cout << ">>>Matriks Y setelah substitusi maju:" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "y" << i + 1 << " = " << Y[i] << endl;
    }

    // 14) Output rumus substitusi mundur
    cout << "\n>>>Lakukan substitusi mundur untuk mencari X, dengan rumus U.X = Y" << endl;

    // 15) Proses Substitusi mundur
    vector<double> X = backwardSubstitution(U, Y, n);

    // 16) Print solusi persamaan linear (X)
    cout << ">>>Solusi dari persamaan linear (X):" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "x" << i + 1 << " = " << X[i] << endl;
    }
    cout << "\n";

    return 0;
}