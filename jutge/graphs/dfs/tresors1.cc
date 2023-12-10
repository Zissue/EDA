#include <iostream>
#include <vector>
using namespace std;

typedef char vertex;
typedef vector<vertex> adj;
typedef vector<adj> graph;

typedef vector<bool> fila;
typedef vector<fila> matrix;

int n, m;

void readMap(graph & G) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) cin >> G[i][j];
}

bool search(graph & G, matrix & visited, int f, int c) {
    if (f < n and c < m and f >= 0 and c >= 0) {
        if (not visited[f][c]) {
            visited[f][c] = true;
            if (G[f][c] == 'X') return false;
            else if (G[f][c] == 't') return true;
            else return (search(G, visited, f+1, c) or 
                         search(G, visited, f-1, c) or
                         search(G, visited, f, c+1) or
                         search(G, visited, f, c-1));
        }
        return false;
    }
    return false;
}

int main () {

    cin >> n >> m;
    graph map(n, adj(m));

    readMap(map);

    int f, c;
    cin >> f >> c;

    matrix visited(n, fila(m, false));

    if (search(map, visited, f-1, c-1)) cout << "yes";
    else cout << "no";
    cout << endl;

}