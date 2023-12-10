#include <iostream>
#include <vector>
using namespace std;

int first_occurrence(double x, const vector<double>& v, int esq, int dre) {
    if (esq > dre) return -1;
    int m = (esq+dre)/2;
    if (x < v[m]) return first_occurrence(x,v,esq,m-1);
    if (x > v[m]) return first_occurrence(x,v,m+1,dre);
    //Trobem un x qualsevol i mirem si mĂŠs enrrere tenim algun altre
    if (m == 0 or v[m-1] != x) return m;
    return first_occurrence(x,v,esq,m-1);
}

int first_occurrence(double x, const vector<double>& v) {
    return first_occurrence(x, v, 0, (v.size()-1));
}

int main () {
    vector<double> v = {0,1,2,3,4,5,5,5,5,5,6,7,8,9};
    cout << first_occurrence(9, v) << endl;
}