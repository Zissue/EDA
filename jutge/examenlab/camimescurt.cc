#include <iostream>
#include <climits>
#include <queue>
#include <stack>
#include <list>
#include <vector>
using namespace std;

using Vertex = int;
using Graph = vector<vector<Vertex>>;
using VI = vector<int>;
using VB = vector<bool>;

const int infinite = INT_MAX;
int n, m;

void readGraph(Graph &G) {
	Vertex x, y;
	for (int i = 0; i < m; i++) {
		cin >> x >> y;
		G[x].push_back(y);
	}
}

list<Vertex> bfs(const Graph &G) {
	VB visited(n, false);
	VI d(n, infinite);
	d[0] = 0;
	VI path(n, -1);
	stack<Vertex> pq;
	pq.push(0);
	bool stop = false;
	while (not pq.empty() and not stop) {
		Vertex act = pq.top();
		pq.pop();
		if (act == n-1) stop = true;
		if (not visited[act]) {
			visited[act] = true;
			for (Vertex adj: G[act]) {
				if (d[adj] == infinite) {
					d[adj] = d[act]+1;
					pq.push(adj);
					path[adj] = act;
				}
			}
		}
	}
	stack<Vertex> S;
	Vertex curr = n-1;
	while (curr != 0) {
		S.push(curr);
		curr = path[curr];
	}
	S.push(curr);
	list<Vertex> ans;
	while (not S.empty()) {
		Vertex aux = S.top();
		ans.push_back(aux);
		S.pop();
	}
	return ans;
}

int main () {
	while (cin >> n >> m) {
		Graph G(n);
		readGraph(G);
		list<Vertex> res = bfs(G);
		bool first = true;
		for (auto x: res) {
			if (!first) cout << " ";
			else first = false;
			cout << x;
		}
		cout << endl;
	}
}