#include <iostream>
#include <vector>

using namespace std;

using Board = vector<vector<char>>;
using MB = vector<vector<bool>>;
using vP = vector<pair<int,int>>;

int n, m, counter = 0;

bool pos_ok(int i, int j) {
	return i >= 0 and j >= 0 and i < n and j < m;
}

bool dfs(const Board &B, int x, int y, MB &visited) {
	if (not pos_ok(x, y)) return false;
	if (visited[x][y]) return false;

	visited[x][y] = true;

	if (B[x][y] == 't') counter++;
	else if (B[x][y] == 'X') return false;

	return dfs(B, x+1, y, visited) or
		   dfs(B, x-1, y, visited) or
		   dfs(B, x, y+1, visited) or
		   dfs(B, x, y-1, visited);
}

int main () {

	cin >> n >> m;

	Board G(n, vector<char>(m));

	for (auto& f: G)
		for (auto& c: f) cin >> c;

	int x, y;
	cin >> x >> y;
	x--; y--;

	MB visited(n, vector<bool>(m, false));

	dfs(G, x, y, visited);
	cout << counter << endl;

}