#include <vector>
#include <iostream>
#include <queue>
#include <stack>
#include <climits>
using namespace std;

using Vertex = int;
using Cost = int;
using Arc = pair<Cost,Vertex>;
using Graph = vector<pair<Cost,vector<Arc>>>;
using VI = vector<int>;
using VB = vector<bool>;

const int infinite = INT_MAX;
int n, m;

void readGraph(Graph &G) {
	Vertex x, y;
	Cost c;
	for (int i = 0; i < m; i++) {
		cin >> x >> y >> c;
		G[x].second.push_back({c,y});
		G[y].second.push_back({c,x});
}	}

void readCosts(Graph &G) {
	for (int i = 0; i < n; i++) {
		cin >> G[i].first;
}	}

int costDijkstra(const Graph &G, Vertex ini, Vertex fin) {
	VB visited(n, false);
	VI path(n, -1);
	VI d(n, infinite);
	d[ini] = 0;

	priority_queue<Arc, vector<Arc>, greater<Arc>> pq;
	pq.push({0, ini});

	while (not pq.empty()) {
		Vertex act = pq.top().second;
		pq.pop();
		if (not visited[act]) {
			visited[act] = true;
			for (Arc adj: G[act].second) {
				Vertex neighbour = adj.second;
				Cost c = adj.first;
				Cost until = d[act] + c;
				if (neighbour != fin) until += G[neighbour].first;
				if (d[neighbour] > until) {
					d[neighbour] = until;
					pq.push({d[neighbour], neighbour});
					path[neighbour] = act;
	}	}	}	}
	return d[fin];
}

int main () {
	cin >> n >> m;
	Graph G(n);
	readCosts(G);
	readGraph(G);

	Vertex a, b;
	while (cin >> a >> b) {
		int cost = costDijkstra(G, a, b);
		cout << "c(" << a << "," << b << ") = ";
		if (cost != infinite) cout << cost;
		else cout << "+oo";
		cout << endl;
}	}