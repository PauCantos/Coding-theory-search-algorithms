#include <iostream>
#include <vector>
#include <math.h>
#include <bitset>
#include <set>

using namespace std;

typedef long long ll;

typedef vector<ll> vi;
typedef vector <vi> vvi;
typedef vector <bool> vb;
typedef set<vb> bt;

// global varibles

int N;
int n;
ll M;
ll size;

long count = 1;
bt::iterator it;

bt G;
vector< bt > S;

vi C;
vi A;

int wt(vb V) {
    int w = 0;
    for (int i = 0; i< V.size(); i++) w+=V[i];
    return w;
}

vb XOR (vb A, vb B) {
    int n = max(A.size(),B.size());
    vb C (n);
    for(int i =0 ; i < n; i++) C[i]=A[i]^B[i];
    return C;
}

int d (vb A, vb B) {
    int w = 0;
    for (int i = 0; i< n; i++) w+=A[i]^B[i];
    return w;
}

vb e(int i, int size) {
    vb I(size,false);
    I[i]=true;
    return I;
}

void backtrack_fill_G (vb progress) { // initioalize with progress empty
    if (progress.size()==n) {
        G.insert(progress);
    } else {
        progress.push_back(false);
        backtrack_fill_G (progress);
        progress[progress.size()-1]=true;
        backtrack_fill_G (progress);
    }
}

void update (vb new_codeword, bt& available) {
    available.erase(new_codeword);
    for(int i = 0; i < n; i++) {
        for(int j = i+1; j< n; j++) {
            available.erase(XOR(XOR(e(j,n), e(i,n)),new_codeword));
        }
    }
}

void print_vb(vb x) {
    for(int i =0; i< x.size();i++) cout << x[i];
    cout << endl;
}

void print_set(bt& X) {
    for (it = X.begin(); it!= X.end(); it++) {
        print_vb(*it);
    }
}

void search_codes(bt Code, bt& available) {
    /* debugging stuff
    cout << "new_ recursion entered:" << endl;
    cout << "Code state:" << endl;
    print_set(Code);
    cout << "availables:" << endl;
    print_set(available);
    */
    if (Code.size()==size) {
        cout << "Code " << count << ":" << endl;
        print_set(Code);
        cout << endl;
        count++;
        return;
    }
    while (!available.empty()) {
        it = available.begin();
        vb x (*it);
        //print_vb(x);
        Code.insert(x);
        available.erase(it);
        bt new_available (available);
        update(x, new_available);
        search_codes(Code, new_available);
        Code.erase(x);
    }
    // cout << "mission avorted" << endl;
}

int main() {    // maximum case; N=5, first non-trivial: N=3.
    cin >> N;
    n = pow(2,N);
    cout << "n=" << n << endl;  // case n=8
    M = pow(2,n);
    size=pow(2,n-N);

    ll a;
    bool ok = true;

    vi C(n+1);
    C[0]=1;

    //  set< bitset<8> > provisional;
    //vector< set< bitset<8> > > G(n+1, provisional);
    // S = vector< set < vb > > (n+1));
    vb emptyw (0);
    backtrack_fill_G(emptyw);

    // print_set(G);
    bt available (G);
    bt Code;
    search_codes(Code, available);

}
