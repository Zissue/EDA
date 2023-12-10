#include <vector>
#include <iostream>

using namespace std;

using VE = vector<int>;
using VVE = vector<VE>;

VVE M;
int n, m;

vector<pair<int, int>> moves = {{1,1}, {-1,1}, {1,-1}, {-1,-1}};

// Calcula {total de bishops, caselles valides}
void dfs(int i, int j, int& total, int& valides)
{
    if (i < 0 or j < 0 or i >= n or j >= m) return;
    if (M[i][j] == -1) return;

    total += M[i][j];
    valides++;

    M[i][j] = -1;

    for (auto p: moves)
        dfs(i+p.first, j+p.second, total, valides);
}

int main()
{
    int cases;
    cin >> cases;
    for (int ncase = 0; ncase < cases; ++ncase)
    {
        cin >> n >> m;
        M = VVE(n, VE(m));

        int total_bishops = 0;
        int total_valid = 0;

        for (auto& v : M) {
            for (auto& x : v) {
                string s;
                cin >> s;
                if (s == "X") x = -1;
                else {
                    x = stoi(s);
                    ++total_valid;
                    total_bishops += x;
                }
            }
        }

        // Els possibles moviments formen grafs connexos
        // Nomes necessitem saber si el total de bishops en un subgraf es pot dividir entre el nombre de caselles valides

        bool result = true;

        if (total_valid == 0) result = true;
        else if (total_bishops % total_valid == 0) {
            int ratio = total_bishops / total_valid;

            for (int i = 0; i < n and result; ++i) {
                for (int j = 0; j < m and result; ++j) {
                    int total = 0;
                    int valid = 0;
                    dfs(i, j, total, valid);
                    
                    if (valid != 0 and (total % valid != 0 or total / valid != ratio)) result = false;
                }
            }
        }
        else {
            result = false;
        }

        cout << "Case " << ncase+1 << ": " << (result ? "yes" : "no" ) << endl;
    }
}
