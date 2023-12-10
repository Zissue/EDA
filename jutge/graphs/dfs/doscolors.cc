#include <iostream>
#include <vector>
using namespace std;

// Two colors == Check if bipartite

typedef int vertex;
typedef vector<vertex> adj;
typedef vector<adj> graph;

int n, m;

void readGraph(graph& G) {

    for (int i = 0; i < m; i++) {

        int x, y; 
        cin >> x >> y;

        G[x].push_back(y);
        G[y].push_back(x);
    }
}

bool is_bipartite(const graph& G, int i, vector<bool>& visited, vector<int>& color) {

    for (int u : G[i]) {

        if (not visited[u]) {

            visited[u] = true;
            color[u] = not color[i];

            if (not is_bipartite(G, u, visited, color)) return false;
        }
        else if (color[i] == color[u]) return false;
    }
    return true;
}


int main () {

    while (cin >> n >> m) {

        if (m == 0 or n == 0) cout << "yes";
        else {

            graph G(n);
            readGraph(G);

            bool bipartite = true;

            vector<int> color(n);
            vector<bool> visited(n, false);

            for (int i = 0; i < n and bipartite; i++) {
                if (not visited[i]) {
                    visited[i] = true;
                    color[i] = 0;
                    bipartite = is_bipartite(G, i, visited, color);
                }
            }
            cout << (bipartite ? "yes" : "no");
        }
        cout << endl;
    }
}