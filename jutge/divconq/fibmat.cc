#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> fila;
typedef vector<fila> matrix;

const matrix iden = {  {1,0}, 
                       {0,1}  };

const matrix aux = {  {1,1},
                      {1,0}  };

const matrix uzero = { {1}, 
                       {0}  };

int mod = -1;

matrix producte(const matrix& a, const matrix& b) {
    
    matrix c(a.size(), vector<int> (b[0].size()));
    
    for (int i = 0; i < a.size(); ++i)
        for (int j = 0; j < b[0].size(); ++j)
            for (int k = 0; k < a[0].size(); ++k) 
               c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % mod;
    return c;
}

matrix powmat(const matrix& mat, int n) {
    if (n == 0) return iden;
    else if (n == 1) return mat;
    else {
        
        matrix aux2 = powmat(mat, n/2);
        matrix aux3 = producte(aux2, aux2);
        
        if (n%2 == 0) return aux3;
        else return producte(aux3, mat);
    }
}

int matfib (int n) {
    if (n == 0) return 0;
    else if (n == 1) return 1;
    else {
        matrix sol = aux;
        sol = powmat(sol, n-1);
        sol = producte(sol, uzero);
        return sol[0][0];
    }
    
}

int main () {
    int n;
    while(cin >> n >> mod) 
        cout << matfib(n) << endl;
}