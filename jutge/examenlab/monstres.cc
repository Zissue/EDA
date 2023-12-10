#include <iostream>
#include <queue>
#include <climits>
#include <vector>
using namespace std;

using MC = vector<vector<char>>;
using MB = vector<vector<bool>>;
using PI = pair<int,int>;
using VPI = vector<PI>;

const int infinite = INT_MAX;

VPI moves = {{1,0}, {-1,0}, {0,1}, {0,-1}};
VPI Mmoves = {{1,0}, {-1,0}, {0,1}, {0,-1}};
int n, m;
MC Board;

PI ReadBoard() {
	PI ini;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> Board[i][j];
			if (Board[i][j] == 'I') ini = {i,j};
	}	}
	return ini;
}

bool pos_ok(PI p) {
	return p.first >= 0 and
		   p.second >= 0 and
		   p.first < n and
		   p.second < m;
}

// Pre: pos_ok(p) is true
bool monster_nearby(PI p) {
	for (auto c: Mmoves) {
		PI pp = {p.first+c.first, p.second+c.second};
		if (pos_ok(pp) and Board[pp.first][pp.second] == 'M') return true;
	}
	return false;
}

bool bfs(PI ini) {
	MB visited(n, vector<bool>(m, false));
	queue<PI> Q;
	Q.push(ini);
	while (not Q.empty()) {
		PI act = Q.front();
		Q.pop();
		if (not visited[act.first][act.second]) {
			visited[act.first][act.second] = true;
			if (Board[act.first][act.second] == 'F') return true;
			for (auto off: moves) {
				PI newp = {act.first+off.first, act.second+off.second};
				if (pos_ok(newp) and not monster_nearby(newp)) {
					Q.push(newp);
				}
			}
		}
	}
	return false;
}

int main () {
	while (cin >> n >> m) {
		Board = MC(n, vector<char>(m));
		PI ini = ReadBoard();
		cout << (bfs(ini) ? "SI" : "NO") << endl;
	}
}