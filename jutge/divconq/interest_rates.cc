#include <iostream>
using namespace std;

double fast_expo(double n, int k) {
	if (k == 0) return 1;
	else {
		double y = fast_expo(n, k/2);
		if (k%2 == 0) return y*y;
		else return y*y*n;
	} 
}

int binary_day_search(int l, int r, double bank_int, double money, double fixm) {
	if (l <= r) {
		int day = (l+r)/2;
		double bank = fast_expo(bank_int, day) * money;
		double friendd = fixm * day + money;

		if (friendd > bank) return binary_day_search(day+1, r, bank_int, money, fixm);
		else if (friendd < bank) return binary_day_search(l, day-1, bank_int, money, fixm);
		else return day;
	}
	else return l;
}

int main () {

	// INPUT:
	// m: money lent
	// f: fixed amount of money charged to his friend
	// r: % daily interest rate offered by the bank
	// 		daily_bank_interest = (r/100)+1

	// OUTPUT:
	// d: days before returning money to get a better deal than bank's offer

	// 		f*d + m     <     daily_bank_interest^d * m

	double money, fixm, r;
	while (cin >> money >> fixm >> r) {
		 double daily_bank_int = (r / 100)+1;
		 cout << binary_day_search(1, 10000000, daily_bank_int, money, fixm) << endl;
	}
}