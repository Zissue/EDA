#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <limits>
 
using namespace std;
 
 
typedef pair<double, int> ArcP;
typedef vector< vector<ArcP> > GrafP;
 
int const INFINITY = numeric_limits<int>::max();
 
void dijkstra(const GrafP &G, int x, int y, vector<int> &d,
                     vector<int> &p) {
 
    int n = G.size();
    d = vector<int>(n, INFINITY);
    d[x] = 0;
    p = vector<int>(n, -1);
    vector<bool> S(n, false);   // vector de "encontrados"
    priority_queue<ArcP, vector<ArcP>, greater<ArcP> > Q;
    Q.push(ArcP(0, x));
    int l = 0;
    while (not Q.empty()) {
        int u = Q.top().second;
        Q.pop();
 
        if (not S[u]) {
            S[u] = true;
            if (u == y) return;
            int m = G[u].size();
            for (int i = 0; i < m; ++i) {
                int v = G[u][i].second;
                int c = G[u][i].first;
                if (d[v] > d[u] + c) {
                    d[v] = d[u] + c;
                    p[v] = u;
                    Q.push(ArcP(d[v], v));
                }
            }
        }
    }
}
 
void leer_tripletes(GrafP &G, int m) {
    int aux;
    ArcP arco;
    // G corresponde a una matriz donde el índice de la fila
    // representa un nodo y en cada columna hay un par que es
    // un nodo y un peso. Por lo tanto se puede decir que si juntamos
    // el nodo de la fila + columna, tenemos la arista (y además, el peso)
    for (int i = 0; i < m; i++) {
        cin >> aux >> arco.second >> arco.first;
        G[aux].push_back(arco);
    }
}
 

 
int main() {
        int n;
        int m;
        while (cin >> n >> m) {
            GrafP G(n);
            leer_tripletes(G, m);
            vector<int> d;
            vector<int> p;  // Vector "parents"
 
            // Pos. inicial y final...
            int x, y;
            cin >> x >> y;
            vector<int> camino;
            dijkstra(G, x, y, d, p);
            if (d[y] != INFINITY) mostrar_camino(p, x, y);
            else cout << "no path from " << x << " to " << y << endl;
        }
}