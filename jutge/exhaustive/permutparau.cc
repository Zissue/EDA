#include <iostream>
#include <vector>
using namespace std;

void escriu(const vector<string> &v) {
	int n = v.size();
	cout << "(";
	for (int i = 0; i < n; ++i) 
		cout << (i != 0 ? "," : "") << v[i];
	cout << ")" << endl;
}

void permutation(vector<string>& sol, int i, vector<bool> &used, const vector<string> &w) {
	int n = sol.size();
	if (i == n) escriu(sol);
	else {
		for (int k = 0; k < n; ++k) {
			if (not used[k]) {
				used[k] = true;
				sol[i] = w[k];
				permutation(sol, i+1, used, w);
				used[k] = false;
			}
		}
	}
}

int main () {
	int n;
	cin >> n;
	vector<string> w(n);
	for (auto& x: w) cin >> x;
	vector<bool> used(n, false);
	vector<string> sol(n);
	permutation(sol, 0, used, w);
}