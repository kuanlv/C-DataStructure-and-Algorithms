// Kuan Lyu Matrix //
// 11/24/2019 //

#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
using namespace std;

class Matrix {

private:
    int rows, cols;
    double* data{nullptr};

public:
    Matrix(int rows, int cols, double val):rows(rows), cols(cols) {
        data = new double[rows * cols];
        for (int i = 0; i < cols * rows; i++)
            data[i] = val;
    }

    Matrix(int rows, int cols):rows(rows), cols(cols), data(new double[rows * cols]){}

    ~Matrix() {
        delete[] data;
    }

    Matrix(const Matrix& orig):rows(orig.rows), cols(orig.cols) {
        data = new double[rows * cols];
        for (int i = 0; i < rows * cols; i++)
            data[i] = orig.data[i];
    }

    Matrix(Matrix &&orig) noexcept : rows(orig.rows), cols(orig.cols) {
        data = orig.data;
        orig.data = nullptr;
    }

    double operator() (int i, int j) const {
        return data[i * cols + j];
    }

    double& operator() (int i, int j) {
        return data[i * cols + j];
    }

    friend Matrix operator+ (const Matrix& a, const Matrix& b) {
        if (a.rows != b.rows || a.cols != b.cols)
            throw "bad size";
        Matrix res(a.rows, a.cols);
        for (int i = 0; i < a.rows * a.cols; i++)
            res.data[i] = a.data[i] + b.data[i];
        return res;
    }

    friend Matrix operator* (const Matrix& a, const Matrix& b ) {
        if (a.rows != b.cols or a.cols != b.rows)
            throw "Bad size";
        Matrix res(a.rows, b.cols);
        for (int i = 0; i < a.rows; i++) {
            for (int j = 0; j < b.cols; j++) {
                double dot = 0;
                for (int k = 0; k < a.cols; k++)
                    dot += a(i, k) * b(k, j);
                res(i, j) = dot;
            }
        }
        return res;
    }

    void swapTwoRows(int i, int j) {
        for (int k = 0; k < cols; k++) {
            double temp = data[i * cols + k];
            data[i * cols + k] = data[j * cols + k];
            data[j * cols + k] = temp;
        }
    }

    void partialPivot(int index, vector<double>& B) {
        int biggestPos = index;
        double biggest = (*this)(index, index);
        for (int j = index; j < rows; j++) {
            if (abs((*this)(j, index)) >= abs(biggest)) {
                biggest = ((*this)(j, index));
                biggestPos = j;
            }
        }
        swapTwoRows(index, biggestPos);
        swap(B[index], B[biggestPos]);
    }

    void GuassEleminate(vector<double>& B) {
        for (int i = 0; i < rows - 1; i++)
            for (int k = i + 1; k < rows; k++) {
                if ((*this)(i, i) == 0)
                    continue;
                double t = (*this)(k, i) / (*this)(i, i);
                for (int j = 0; j <= rows; j++)
                    (*this)(k, j) = (*this)(k, j) - t * (*this)(i, j);
                B[k] -= t * B[i];
                (*this)(k, 0) = 0;
            }
    }

    vector<double> backSubstitute(vector<double>& B) {
        vector<double> res;
        res.reserve(rows);
        for (int i = 0; i < rows; i++)
            res.push_back(0);
        for (int i = rows - 1; i >= 0; i--) {
            res[i] = B[i];
            for (int j = i+1; j < rows; j++)
                if (j != i)
                    res[i] = res[i] - (*this)(i, j) * res[j];
            res[i] = res[i] / (*this)(i, i);
        }
        return res;
    }

    vector<double> solve(vector<double>& B) {
        vector<double> res;
        partialPivot(0, B);
        GuassEleminate(B);
        res = backSubstitute(B);
        return res;
    }


    void display() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++)
                cout << data[i * cols + j] << " ";
            cout << endl;
        }
        cout << endl;
    }

    static Matrix read(istream& s) {
        int n;
        s >> n;
        Matrix m(n,n);
        for (int i = 0; i < n * n; i++)
            s >> m.data[i];
        return m;
    }

};

void print(vector<double>& B) {
    for (auto& x: B)
        cout << x << " ";
    cout << endl;
}

vector<double> readAndSolve() {
    ifstream inFile;
    inFile.open("mat.dat");
    if (not inFile.is_open())
        throw "not open";
    int rows;
    inFile >> rows;
    Matrix matrix(rows, rows);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < rows; j++)
            inFile >> matrix(i, j);
    }
    cout << "matrix is: " << endl;
    matrix.display();
    vector<double> B;
    B.reserve(rows);
    double data;
    while (not inFile.eof()) {
        inFile >> data;
        B.push_back(data);
    }

    return matrix.solve(B);
}


int main() {
    vector<double> res;
    res = readAndSolve();
    cout << "result is: ";
    print(res);
}