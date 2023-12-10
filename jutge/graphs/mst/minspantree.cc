#include <iostream>
#include <vector>
#include <queue>

using namespace std;

using Vertex = int;
using Cost = int;
using Arc = pair<Cost,Vertex>;
using Graph = vector<vector<Arc>>;
using IV = vector<int>;
using BV = vector<bool>;

int m;

void ReadGraph(Graph &G) {
	Vertex u, w;
	Cost c;
	for (int i = 0; i < m; i++) {
		cin >> u >> w >> c;
		--u;	--w;
		G[u].push_back({c,w});
		G[w].push_back({c,u});
	}
}

// Prim's Algorithm to get the minimum spanning tree
int minimum_spanning_tree(const Graph &G) {
	int n = G.size();
	int sum = 0;
	BV visited(n, false);
	priority_queue<Arc, vector<Arc>, greater<Arc>> pq;
	pq.push({0, 0});
	while (not pq.empty()) {
		Vertex v = pq.top().second;
		Cost c = pq.top().first;
		pq.pop();
		if (not visited[v]) {
			visited[v] = true;
			sum += c;
			for (Arc a: G[v]) pq.push(a);
		}
	}
	return sum;
}

int main () {
	int n;
	while (cin >> n >> m) {
		Graph G(n);
		ReadGraph(G);
		cout << minimum_spanning_tree(G) << endl;
	}
}