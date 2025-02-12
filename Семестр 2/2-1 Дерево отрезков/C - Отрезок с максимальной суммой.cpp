#include <bits/stdc++.h>

using ll = long long;

using namespace std;

struct sum_segment {
	ll value, maxSubValue, maxPrefix, maxSuffix;

	sum_segment() {
		value = 0, maxSubValue = 0, maxPrefix = 0, maxSuffix = 0;
	}

	sum_segment(ll v) {
		value = v;

		if (v > 0)
			maxSubValue = v, maxPrefix = v, maxSuffix = v;
		else
			maxSubValue = 0, maxPrefix = 0, maxSuffix = 0;
	}
};

int n, m, n_;
vector<sum_segment> tree;

sum_segment func(sum_segment s1, sum_segment s2) {
	auto s = sum_segment(s1.value + s2.value);

	s.maxPrefix = max(s1.maxPrefix, s1.value + s2.maxPrefix);
	s.maxSuffix = max(s2.maxSuffix, s2.value + s1.maxSuffix);
	s.maxSubValue = max(s1.maxSuffix + s2.maxPrefix, max(s1.maxSubValue, s2.maxSubValue));

	return s;
}

void set_(int i, ll v) {
	i += n_ - 1;
	tree[i] = v;

	while (i != 0) {
		i = (i - 1) >> 1;
		int l = (i << 1) + 1, r = (i << 1) + 2;
		tree[i] = func(tree[l], tree[r]);
	}
}

int main() {
	cin >> n >> m;

	n_ = 1;
	while (n_ < n)
		n_ <<= 1;

	tree = vector<sum_segment>(2 * n_ - 1);
	int j = tree.size() - n_;

	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;

		tree[i + j] = sum_segment(x);
	}

	for (int i = j - 1; i >= 0; i--) {
		int l = (i << 1) + 1, r = (i << 1) + 2;
		tree[i] = func(tree[l], tree[r]);
	}

	cout << tree.front().maxSubValue << "\n";

	while (m--) {
		int i, v;
		cin >> i >> v;

		set_(i, v);

		cout << tree.front().maxSubValue << "\n";
	}

	return 0;
}