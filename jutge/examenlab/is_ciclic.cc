#include <iostream>
#include <vector>
#include <stack>
#include <list>
#include <queue>

using namespace std;

using Vertex = int;
using Graph = vector<vector<Vertex>>;
using VI = vector<int>;

int m;

bool es_ciclic(const Graph &G) {
	int n = G.size();
	VI grad(n, 0);
	for (auto& x: G) {
		for (Vertex v: x){
			++grad[v];
	}	}
	stack<Vertex> S;
	for (Vertex u = 0; u < n; u++)
		if (grad[u] == 0) S.push(u);

	while (not S.empty()) {
		Vertex u = S.top();		S.pop();
		n--;
		for (Vertex adj: G[u]) {
			if (--grad[adj] == 0) S.push(adj);
	}	}
	return n > 0;
}

bool topological_sort(const Graph &G) {

    int n = int(G.size());
    VI graus(n, 0);

    for (const auto &adj: G) 
        for (Vertex v: adj) 
            ++graus[v];

    queue<Vertex> S;
    for (Vertex u = 0; u < n; u++)
        if (graus[u] == 0) S.push(u);

    list<Vertex> Tlist;
    while (not S.empty()) {
        Vertex u = S.front();     S.pop();
        Tlist.push_back(u);
        for (Vertex v: G[u]) {
            if (--graus[v] == 0) S.push(v);
    }   }
    return Tlist.size() != n;
}

void readGraph(Graph &G) {
	int x, y;
	for (int i = 0; i < m; i++) {
		cin >> x >> y;
		G[x].push_back(y);
}	}

int main () {
	int n;
	while (cin >> n >> m) {
		Graph G(n);
		readGraph(G);
		cout << (es_ciclic(G) ? "yes" : "no") << endl;
}	}