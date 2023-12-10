#include <iostream>
#include <vector>
#include <climits>
#include <queue>

using namespace std;

using P = pair<int,int>;
using VP = vector<P>;
using MC = vector<vector<char>>;
using MI = vector<vector<int>>;
using MB = vector<vector<bool>>;

const int infinite = INT_MAX;

VP moves = {{1,0}, {0,1}, {-1,0}, {0,-1}};
int n, m;

void readBoard(MC &B) {
	for (auto& f: B)
		for (auto& c: f) cin >> c;
}

bool pos_ok(const MC &B, P p) {
	return p.first >= 0 and
		   p.second >= 0 and
		   p.first < n and
		   p.second < m and
		   B[p.first][p.second] != 'X';
}

int bfs(const MC &B, int x, int y) {
	MI d(n, vector<int>(m, infinite));
	d[x][y] = 0;
	MB visited(n, vector<bool>(m, false));
	queue<P> Q;
	Q.push({x,y});
	int currmax = -1,
		prevmax = -1;
	while (not Q.empty()) {
		P act = Q.front();
		Q.pop();
		if (not visited[act.first][act.second]) {
			visited[act.first][act.second] = true;
			if (B[act.first][act.second] == 't' and d[act.first][act.second] >= currmax) {
				prevmax = currmax;
				currmax = d[act.first][act.second];
			}
			for (P p: moves) {
				P neighbour = {act.first+p.first, act.second+p.second};
				if (pos_ok(B, neighbour) and d[neighbour.first][neighbour.second] == infinite) {
					d[neighbour.first][neighbour.second] = d[act.first][act.second]+1;
					Q.push(neighbour);
				}
			}
		}
	}
	return prevmax;
}

int main () {
	cin >> n >> m;
	MC board(n, vector<char>(m));
	readBoard(board);
	int x, y;
	cin >> x >> y;
	--x; --y;
	int d = bfs(board, x, y);
	if (d == -1) cout << "no es pot arribar a dos o mes tresors";
	else cout << "segona distancia maxima: " << d;
	cout << endl;
}