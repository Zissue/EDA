#include <iostream>
#include <vector>

using namespace std;

using matrixC = vector<vector<char>>;
using matrixB = vector<vector<bool>>;

int n, m;
matrixC taulell;
matrixB visited;

vector<pair<int, int>> mov = {{1,0}, {-1,0}, {0,1}, {0,-1}};

bool pos_ok(int i, int j) { return i >= 0 and j >= 0 and i < n and j < m; }

void dfs(int i, int j, char c) {
   if (not pos_ok(i, j)) return;
   if (taulell[i][j] == '#') return;

   if (not visited[i][j]) {
      visited[i][j] = true;
      
      taulell[i][j] = c;
      
      for (auto m: mov) dfs(i+m.first, j+m.second, c);
   }
}

int main () {

   while (cin >> n >> m) {

      taulell = matrixC(n, vector<char>(m));
      visited = matrixB(n, vector<bool>(m, false));

      for (auto& x: taulell)
         for (auto& c: x)
            cin >> c;
      
      for (int i = 0; i < n; i++) {
         for (int j = 0; j < m; j++) {
            if (taulell[i][j] != '#' and taulell[i][j] != '.') {
               dfs(i, j, taulell[i][j]);
            }
         }
      }

      for (const auto& x: taulell) {
         for (const auto& c: x) cout << c;
         cout << endl;
      }
      cout << endl;
   }
}