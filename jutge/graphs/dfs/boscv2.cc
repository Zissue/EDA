#include <vector>
#include <iostream>

using namespace std;

// Perque un graf sigui bosc, cada subgraf connex ha de ser un 
// arbre (és a dir, un graf connex i sense cicles)

using Vertex = int;
using Graph = vector<vector<Vertex>>;	// llista d'adjacencia
using VB = vector<bool>;

int n, m;

void readGraph(Graph &G) {
	for (int i = 0; i < m; i++) {
		Vertex x, y;
		cin >> x >> y;
		G[x].push_back(y);
		G[y].push_back(x); // Ja que no es dirigit, bi-direccional
	}
}

void te_cicles(const Graph &G, Vertex pare, Vertex act, VB &visited, bool& cicles) {
	if (visited[act]) {
		cicles = true;
		return;	
	} 
	
	visited[act] = true;

	for (Vertex x: G[act]) {
		if (x != pare) te_cicles(G, act, x, visited, cicles);
		if (cicles) return;
	}
}

bool te_cicles(const Graph &G, Vertex node, VB &visited) {
	bool cicles = false;
	te_cicles(G, node, node, visited, cicles);
	return cicles;
}

//Retorna -1 si te cicles, o el numero de arbres
int dfs(const Graph &G) {

	VB visited(n, false);
	int arbres = 0;

	for (int node = 0; node < n; node++) {
		if (not visited[node]) {
			if (!te_cicles(G, node, visited)) arbres++;
			else return -1;
		}
	}
	return arbres;
}

int main () {

	while (cin >> n >> m) {

		Graph G(n);
		readGraph(G);

		int narbres = dfs(G);
		if (narbres != -1) cout << narbres << endl;
		else cout << "no" << endl;
	}
}