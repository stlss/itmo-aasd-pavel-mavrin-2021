#include <bits/stdc++.h>

using namespace std;

int right_bin_search(vector<int>& v, int value) {
	int l = 0, r = v.size();
	while (l + 1 != r) {
		int m = (l + r) / 2;

		if (v[m] <= value)
			l = m;
		else
			r = m;
	}

	return r;
}

int main() {
	int n, k;
	cin >> n >> k;

	vector<int> v(n);
	for (auto& x : v)
		cin >> x;

	while (k--) {
		int x;
		cin >> x;

		int i = right_bin_search(v, x);
		if (i == v.size()) {
			cout << v.back() << " ";
			continue;
		}

		int j = i - 1;
		if (j == -1) {
			cout << v.front() << " ";
			continue;
		}

		if (x - v[j] <= v[i] - x)
			cout << v[j] << " ";
		else
			cout << v[i] << " ";
	}

	cout << endl;

	return 0;
}