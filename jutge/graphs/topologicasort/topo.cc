#include <iostream>
#include <list>
#include <queue>
#include <vector>

using namespace std;

using Vertex = int;
using Graph = vector<vector<Vertex>>;
using VI = vector<int>;

int m;

void readGraph(Graph &G) {
    Vertex x, y;
    for (int i = 0; i < m; i++) {
        cin >> x >> y;
        G[x].push_back(y);
    }
}

list<Vertex> topological_sort(const Graph &G) {

    int n = int(G.size());
    VI graus(n, 0);

    for (const auto &adj: G) 
        for (Vertex v: adj) 
            ++graus[v];

    priority_queue<Vertex, vector<Vertex>, greater<Vertex>> S;
    for (Vertex u = 0; u < n; u++)
        if (graus[u] == 0) S.push(u);

    list<Vertex> Tlist;
    while (not S.empty()) {
        Vertex u = S.top();     S.pop();
        Tlist.push_back(u);
        for (Vertex v: G[u]) {
            if (--graus[v] == 0) S.push(v);
    }   }
    return Tlist;
}

int main () {

    int n;
    while (cin >> n >> m) {

        Graph G(n);
        readGraph(G);

        list<Vertex> topoList = topological_sort(G);

        bool first = true;
        for (Vertex v: topoList) {
            if (!first) cout << " ";
            else first = false;
            cout << v;
        }
        cout << endl;
    }
}
