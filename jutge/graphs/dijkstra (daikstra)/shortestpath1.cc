#include <vector>
#include <iostream>
#include <queue>
#include <climits>
using namespace std;

typedef pair<int, int> Arc;
typedef vector<Arc> adjP;
typedef vector<adjP> graphP;

const int infinit = INT_MAX;
int m;

// Reads the adjacency list of a directed graphP
void readGraph(graphP& G) {
    for (int i = 0; i < m; i++) {   //      c
        int u, v, c;                // (u) ---> (v)         with cost: c
        cin >> u >> v >> c;
        G[u].push_back({c, v});
    }
}

int dijkstra(const graphP& G, int x, int y) {
    int n = G.size();
    vector<int> dist(n, infinit);
    dist[x] = 0;

    vector<bool> visited(n, false);

    priority_queue<Arc, vector<Arc>, greater<Arc>> pq;
    pq.push({0, x});

    while (not pq.empty()) {
        Arc aux = pq.top();
        pq.pop();

        if (not visited[aux.second]) {
            visited[aux.second] = true;

            for (Arc a: G[aux.second]) {
                if (dist[a.second] > dist[aux.second] + a.first) {
                    dist[a.second] = dist[aux.second] + a.first;
                    pq.push({dist[a.second], a.second});
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

        int d = dijkstra(G, x, y);
        if (d != INT_MAX) cout << d;
        else cout << "no path from " << x << " to " << y;
        cout << endl;
    }

}