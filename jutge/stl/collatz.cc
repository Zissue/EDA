#include <iostream>
#include <unordered_map>
using namespace std;

bool repeated(const unordered_map<int,int>& m, int x) {
	if (m.find(x) != m.end()) return true;
	return false;
}

int main () {

	int x, y, n;
	while (cin >> x >> y >> n) {

		unordered_map<int,int> seq;
		seq.insert(make_pair(n, 1));

		bool limit = false;
		bool rep = false;

		int it = 2;
		while (!limit and !rep) {

			n = (n%2 == 0) ? (n/2 + x) : (3*n + y);
			
			rep = repeated(seq, n);
			
			if (n > 100000000) limit = true;
			else if (!rep) seq.insert(make_pair(n, it));
			
			it++;
		}

		if (limit) cout << n;
		else cout << it-1 - seq[n];
		cout << endl;
	}
}