#include <vector>
#include <iostream>

using namespace std;

using Vertex = int;
using Graph = vector<vector<Vertex>>;
using IV = vector<int>;
using BV = vector<bool>;

int n, m;

void readGraph(Graph &G) {
	Vertex x, y;
	for (int i = 0; i < m; i++) {
		cin >> x >> y;
		G[x].push_back(y);
		G[y].push_back(x);
	}
}

bool is_bipartite(const Graph &G, Vertex act, BV &visited, IV &colors) {
	for (Vertex v: G[act]) {
		if (not visited[v]) {
			visited[v] = true;
			colors[v] = not colors[act];
			if (not is_bipartite(G, v, visited, colors)) return false; 
		}
		else if (colors[act] == colors[v]) return false;
	}
	return true;
}

bool dfs(const Graph &G) {
	BV visited(n, false);
	IV colors(n);
	bool bipartite = true; 				// Asumin que si ho es

	for (Vertex u = 0; u < n and bipartite; u++) {
		if (not visited[u]) {
			visited[u] = true;
			colors[u] = 0;
			bipartite = is_bipartite(G, u, visited, colors);
		}
	}
	return bipartite;
}

int main () {

	while (cin >> n >> m) {

		if (n == 0 or m == 0) {
			cout << "yes" << endl;
		}
		else {
			Graph G(n);
			readGraph(G);

			cout << (dfs(G) ? "yes" : "no") << endl;
		}
	}
}