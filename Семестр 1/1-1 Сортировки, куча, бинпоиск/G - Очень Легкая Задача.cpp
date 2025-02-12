#include <bits/stdc++.h>

using namespace std;

int n, x, y;

bool f(int time) {
	if (time < x)
		return false;

	time -= x;
	int cnt1 = time / x;
	int cnt2 = time / y;

	return cnt1 + cnt2 + 1 >= n;
}

int main() {
	cin >> n >> x >> y;

	if (x > y)
		swap(x, y);

	int l = 0, r = 1;
	while (!f(r))
		r *= 2;

	while (l + 1 != r) {
		int m = l + (r - l) / 2;

		if (f(m))
			r = m;
		else
			l = m;
	}

	cout << r << endl;

	return 0;
}