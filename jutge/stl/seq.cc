#include <iostream>
#include <set>
#include <string>

using namespace std;

void atoi(string x, set<int>& seq) {
	int num = 0;
	for (int i = 0; i < x.size(); i++) {
		if (x[i] != ' ') num = num*10 + x[i]-'0';
		else {
			seq.insert(num);
			num = 0;
		}
	}
	seq.insert(num);
}

int main () {
	string inp;
	while (getline(cin, inp)) {
		set<int> seq;
		atoi(inp, seq);

		if (inp == "") cout << 0 << endl;
		else {
			bool first = true;
			int currlength = 0;
			int last;
			bool paridad;

			for (auto it = seq.begin(); it != seq.end(); it++) {
				if (first) {
					++currlength;
					last = *it;
					paridad = (*it)%2 == 0;
					first = false;
				}
				else {
					if (paridad and (*it)%2 != 0) {
						currlength++;
						last = *it;
						paridad = false;
					}
					else if (!paridad and (*it)%2 == 0)  {
						currlength++;
						last = *it;
						paridad = true;
					}	
				}
			}
			cout << currlength << endl;
		}
	}
}