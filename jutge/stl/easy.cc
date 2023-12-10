#include <set>
#include <iostream>
using namespace std;

struct compLength {
	bool operator() (const string& a, const string& b) const {
		if (a.size() != b.size()) return a.size() < b.size();
		else return a < b;
	}
};

int main () {

	int gamenum = 1;
	string inp;
	while (inp != "QUIT") {

		set<string> has;
		set<string, compLength> had;

		while (cin >> inp and inp != "END" and inp != "QUIT") {

			auto its = has.find(inp);

			if (its == has.end()) {
				has.insert(its, inp);
				auto itd = had.find(inp);
				if (itd != had.end()) had.erase(inp);
			}
			else {
				has.erase(its);
				had.insert(inp);
			}
		}

		if (gamenum != 1) cout << endl;
		cout << "GAME #" << gamenum << endl << "HAS:" << endl;
		for (auto x: has) cout << x << endl;
		cout << endl << "HAD:" << endl;
		for (auto x: had) cout << x << endl;
		gamenum++;
	}
}