#include <vector>
#include <iostream>
#include <queue>
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

int bfs(const matrixC& T, int x0, int y0) {

    int f = T.size(), c = T[0].size();
    matrixI DD(f, filaI(c, INT_MAX));

    int maxT = 0;

    DD[x0][y0] = 0;
    queue<pair<int, int>> Q;
    Q.push({x0, y0});

    while( not Q.empty()) {

        pair<int, int> pare = Q.front();
        Q.pop();

        if (T[pare.first][pare.second] == 't' and maxT < DD[pare.first][pare.second]) 
            maxT = DD[pare.first][pare.second];

        for (auto m : moves) {
            pair<int, int> aux = {m.first+pare.first, m.second+pare.second};
            if (nice_pos(T, aux) and DD[aux.first][aux.second] == INT_MAX) {
                Q.push(aux);
                DD[aux.first][aux.second] = DD[pare.first][pare.second]+1;
            }
        }
    }
    if (maxT != 0) return maxT;
    else return -1;
}

int main () {

    int f, c;
    cin >> f >> c;

    matrixC M(f, filaC(c));
    readMatrix(M);

    int x0, y0;
    cin >> x0 >> y0;
    x0--; y0--;

    int dist = bfs(M, x0, y0);
    if (dist != -1) cout << "distancia maxima: " << dist;
    else cout << "no es pot arribar a cap tresor";
    cout << endl;
}