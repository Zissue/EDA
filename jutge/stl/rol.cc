#include <set>
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

bool compa(const pair<string, int>& p1, const pair<string, int>& p2) {
	if (p1.second != p2.second) {
		return p1.second > p2.second;
	}
	else {
		return p1.first < p2.first;
	}
}

int main () {

	string ACTION;
	map<string, int> playerbase;
	set<string> online;

	while (cin >> ACTION) {

		string j1;
		cin >> j1;

		if (ACTION == "LOGIN") {
			if (online.find(j1) == online.end()) {
				if (playerbase.find(j1) == playerbase.end()) {
					playerbase.insert(make_pair(j1, 1200));
				}
				online.insert(j1);
			}
		}
		else if (ACTION == "LOGOUT") {
			if (online.find(j1) != online.end()) {
				online.erase(j1);
			}
		}
		else if (ACTION == "PLAY") {
			string j2;
			cin >> j2;
			if (online.find(j1) != online.end() and online.find(j2) != online.end()) {
				playerbase[j1] += 10;
				if (playerbase[j2]-10 >= 1200) playerbase[j2] -= 10;
				else playerbase[j2] = 1200;
			}
			else cout << "jugador(s) no connectat(s)" << endl;
			
		}
		else if (ACTION == "GET_ELO") {
			cout << j1 << " " << playerbase[j1] << endl;
		}
	}
	cout << endl << "RANKING"<< endl;
	vector<pair<string, int>> ranking(playerbase.size());
	int i = 0;
	for (auto x: playerbase) {
		ranking[i] = x;
		i++;
	}
	sort(ranking.begin(), ranking.end(), compa);
	for (auto x: ranking) cout << x.first << " " << x.second << endl;
}