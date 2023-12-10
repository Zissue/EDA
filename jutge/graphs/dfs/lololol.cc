#include <vector> 
#include <iostream> 
using namespace std; 
typedef vector <vector <int> > graph;  // Lista de adyacencia

bool es_arbol (const graph& G, int nodo_padre, int nodo_actual, vector <bool>& vis){
    if (vis[nodo_actual]) return false; 
    vis[nodo_actual] = true; 
    for (int i=0; i<G[nodo_actual].size(); ++i){
        if (G[nodo_actual][i]!=nodo_padre & !es_arbol (G, nodo_actual, G[nodo_actual][i], vis)) return false; 
    }
    return true; 
}

int is_it_forest (const graph& G){
    int n = G.size();
    vector <bool> vis (n, false); 
    int number_of_trees = 0; 
    for (int i=0; i<n; ++i){
        if (!vis[i]) {
            if (es_arbol(G,i,i,vis)) ++ number_of_trees; 
            else return -1; 
        }
    }
    return number_of_trees; 
}

int main (){
    int n,m;
    while (cin >> n >> m){
        graph G (n); 

        int v1, v2; 
        for (int i=0; i<m; ++i) {
            cin >> v1 >> v2; 
            G [v1].push_back(v2); 
            G [v2].push_back(v1); 
        }
        
        int r = is_it_forest (G); 
        if (r==-1) cout << "no" << endl; 
        else cout << r << endl; 
    } 

}   