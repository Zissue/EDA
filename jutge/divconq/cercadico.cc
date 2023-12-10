#include <iostream>
#include <vector>
using namespace std;

int posicio(double x, const vector<double>& v, int esq, int dre) {
    if (esq > dre) return -1;
    int m = (esq+dre)/2;
    if (v[m] == x) return m;
    if (x < v[m]) return posicio(x, v, esq, m-1);
    else return posicio(x, v, m+1, dre);
}