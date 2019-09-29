#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

// global varibles
int N;
long n;
long long M;

int wt(int k) {
    int cont;
    while (k) {
        cont += k & 1;
        k >>= 1;
    }
    return cont;
}

int main() {
    ofstream myfile;
    cin >> N;
    myfile.open("outputs/adjacency_matrix(2).txt");

    n = pow(2,N);
    myfile << "Matrix for n = " << n << endl;
    cout << "n=" << n << endl;
    M = pow(2,n);
    cout << "printing " << M << "x" << M << " matrix" << endl;
    for(int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            myfile << "  " << ((wt(i^j)==1) ? 1 : 0) << "  ";
        }
        myfile << endl;
    }
    cout << "done" << endl;
    myfile.close();
    return 0;
}
