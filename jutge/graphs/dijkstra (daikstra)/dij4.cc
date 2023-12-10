#include <iostream>
#include <queue>
#include <vector>
#include <climits>

using namespace std;

using vI = vector<int>;
using vB = vector<bool>;
using Arc = pair<int,int>;

using Graph = vector<vector<Arc>>;
using Cost = int;
using Node = int;

const int infinite = INT_MAX;

int m;
Graph G;

void readGraph() {
	int u, v, c;
	for (int i = 0; i < m; i++)  {
		cin >> u >> v >> c;
		Arc a = {c, v};
		G[u].push_back(a);
	}
}

pair<int,int> dijkstra(int x, int y /*, vI & path*/) {

	int n = G.size();
	vB visited(n, false);

	vI d(n, infinite);
	d[x] = 0;

	vI ways(n, 0);
	ways[x] = 1;

	priority_queue<Arc, vector<Arc>, greater<Arc>> pq;
	pq.push({0, x});

	while (not pq.empty()) {
		Node node = pq.top().second;
		pq.pop();

		if (not visited[node]) {
			visited[node] = true;

			for (const Arc& a: G[node]) {
				Node neighbour = a.second;
				Cost c = a.first;
				if (d[neighbour] > d[node] + c) {
					d[neighbour] = d[node] + c;
					pq.push({d[neighbour], neighbour});

					ways[neighbour] = ways[node];
					/*path[neighbour] = node;*/
				}
				else if (d[neighbour] == d[node] + c) {
					ways[neighbour] += ways[node];
				}
			}
		}
	}
	return {d[y], ways[y]};
}

int main () {
	int n;

	while (cin >> n >> m) {

		G = Graph(n);
		readGraph();

		int x, y;
		cin >> x >> y;

		/* vI path(n, -1); */ // vector donde se guarda el camino de x a y

		pair<int,int> d = dijkstra(x, y  /*path*/);

		if (d.first == infinite) cout << "no path from " << x << " to " << y;
		else cout << "cost " << d.first << ", " << d.second << " way(s)";
		cout << endl;

	}

}