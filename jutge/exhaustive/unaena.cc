#include <iostream>
#include <vector>
using namespace std;

void escriu(const vector<int> &v) {
	int n = v.size();
	cout << "(";
	for (int i = 0; i < n; ++i) 
		cout << v[i] << (i != n-1 ? "," : "");
	cout << ")" << endl;
}

void permutation(vector<int> &sol, int i, vector<bool> &used) {
	int n = sol.size();
	if (i == n) escriu(sol);
	else {
		for (int k = 1; k <= n; ++k) {
			if (not used[k]) {
				sol[i] = k;
				used[k] = true;
				permutation(sol, i+1, used);
				used[k] = false;
}	}	}	}

int main () {
	int n;
	cin >> n;
	vector<int> sol(n);
	vector<bool> used(n);
	permutation(sol, 0, used);
}