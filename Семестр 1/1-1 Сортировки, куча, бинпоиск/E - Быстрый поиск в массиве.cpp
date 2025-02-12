#include <bits/stdc++.h>

using namespace std;

int left_bin_search(vector<int>& v, int value) {
	int l = -1, r = v.size();
	while (l + 1 != r) {
		int m = (l + r) / 2;

		if (v[m] < value)
			l = m;
		else
			r = m;
	}

	return r;
}

int right_bin_search(vector<int>& v, int value) {
	int l = -1, r = v.size();
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
	int n;
	cin >> n;

	vector<int> v(n);
	for (auto& x : v)
		cin >> x;

	sort(v.begin(), v.end());

	int k;
	cin >> k;

	while (k--) {
		int l, r;
		cin >> l >> r;

		int i = left_bin_search(v, l);
		int j = right_bin_search(v, r);

		cout << j - i << " ";
	}
	
	cout << endl;

	return 0;
}