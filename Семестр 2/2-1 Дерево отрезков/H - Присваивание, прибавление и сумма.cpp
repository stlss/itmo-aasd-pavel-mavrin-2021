#include <bits/stdc++.h>

using ll = long long;

using namespace std;

struct segment {
	ll sum = 0, operatedValue1 = 0;
	bool operatedValue2 = true;
	int len = 1;

	void operation(ll v1, bool v2) {
		sum = len * v1 + sum * v2;
		operatedValue1 = v1 + operatedValue1 * v2, operatedValue2 *= v2;
	}
};

int n, m, n_;
vector<segment> tree;

void propagate(int i) {
	int l = (i << 1) + 1, r = (i << 1) + 2;
	tree[l].operation(tree[i].operatedValue1, tree[i].operatedValue2);
	tree[r].operation(tree[i].operatedValue1, tree[i].operatedValue2);

	tree[i].operatedValue1 = 0, tree[i].operatedValue2 = true;
}

void operation(int l, int r, ll v1, bool v2, int i, int li, int ri) {
	if (r < li || ri < l)
		return;

	if (l <= li && ri <= r) {
		tree[i].operation(v1, v2);
		return;
	}

	propagate(i);

	int mi = (li + ri) / 2;
	operation(l, r, v1, v2, (i << 1) + 1, li, mi);
	operation(l, r, v1, v2, (i << 1) + 2, mi + 1, ri);

	ll lv = tree[(i << 1) + 1].sum, rv = tree[(i << 1) + 2].sum;
	tree[i].sum = lv + rv;
}

ll sum(int l, int r, int i, int li, int ri) {
	if (r < li || ri < l)
		return 0;

	if (l <= li && ri <= r)
		return tree[i].sum;

	propagate(i);

	int mi = (li + ri) / 2;
	ll r1 = sum(l, r, (i << 1) + 1, li, mi);
	ll r2 = sum(l, r, (i << 1) + 2, mi + 1, ri);

	return r1 + r2;
}

int main() {
	cin >> n >> m;

	n_ = 1;
	while (n_ < n)
		n_ <<= 1;

	tree = vector<segment>(2 * n_ - 1);
	int j = n_ - 1;

	for (int i = j - 1; i >= 0; i--) {
		int l = (i << 1) + 1, r = (i << 1) + 2;
		tree[i].sum = min(tree[l].sum, tree[r].sum);
		tree[i].len = tree[l].len + tree[r].len;
	}

	while (m--) {
		int c, l, r, v;
		cin >> c >> l >> r;

		switch (c)
		{
			case 1:
				cin >> v;
				operation(l, r - 1, v, false, 0, 0, n_ - 1);
				break;

			case 2:
				cin >> v;
				operation(l, r - 1, v, true, 0, 0, n_ - 1);
				break;

			case 3:
				cout << sum(l, r - 1, 0, 0, n_ - 1) << "\n";
				break;
		}
	}

	return 0;
}