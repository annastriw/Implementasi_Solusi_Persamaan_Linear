///Dibuat oleh ANNAS TRI WIDAGDO
///21120122140112 - TEKKOM UNDIP

#include <iostream>

using namespace std;

// Fungsi untuk mencetak matriks ukuran 3x3
void printMatrix(double mat[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    //1). Inputan manual dari user sejumlah 3 buah Persamaan Linear
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

    //2). Konversi menjadi Matriks Koefisien Utama ukuran 3x3 (Matriks A)
    double A[3][3] = {
        {a11, a12, a13},
        {a21, a22, a23},
        {a31, a32, a33}
    };

    //3). Konversi Konstanta pada ruas kanan persamaan (Matriks B)
    double B[3][1] = {
        {b1},
        {b2},
        {b3}
    };

    //4). Menampilkan matriks A
    cout << "\n";
    cout << ">>>Matriks A:" << endl;
    printMatrix(A);
    cout << "\n";

    //5). Menampilkan matriks B
    cout << ">>>Matriks B:" << endl;
    for (int i = 0; i < 3; i++) {
        cout << B[i][0] << endl;
    }
    cout << "\n";

    //6). Mencari determinan matriks A
    double det = A[0][0] * (A[1][1] * A[2][2] - A[1][2] * A[2][1]) -
                 A[0][1] * (A[1][0] * A[2][2] - A[1][2] * A[2][0]) +
                 A[0][2] * (A[1][0] * A[2][1] - A[1][1] * A[2][0]);

    //7). Menampilkan nilai determinan matriks A
    cout << ">>>Determinan Matriks A:" << endl;
    cout << "Determinan A= " << det << endl;
    cout << "\n";

    //8). Cek apakah det A tidak nol
    if (det != 0) {
        double A_inv[3][3];

        //9). Mencari matriks invers A
        A_inv[0][0] = (A[1][1] * A[2][2] - A[1][2] * A[2][1]) / det;
        A_inv[0][1] = -(A[0][1] * A[2][2] - A[0][2] * A[2][1]) / det;
        A_inv[0][2] = (A[0][1] * A[1][2] - A[0][2] * A[1][1]) / det;
        A_inv[1][0] = -(A[1][0] * A[2][2] - A[1][2] * A[2][0]) / det;
        A_inv[1][1] = (A[0][0] * A[2][2] - A[0][2] * A[2][0]) / det;
        A_inv[1][2] = -(A[0][0] * A[1][2] - A[0][2] * A[1][0]) / det;
        A_inv[2][0] = (A[1][0] * A[2][1] - A[1][1] * A[2][0]) / det;
        A_inv[2][1] = -(A[0][0] * A[2][1] - A[0][1] * A[2][0]) / det;
        A_inv[2][2] = (A[0][0] * A[1][1] - A[0][1] * A[1][0]) / det;

        //10). Menampilkan matriks invers A
        cout << ">>>Matriks Invers A:" << endl;
        printMatrix(A_inv);
        cout << "\n";

        double X[3][1] = {0};

        //11). Menampilkan rumus perkalian matriks invers A dengan matriks B
        cout << ">>>X = A_invers * B:" << endl;

        //12). Perkalian matriks invers A dengan B
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 1; j++) {
                for (int k = 0; k < 3; k++) {
                    X[i][j] += A_inv[i][k] * B[k][j];
                }
            }
        }

        //13). Menampilkan hasil persamaan linear
        cout << ">>>Hasil Persamaan Linear (X):" << endl;
        cout << "X1 = " << X[0][0] << endl;
        cout << "X2 = " << X[1][0] << endl;
        cout << "X3 = " << X[2][0] << endl;
        cout << "\n";
    } else {
        cout << ">>>Hasil Persamaan Linear (X):" << endl;
        cout << "Determinan nol. Matriks Anda tidak dapat diinvers." << endl;
        cout << "\n";
    }

    return 0;
}
