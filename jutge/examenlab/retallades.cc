#include <iostream>
#include <queue>
#include <vector>
using namespace std;

using Vertex = int;
using Cost = int;
using Arc = pair<Cost,Vertex>;
using Graph = vector<vector<Arc>>;
using VB = vector<bool>;

int n, m;
Cost sum = 0;		// Cost de manteniment de totes les carreteres

void ReadGraph(Graph &G) {
	Cost c;
	Vertex x, y;
	for (int i = 0; i < m; i++) {
		cin >> x >> y >> c;
		G[x].push_back({c,y});
		G[y].push_back({c,x});
		sum += c;
	}
}

int mst(const Graph &G) {
	int costcami = 0;			//cost del camí mínim
	VB visited(n, false);
	priority_queue<Arc, vector<Arc>, greater<Arc>> pq;
	pq.push({0, 0});
	while (not pq.empty()) {
		Vertex u = pq.top().second;
		Cost c = pq.top().first;
		pq.pop();
		if (not visited[u]) {
			visited[u] = true;
			costcami += c;
			for (Arc a: G[u]) pq.push(a);
		}
	}
	return costcami;
}

int main () {
	while (cin >> n >> m) {
		sum = 0;
		Graph G(n);
		ReadGraph(G);

		int cami = bfs(G);
		cout << sum - cami << endl;
	}
}