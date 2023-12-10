#include <iostream>
#include <vector>
using namespace std;

void readVector(vector<int>& v) {
	for (int i = 0; i < v.size(); i++) cin >> v[i];
}

int merge(vector<int>& v, int l, int m, int r) {
	vector<int> aux(r - l + 1);
	int inv = 0;			// # inversions
	int i = l;	int j = m+1; int k = 0;
	while (i <= m and j <= r) {
		if (v[i] <= v[j]) {
			aux[k] = v[i];
			++i;
			++k;
		}
		else {
			aux[k] = v[j];
			++j;
			++k;
			inv += m-i + 1;
		}
	}
	while (i <= m) {
		aux[k] = v[i];
		++i;
		++k;
	}
	while (j <= r) {
		aux[k] = v[j];
		++j;
		++k;
	}
	for (int p = 0; p < (r-l+1); ++p) v[l+p] = aux[p];
	return inv;
}

int merge_sort(vector<int>& v, int l, int r) {
	if (l >= r) return 0;
	else {
		int m = (l+r)/2;
		return (merge_sort(v, l, m) + 
				merge_sort(v, m+1, r) +
				merge(v, l, m, r));
	}
}

int merge_sort(vector<int>& v) {
	return merge_sort(v, 0, v.size()-1);
}

int main () {
	int n;
	while (cin >> n) {
		vector<int> seq(n);
		readVector(seq);
		cout << merge_sort(seq) << endl;
	}
}