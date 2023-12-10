#include <vector>
#include <stack>
#include <iostream>
#include <queue>
#include <climits>
using namespace std;

typedef pair<int, int> Arc;
typedef vector<Arc> adjP;
typedef vector<adjP> graphP;

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

stack<int> pathBuilding(const vector<int>& p, int x, int y) {
    stack<int> path;
    while (x != y) {
        path.push(y);
        y = p[y];
    }
    path.push(y);

    return path;
}

int dijkstra(const graphP& G, int x, int y, vector<int>& path) {
    int n = G.size();
    vector<int> d(n, infinite);
    d[x] = 0;

    vector<bool> visited(n, false);

    priority_queue<Arc, vector<Arc>, greater<Arc>> pq;
    pq.push({0, x});

    while (not pq.empty()) {
        Arc aux = pq.top();
        pq.pop();
        
        int p = aux.second;

        if (not visited[p]) {
            visited[p] = true;

            for (Arc a: G[p]) {

                int pnew = a.second;

                if (d[pnew] > d[p] + a.first) {

                    d[pnew] = d[p] + a.first;

                    path[pnew] = p;

                    pq.push({d[pnew], pnew});
                }
            }
        }
    }
    return d[y];
}

int main () {

    int n;
    while (cin >> n >> m) {

        graphP G(n);
        readGraph(G);

        int x, y;
        cin >> x >> y;

        vector<int> p(n);

        int d = dijkstra(G, x, y, p);

        if (d == infinite) cout << "no path from " << x << " to " << y << endl;
        else {
            // cout << "cost " << d << ", ";
            stack<int> path = pathBuilding(p, x, y);
            bool first = true;
            while (not path.empty()) {
                if (!first) cout << " ";
                else first = false;
                cout << path.top();
                path.pop();
            }
            // cout << path.size();
            // cout << " step(s)" << endl;
            cout << endl;
}   }   }