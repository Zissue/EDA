#include <vector>
#include <iostream>

using namespace std;

using filaI = vector<int>;
using matrixI = vector<filaI>;

int n, m;
matrixI board;

vector<pair<int, int>> moves = {{1,1}, {-1,1}, {1,-1}, {-1,-1}};

bool pos_ok(int i, int j) {
    return i >= 0 and j >= 0 and i < n and j < m;
}

void dfs(int i, int j, int& total, int& valid) {
    if (not pos_ok(i, j)) return;
    if (board[i][j] == -1) return;

    total += board[i][j];
    valid++;

    board[i][j] = -1;

    for (auto p: moves)
        dfs(i+p.first, j+p.second, total, valid);
}

int main () {
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        
        cin >> n >> m;

        board = matrixI(n, filaI(m));

        int countB = 0;
        int countV = 0;

        string s;
        for (auto& x: board) {
            for (int& y: x) {
                cin >> s;
                if (s == "X") y = -1;
                else {
                    y = stoi(s);
                    ++countV;
                    countB += y;
                }
            }
        }

        bool ans = true;

        if (countV == 0) ans = true;
        else if (countB % countV == 0) {
            int ratio = countB / countV;

            for (int j = 0; j < n and ans; j++) {
                for (int w = 0; w < m and ans; w++) {

                    int total = 0,
                        valid = 0;

                    dfs(j, w, total, valid);
                    if (valid != 0 and (total % valid != 0 or total/valid != ratio)) ans = false;
                }
            }
        }
        else ans = false;

        cout << "Case " << i << ": " << (ans ? "yes" : "no") << endl;
    }
}