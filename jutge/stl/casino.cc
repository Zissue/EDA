#include <iostream>
#include <map>
using namespace std;

typedef map<string,int> MAP;

int main () {

	MAP playerbase;

	string player;
	string action;

	while (cin >> player >> action) {
		
		if (action != "wins") {
			if (playerbase.find(player) != playerbase.end()) {
				if (action == "enters") {
					cout << player << " is already in the casino" << endl;
				}
				else {
					cout << player << " has won " << playerbase[player] << endl;
					playerbase.erase(playerbase.find(player));
				}
			}
			else {
				if (action == "enters") {
					playerbase.insert(make_pair(player,0));
				}
				else {
					cout << player << " is not in the casino" << endl;
				}
			}
		}
		else {
			int earnings;
			cin >> earnings;
			if (playerbase.find(player) != playerbase.end()) {
				playerbase[player] += earnings;
			}
			else cout << player << " is not in the casino" << endl;
		}

	}
	cout << "----------" << endl;
	for (pair<string,int> p : playerbase) 
		cout << p.first << " is winning " << p.second << endl;
}