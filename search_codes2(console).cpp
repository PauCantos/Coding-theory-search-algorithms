#include <iostream>
#include <vector>
#include <math.h>
#include <bitset>
#include <set>
#include <string>

using namespace std;

typedef long long ll;

typedef vector<ll> vi;
typedef vector <vi> vvi;
typedef vector <bool> vb;
typedef set<vb> bt;
typedef bt::iterator btit;

// global varibles
int N;
int n;
ll M;
ll codelength;

//ll a;
//bool ok = true;

long cont = 0;

bt G;
vector< bt > S;
bt S0;

bool first=true;

// some usefull functions related to the problem
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

bt neighbours1 (vb u) {
    bt N;
    for(int i=0;i<n;i++) {
        N.insert(XOR(e(i,n),u));
    }
    return N;
}

bt neighbours2 (vb u) {
    bt N;
    for(int i=0;i<n;i++) {
        for (int j=0; i< n; j++){
            N.insert(XOR(XOR(e(i,n),e(j,n)),u));
        }
    }
    return N;
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

void print_vb(vb x) {
    for(int i =0; i< x.size();i++) cout << x[i];
}

void print_set(bt& X) {
    for (btit it = X.begin(); it!= X.end(); it++) {
        print_vb(*it);
        cout << endl;
    }
}

// important functions: recursion in search_codes while update is just a void used at the begining to write less
void update (vb& new_codeword, bt& Code, bt& available, bt& tofullfill) {
    Code.insert(new_codeword);
    for(int i = 0; i < n; i++) {
        tofullfill.erase(XOR(e(i,n), new_codeword));
        for(int j = i+1; j< n; j++) {
            available.erase(XOR(XOR(e(j,n),e(i,n)), new_codeword));
        }
    }
    /*
    bt N1 (neighbours1(new_codeword));
    bt N2 (neighbours2(new_codeword));
    for(btit it = N1.begin(); it != N1.end(); it++) tofullfill.erase(*it);
    for(btit it = N2.begin(); it != N2.end(); it++) available.erase(*it);
    */
    available.erase(new_codeword);
}

void search_codes(vb new_codeword, bt Code, bt available, bt tofullfill) {
    //cout << "new recursion entered, updating information...:" << endl;
    update(new_codeword, Code, available, tofullfill);  // updates the variables Code, available and tofullfill
    /* debugging stuff
    cout << "Code state:" << endl;
    print_set(Code);
    cout << "availables:" << endl;
    print_set(available);
    */
    if (Code.size()==codelength) {
        if (available.empty() and tofullfill.empty()) {
            cout << "Code " << ++cont << ":" << endl;
            if (first) {
                bt S0 (new_codeword);
                print_set(S0);
                first = false;
            } else {
                if(set_intersection(S0.begin(),S0.end(),new_codeword.begin(),new_codeword.end()).empty()) {
                    print_set(new_codeword);
                }
            }
            cout << endl;
            return;
        } else cout << "there was an error" << endl;
    }
    btit u = tofullfill.begin();
    bt N (neighbours1(*u));
    for (btit it = N.begin(); it != N.end(); it++) {
        btit v = available.find(*it);
        if(v!=available.end()) {
            search_codes(*v, Code, available, tofullfill);
            available.erase(v); // don't put it before, else you there is no *v
        }
    }
}

int main() {
    cin >> N;
                /*  minimum case: N=0
                    maximum case: N=3
                    first non-trivial: N=2
                    first non-easy: N=3
                */

    n = pow(2,N);
    cout << "n=" << n << endl;
    M = pow(2,n);
    codelength=pow(2,n-N);
    vb emptyw (0);
    backtrack_fill_G(emptyw);

    //print_set(G);
    vb o (n, false);
    bt available (G);
    bt tofullfill (G);
    bt Code;
    //btit oit = available.find(o);
    search_codes(o, Code, available, tofullfill);
    cout << ((cont==n) ? "all ok" : "non-expected number of codes") << endl;

    return 0;
}
