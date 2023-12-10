#include <iostream>
#include <vector>
using namespace std;

using Vertex = int;
using Graph = vector<vector<Vertex>>;
using VB = vector<bool>;

int n, m;

void ReadGraph(Graph &G) {
	Vertex x, y;
	for (int i = 0; i < m; i++) {
		cin >> x >> y;
		G[x].push_back(y);
		G[y].push_back(x);
	}
}

void te_cicles(const Graph &G, VB &visited, Vertex act, Vertex pare, bool &cicles) {
	if (visited[act]) {
		cicles = true;
		return;
	}
	visited[act] = true;
	for (Vertex v: G[act]) {
		if (v != pare) te_cicles(G, visited, v, act, cicles);
		if (cicles) return;
	}
}

bool te_cicles(const Graph &G, VB &visited, Vertex u) {
	bool cicles = false;
	te_cicles(G, visited, u, u, cicles);
	return cicles;
}

int dfs(const Graph &G) {
	VB visited(n, false);
	int cc = 0;
	for (Vertex u = 0; u < n; u++) {
		if (not visited[u]) {
			if (not te_cicles(G, visited, u)) ++cc;
			else return -1;
		}
	}
	return cc;
}

int main () {
	while (cin >> n >> m) {
		Graph G(n);
		ReadGraph(G);
		int cc = dfs(G);
		if (cc != -1) cout << cc << endl;
		else cout << "no" << endl;
	}
}