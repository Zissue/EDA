#include <vector>
#include <iostream>
#include <queue>
#include <list>
#include <map>
using namespace std;

int main () {
    map<string, int> m;
    int i = 0;
    string s;
    while (cin >> s) {
        m.insert({s,i++});
        for (auto x: m) cout << x.first << "     " << x.second << endl;
    }
}



























// list<int> ordenacio_topologica (Graph& G) {
//     int n = int(G.size());
//     priority_queue<int, vector<int>, greater<int>> cua;
    
//     vector<int> ge(n, 0);
    
//     for (int u = 0; u < n; ++u) {
//         for (int i = 0; i < G[u].size(); ++i) {
//             ++ge[G[u][i]];
//         }
        
//     }

//     for (int u = 0; u < n; ++u) {
//         if (ge[u] == 0) {
//             cua.push(u);
//         }
        
//     }
//     list<int> L;
//     while (not cua.empty()) {
//         int u = cua.top(); cua.pop();
//         L.push_back(u);
//         for (int i = 0; i < G[u].size(); ++i) {
//             int v = G[u][i];
//             if (--ge[v] == 0) {
//                  cua.push(v);
//             }
//         }
        
//     }
//     return L;
    
// }