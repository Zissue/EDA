#include <iostream>
#include <map>
using namespace std;

int main () {
	string op;
	double total = 0.0;
	map<int,int> m;
	while (cin >> op) {
		if (op == "delete") {
			if (!m.empty()) {
				auto it = m.begin();
				if (it->first > 1) m.erase(it);
				else --(m[it->first]);
				total -= m.begin()->first;
			}
			else cout << "no elements" << endl;
		}
		else {
			int n;
			cin >> n;
			if (m.find(n) != m.end()) ++m[n];
			else m.insert(make_pair(n,1));
			total += n;
		}

		if (!m.empty()) {
			auto it = m.end();
			cout << "minimum: " << m.begin()->first;
			cout << ", maximum: " << it->first;
			cout << ", average: " << total/m.size() << endl;	
		}
		// cout << endl;cout << endl;cout << endl;cout << endl;cout << endl;cout << endl;cout << endl;cout << endl;cout << endl;cout << endl;
		// for (auto lol : m) cout << lol.first << ", " << lol.second << endl;
	}
}