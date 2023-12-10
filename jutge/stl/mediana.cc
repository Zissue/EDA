#include <iostream>
#include <set>
using namespace std;

int main () {
	set<string> cjt;
	string x;
	auto mid = cjt.end();

	while (cin >> x and x != "END") {
		auto it = cjt.insert(x).first;
		if (mid == cjt.end()) mid = it;
		else if (cjt.size()%2 == 0 and x < *mid) --mid;
		else if (cjt.size()%2 != 0 and x > *mid) ++mid;
		cout << *mid << endl;
	}
}
