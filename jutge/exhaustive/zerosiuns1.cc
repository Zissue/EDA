#include <iostream>
#include <vector>
using namespace std;

void escriu(const vector<int> &sol) {
	int n = sol.size();
	for (int i = 0; i < n; ++i)
		cout << (i != 0 ? " " : "") << sol[i];
	cout << endl;
}

void zero_i_uns(vector<int> &sol, int i) {
	int n = sol.size();
	if (i == n) escriu(sol);
	else {
		sol[i] = 0;
		zero_i_uns(sol, i+1);
		sol[i] = 1;
		zero_i_uns(sol, i+1);
}	}

int main () {
	int n;
	cin >> n;
	vector<int> sol(n);
	zero_i_uns(sol, 0);
}