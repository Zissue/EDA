#include <iostream>
#include <map>
using namespace std;

int main () {

	map<string,int> bossa;
	map<string,int>::iterator min, max;

	string op;
	while (cin >> op) {

		if (bossa.size() != 0) {
			min = bossa.begin();
			max = --bossa.end();
		} 

		if (op == "minimum?") {
			if (bossa.size() != 0) 
				cout << "minimum: " << min->first << ", " << min->second << " time(s)";
			else cout << "indefinite minimum";
			cout << endl;
		}
		else if (op == "maximum?") {
			if (bossa.size() != 0) 
				cout << "maximum: " << max->first << ", " << max->second << " time(s)";
			else cout << "indefinite maximum";
			cout << endl;
		}
		else if (op == "delete") {
			string word;
			cin >> word;
			if (bossa.find(word) != bossa.end()) {
				if (bossa[word] > 1) --bossa[word];
				else bossa.erase(word);
			}
		}
		else if (op == "store") {
			string word;
			cin >> word;
			if (bossa.find(word) != bossa.end()) {
				++bossa[word];
			}
			else bossa.insert(make_pair(word,1));
		}
	}
}