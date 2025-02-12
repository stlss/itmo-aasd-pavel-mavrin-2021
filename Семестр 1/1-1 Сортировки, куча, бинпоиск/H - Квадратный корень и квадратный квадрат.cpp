#include <bits/stdc++.h>

using namespace std;

long double f(long double x) {
	return pow(x, 2) + sqrt(x);
}

int main() {
	long double c;
	cin >> c;

	long double l = 0, r = 1e5;
	while (r - l > 1e-7) {
		long double m = (l + r) / 2;

		if (f(m) > c)
			r = m;
		else
			l = m;
	}

	cout << setprecision(19) << (l + r) / 2 << endl;

	return 0;
}