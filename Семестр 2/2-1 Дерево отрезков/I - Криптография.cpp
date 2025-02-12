#include <bits/stdc++.h>

using ll = long long;

using namespace std;

struct matrix {
	ll v1 = 1, v2 = 0, v3 = 0, v4 = 1;
};

int r, n, m, n_;
vector<matrix> tree;
matrix identityMatrix;

matrix multiply(matrix mtr1, matrix mtr2) {
	auto mtr = matrix();
	mtr.v1 = (mtr1.v1 * mtr2.v1 + mtr1.v2 * mtr2.v3) % r;
	mtr.v2 = (mtr1.v1 * mtr2.v2 + mtr1.v2 * mtr2.v4) % r;
	mtr.v3 = (mtr1.v3 * mtr2.v1 + mtr1.v4 * mtr2.v3) % r;
	mtr.v4 = (mtr1.v3 * mtr2.v2 + mtr1.v4 * mtr2.v4) % r;
	return mtr;
}

matrix segment_value(int l, int r, int i, int li, int ri) {
	if (r < li || ri < l)
		return identityMatrix;

	if (l <= li && ri <= r)
		return tree[i];

	int m = (li + ri) / 2;
	auto mtr1 = segment_value(l, r, (i << 1) + 1, li, m);
	auto mtr2 = segment_value(l, r, (i << 1) + 2, m + 1, ri);

	return multiply(mtr1, mtr2);
}

int main() {
	cin >> r >> n >> m;

	n_ = 1;
	while (n_ < n)
		n_ <<= 1;

	tree = vector<matrix>(2 * n_ - 1);
	int j = n_ - 1;

	for (int i = 0; i < n; i++) {
		ll v1, v2, v3, v4;
		cin >> v1 >> v2 >> v3 >> v4;

		tree[i + j] = matrix{ v1, v2, v3, v4 };
	}

	for (int i = j - 1; i >= 0; i--) {
		int l = (i << 1) + 1, r = (i << 1) + 2;
		tree[i] = multiply(tree[l], tree[r]);
	}

	while (m--) {
		int l, r;
		cin >> l >> r;

		auto mtr = segment_value(l - 1, r - 1, 0, 0, n_ - 1);
		cout << mtr.v1 << " " << mtr.v2 << "\n" << mtr.v3 << " " << mtr.v4 << "\n\n";
	}

	return 0;
}