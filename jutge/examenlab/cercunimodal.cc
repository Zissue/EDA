#include <iostream>
#include <vector>

using namespace std;

int pic(const vector<int>& v, int l, int r) {
	if (l+1 >= r) {
		if (v[l] < v[r]) return r;
		else return l;
	}
	int m = (l+r)/2;
	if (v[m+1] > v[m]) return pic(v, m+1, r);
	if (v[m-1] > v[m]) return pic(v, l, m-1);
	return m;
}

int top(const vector<int>& v, int l, int r) {
	if (l+1 >= r) {
		if (v[l] < v[r]) return r;
		else return l;
	}
	int m = (l+r)/2;
	if (v[m-1] > v[m]) return top(v, l, m-1);
	if (v[m+1] > v[m]) return top(v, m+1, r);
	return m;
}

bool bin_search(bool asc, const vector<int>& v, int l, int r, int x) {
	if (l == r) return v[l] == x;
	int m = (l+r)/2;
	bool cond;
	if (asc) cond = (x <= v[m]);
	else 	 cond = (x >= v[m]);
	if (cond) return bin_search(asc, v, l, m, x);
	else 	  return bin_search(asc, v, m+1, r, x);
}

bool search(int x, const vector<int>& v) {
	int n = v.size();
	int p = pic(v, 0, n-1);
	return bin_search(true, v, 0, p, x) or bin_search(false, v, p, n-1, x);
}

int main () {
	vector<int> v = {0, 2, 5, 7, 6, 5, 4, 3, 1};
	int x;
	cin >> x;
	cout << search(x, v) << endl;
}