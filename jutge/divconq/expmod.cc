#include <iostream>
using namespace std;

int expmod(int n, int k, int m) {
	if (k == 0) return 1;
	else {
		int y = (expmod(n, k/2, m))%m;
		if (k%2 == 0) return (y*y)%m;
		else return (((y*y)%m)*(n%m))%m;
	} 
}

int main() {
	int n, k, m;
	while (cin >> n >> k >> m) {
		cout << expmod(n, k, m) << endl;
	}
}