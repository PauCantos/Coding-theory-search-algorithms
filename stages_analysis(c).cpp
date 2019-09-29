#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

typedef long long ll;

typedef vector<ll> vi;
typedef vector <vi> vvi;

int main() {
    int N;   // maximum case; N=5, first non-trivial: N=3.
    cin >> N;
    int n = pow(2,N);
    cout << "n=" << n << endl;

    ll a;
    bool ok = true;

    vi C(n);
    C[0]=1;

    vi A(n);
    A[0]=1; cout << 0 << "   " << A[0] << endl; // case A[0]= is also interesting
    A[1]=1; cout << 1 << "   " << A[1] << endl;
    for (int k=2; k<=n; k++) {
        C[k-1]=C[k-2]*(n-(k-2))/(k-1);
        a=C[k-1]-(n-(k-2))*A[k-2];
        A[k]=a/k;
        cout << k << "   " << A[k];
        if (a%k!=0) {
            cout << "   error";
            ok=false;
        }
        cout << endl;
    }
    cout<< ((ok) ? "ok" : "bad thing hapened") << endl;
    cout << "-------------" << endl;

    ll P = 1;
    ll S = A[0];
    for(int k=1; k<=n; k++) {
        P*=pow(k,A[k]);
        S+=A[k];
    }
    cout << "Sum: " << S << "   " << ((S==pow(2,n-N)) ? "ok" : "error") << endl;
    cout << "Combinations: " << P << endl;
}
