#include <vector>
#include <stack>
#include <iostream>
#include <queue>
#include <climits>
using namespace std;

		  // cost, dest
typedef pair<int, int> Arc;
typedef vector<vector<Arc>> graphP;

const int infinite = INT_MAX;
int m;

// Reads the adjacency list of a directed graphP
void readGraph(graphP& G) {
    for (int i = 0; i < m; i++) {   //      c
        int u, v, c;                // (u) ---> (v)         with cost: c
        cin >> u >> v >> c;
        G[u].push_back({c, v});
    }
}

int dijkstra(const graphP& G, int x, int y, vector<int>& path, vector<int>& steps) {
    int n = G.size();
    vector<int> dist(n, infinite);
    dist[x] = 0;
    // steps[x] = 0;
    // vector<bool> visited(n, false);

    priority_queue<Arc, vector<Arc>, greater<Arc>> pq;
    pq.push({0, x});

    while (not pq.empty()) {
        Arc aux = pq.top();
        pq.pop();

        if (dist[aux.second] != infinite) {
            // visited[aux.second] = true;

            for (Arc a: G[aux.second]) {
                if (dist[a.second] > dist[aux.second] + a.first) {
                    dist[a.second] = dist[aux.second] + a.first;
                    pq.push({dist[a.second], a.second});
                    path[a.second] = aux.second;
                    steps[a.second] = steps[aux.second] + 1;
                }
                else if ((dist[a.second] == dist[aux.second] + a.first) 
                			and steps[a.second] > steps[aux.second] + 1) {
                    steps[a.second] = steps[aux.second] + 1;
                }
            }
        }
    }
    return dist[y];
}

int main () {

    int n;
    while (cin >> n >> m) {

        graphP G(n);
        readGraph(G);

        int x, y;
        cin >> x >> y;

        vector<int> p(n);
        vector<int> steps(n, 0);
        int d = dijkstra(G, x, y, p, steps);

        if (d == infinite) cout << "no path from " << x << " to " << y << endl;
        else {
            cout << "cost " << d << ", ";
            cout << steps[y];
            cout << " step(s)" << endl;
        }
    }
}