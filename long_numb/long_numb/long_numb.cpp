#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <random>

#include "BigInt.h"
#include "Rational.h"
#include "MatVect.h"
using namespace std;

int getRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

void randmatrEL(Matrix<BigInt> randomMatrix, int N)
{
    for (int i = 0; i < N; ++i) {
        randomMatrix[i] = { BigInt(rand()), BigInt(rand()), BigInt(rand()) };

    }

}
int main() {
    BigInt a = 1789;
    BigInt b = 321876;
    BigInt c = 3244546238574382910;
    cout << "Class BigInt" << endl;

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "a + b = " << a + b << endl;
    cout << "a - b = " << a - b << endl;
    cout << "a * b = " << a * b << endl;
    cout << "a / b = " << a / b << endl;
    cout << "a << 4 = " << (a << 4) << endl;
    cout << "b >> 1 = " << (b >> 1) << endl;

    cout << "Class Rational" << endl;
    Rational<BigInt> x(a, b);
    Rational<BigInt> y(b, c);
    Rational<long long> z(1, 3);

    cout << "x = " << x << endl;
    cout << "y = " << y << endl;
    cout << "z = " << z << endl;

    cout << "x + y = " << x + y << endl;
    cout << "x - y = " << x - y << endl;
    cout << "x * y = " << x * y << endl;
    cout << "x / y = " << x / y << endl;
    cout << "x << 2" << (x.shiftLeft(2)) << endl;
    cout << "x >> 2" << (x.shiftRight(1)) << endl;


    cout << "Class Matrix and Vector" << endl;

    int N1 = 3;
    int N2 = 10;
    int N3 = 50;

    Matrix<BigInt> randomMatrix1(N1, N1);
    Matrix<BigInt> randomMatrix2(N2, N2);
    Matrix<BigInt> randomMatrix3(N3, N3);

    for (int i = 0; i < N1; ++i) {

       randomMatrix1[i] = { BigInt(rand()),BigInt(rand()),BigInt(rand()) };
        
    }

    for (int i = 0; i < N2; ++i) {
            randomMatrix2[i] = { BigInt(rand()),BigInt(rand()),BigInt(rand()),BigInt(rand()),BigInt(rand()),BigInt(rand()),BigInt(rand()),BigInt(rand()),BigInt(rand()),BigInt(rand()) };
    }
    vector<BigInt> bRandom1 = { BigInt(rand()),  BigInt(rand()),  BigInt(rand()) };

    vector<BigInt> bRandom2;
    for (int i = 0; i < N2; ++i) {
        bRandom2.push_back(BigInt(rand()));
    }
    vector<BigInt> bRandom3;
    for (int i = 0; i < N3; ++i) {
        bRandom3.push_back(BigInt(rand()));
    }
    cout << "Random Matrix N=3:\n" << randomMatrix1 << std::endl;
    cout << "Solution N=3:\n";
    vector<BigInt> solutionRandom1 = randomMatrix1.solveEquations(bRandom1);
    for (int i = 0; i < solutionRandom1.size(); ++i) {
        std::cout << "x" << i + 1 << " = " << solutionRandom1[i] << " ";
    }
    cout << ";" << endl;

    cout << "Solution N=10:\n";
    vector<BigInt> solutionRandom2 = randomMatrix2.solveEquations(bRandom2);
    for (int i = 0; i < solutionRandom2.size(); ++i) {
        cout << "x" << i + 1 << " = " << solutionRandom2[i]<< " ";
    }
    cout << ";" << endl;

    Matrix<Rational<BigInt>> rationalMatrix(N1, N1);
    for (int i = 0; i < N1; ++i) {

        rationalMatrix[i] = { Rational<BigInt>(getRandomNumber(1,10), getRandomNumber(1,10)),Rational<BigInt>(
            getRandomNumber(0,10), getRandomNumber(1,10)),Rational<BigInt>(getRandomNumber(1,10), getRandomNumber(1,10))};

    }
    
    vector<Rational<BigInt>> bRational = { Rational<BigInt>(3, 1), Rational<BigInt>(1, 1), Rational<BigInt>(5, 1) };
    cout << "Rational Matrix:\n" << rationalMatrix << endl;
    cout << "Solution:\n";
    vector<Rational<BigInt>> solutionRational = rationalMatrix.solveEquations(bRational);
    for (int i = 0; i < solutionRational.size(); ++i) {
        cout << "x" << i + 1 << " = " << solutionRational[i] << endl;
    }
    return 0;
}