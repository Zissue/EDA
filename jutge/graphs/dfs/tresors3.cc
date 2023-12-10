#include <iostream>
#include <vector>
using namespace std;

typedef char vertex;
typedef vector<vertex> adj;
typedef vector<adj> graph;

typedef vector<bool> fila;
typedef vector<fila> matrix;

int n, m, counter = 0;

void readMap(graph & G) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) cin >> G[i][j];
}

void search(graph & G, matrix & visited, int f, int c) {
    if (f < n and c < m and f >= 0 and c >= 0) {
        if (not visited[f][c]) {
            visited[f][c] = true;
            if (G[f][c] == 'X') return;
            else {
                if (G[f][c] == 't') counter++;
                search(G, visited, f+1, c); 
                search(G, visited, f-1, c);
                search(G, visited, f, c+1);
                search(G, visited, f, c-1);
            }
        }
        return;
    }
    return;
}

int main () {

    cin >> n >> m;
    graph map(n, adj(m));

    readMap(map);

    int f, c;
    cin >> f >> c;

    matrix visited(n, fila(m, false));
    search(map, visited, f-1, c-1);
    cout << counter << endl;

}