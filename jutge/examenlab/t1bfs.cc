#include <vector>
#include <iostream>
#include <queue>
#include <stack>
#include <climits>
using namespace std;

typedef vector<char> filaC;
typedef vector<filaC> matrixC;
typedef vector<int> filaI;
typedef vector<filaI> matrixI;

vector<pair<int, int>> moves = {{0,1}, {0,-1}, {1,0}, {-1,0}};

void readMatrix(matrixC& M) {
    for (int i = 0; i < M.size(); i++)
        for (int j = 0; j < M[0].size(); j++) cin >> M[i][j];
}

bool nice_pos(const matrixC& M, pair<int, int> p) {
    return p.first >= 0 and p.second >= 0 
                        and p.first <= M.size()-1 
                        and p.second <= M[0].size()-1 
                        and M[p.first][p.second] != 'X';
}

bool bfs(const matrixC& M, int x0, int y0) {

    int f = M.size(), c = M[0].size();
    matrixI dist(f, filaI(c, INT_MAX));

    stack<pair<int, int>> Q;
    dist[x0][y0] = 0;
    Q.push({x0, y0});

    while (not Q.empty()) {

        pair<int, int> p = Q.top();
        Q.pop();

        if (M[p.first][p.second] == 't') return true;

        for (pair<int, int> pp : moves) {

            pair<int, int> pos = {pp.first + p.first, pp.second + p.second};

            if (nice_pos(M, pos) and dist[pos.first][pos.second] == INT_MAX) {
                Q.push(pos);
                dist[pos.first][pos.second] = dist[p.first][p.second]+1;
            }
        }
    }
    return false;
}

int main () {

    int f, c;
    cin >> f >> c;

    matrixC M(f, filaC(c));
    readMatrix(M);

    int x0, y0;
    cin >> x0 >> y0;
    x0--; y0--;

    if (bfs(M, x0, y0)) cout << "yes";
    else cout << "no";
    cout << endl;
}