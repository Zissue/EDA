#include <iostream>
#include <vector>

using namespace std;

int mes_a_la_dreta(double x, const vector<double>& v, int l, int r) {
	if (l == r) return r;
	int m = (l+r)/2;
	if (x < v[m]) return mes_a_la_dreta(x, v, l, m);
	else return mes_a_la_dreta(x, v, m+1, r);
}

int mes_a_la_dreta(double x, const vector<double>& v) {
	return mes_a_la_dreta(x, v, 0, v.size());
}