#include <iostream>
#include <vector>
using namespace std;

bool asc_dic_search(const vector<int> &v, int x, int l, int r) {
    if (l > r) return false;
    int m = (l+r)/2;
    if (v[m] == x) return true;
    if (x < v[m]) return asc_dic_search(v, x, l, m-1);
    else return asc_dic_search(v, x, m+1, r);
}

bool search(const vector<int>& a, int l, int r, int x) {
    if (l+1 == r) return a[l] == x or a[r] == x;
    int m = (l+r)/2;
    if (a[m] >= a[l]) {
        if (a[l] <= x and x <= a[m]) {
            return asc_dic_search(a, x, l, m+1);
        }
        return search(a, m, r, x);
    }
    else {
        if (a[m] <= x and x <= a[r]) {
            return asc_dic_search(a, x, m, r+1);
        }
        return search(a, l, m, x);
    }
}

bool search(int x, const vector<int>& v){
    return search(v, 0, v.size()-1, x);
}

int main() {
    int n;
    while (cin >> n) {
        vector<int> V(n);
        for (int i = 0; i < n; ++i) cin >> V[i];
        int m;
        cin >> m;
        while (m--) {
          int x;
          cin >> x;
          cout << ' ' << search(x, V);
        }
        cout << endl;
    }
}
