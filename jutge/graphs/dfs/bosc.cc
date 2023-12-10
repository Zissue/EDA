#include <vector>
#include <iostream>
using namespace std;

typedef int vertex;
typedef vector<vertex> adj;
typedef vector<adj> graph;

typedef vector<bool> vlist;
typedef vector<vlist> matrix;

int n, m;
bool cicle = false;

void buildGraph(graph& G) {
	for (int i = 0; i < m; i++) {

		int x, y;
		cin >> x >> y;

		// Adyacency list
		G[x].push_back(y);
		G[y].push_back(x);
	}
}

void search_cicles(const graph& G, int u, vector<bool>& visited, int pare, bool& cicle) {
	if (!visited[u]) {
		visited[u] = true;
		for (vertex x: G[u]) {
			if (x != pare) search_cicles(G, x, visited, u, cicle);
			if (cicle) return;
		}
	}
	else cicle = true;
}

void DFS(const graph& G, vector<bool>& visited, int& arbres) {

	int size = G.size();

	for (int u = 0; u < size; ++u) {
		if (!visited[u]) {
			cicle = false;
			search_cicles(G, u, visited, u, cicle);
			if (!cicle) arbres++;
			else return;
		}
	}
}

int main () {

	while (cin >> n >> m) {

		graph G(n);

		buildGraph(G);

		vlist visited(n, false);
		int arbres = 0;

		DFS(G, visited, arbres);

		if (!cicle) cout << arbres;
		else cout << "no";
		cout << endl;
	}
}