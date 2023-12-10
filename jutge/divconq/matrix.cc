#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> fila;
typedef vector<fila> matrix;

const matrix iden = { {1,0}, 
                      {0,1}  };

int m;

matrix producte(const matrix& a, const matrix& b) {
    matrix c(a.size(), vector<int> (b[0].size()));
    
    for (int i = 0; i < a.size(); ++i)
        for (int j = 0; j < b[0].size(); ++j)
            for (int k = 0; k < a[0].size(); ++k) 
               c[i][j] = (c[i][j] + a[i][k]*b[k][j]) % m;
    return c;
}

matrix powmat(const matrix& mat, int n) {
    if (n == 0) return iden;
    else {
        matrix aux2 = powmat(mat, n/2);
        matrix aux2peraux2 = producte(aux2, aux2);
        
        if (n%2 == 0) return aux2peraux2;
        else return producte(aux2peraux2, mat);
    }
}

int main () {
    matrix mat(2, fila (2));
    while (cin >> mat[0][0] >> mat[0][1] >> mat[1][0] >> mat[1][1]) {
        
        int n;
        cin >> n >> m;
        
        mat = powmat(mat, n);
        
        for (int i = 0; i < mat.size(); i++) {
            bool first = true;
            for (auto x: mat[i]) {
                if (first) first = false;
                else cout << " ";
                cout << x;
            }
            cout << endl;
        }
        cout << "----------" << endl;
    }
}