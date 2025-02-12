#include <bits/stdc++.h>

using ull = unsigned long long;

using namespace std;

int n, k;
vector<int> v;

bool f(ull x) {
	ull sum = 0;
	int k_ = 0;

	for (int i = 0; i < n; i++) {
		if (v[i] > x)
			return false;

		if (sum + v[i] > x) {
			sum = v[i];
			k_++;
		}
		else
			sum += v[i];
	}

	return k_ < k;
}

int main() {
	cin >> n >> k;

	v = vector<int>(n);
	for (auto& x : v)
		cin >> x;

	ull l = 0, r = 1;
	while (!f(r))
		r *= 2;

	while (l + 1 != r) {
		ull m = l + (r - l) / 2;

		if (f(m))
			r = m;
		else
			l = m;
	}

	cout << r << endl;

	return 0;
}