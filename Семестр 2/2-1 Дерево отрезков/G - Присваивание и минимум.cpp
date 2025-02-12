#include <bits/stdc++.h>

using ll = long long;

using namespace std;

int n, m, n_;
vector<pair<int, ll>> tree;

void propagate(int i) {
	if (tree[i].second == INT32_MAX)
		return;

	int l = (i << 1) + 1, r = (i << 1) + 2;
	tree[l].first = tree[i].second, tree[l].second = tree[i].second;
	tree[r].first = tree[i].second, tree[r].second = tree[i].second;

	tree[i].second = INT32_MAX;
}

void assign(int l, int r, ll v, int i, int li, int ri) {
	if (r < li || ri < l)
		return;

	if (l <= li && ri <= r) {
		tree[i].first = v, tree[i].second = v;
		return;
	}

	propagate(i);

	int mi = (li + ri) / 2;
	assign(l, r, v, (i << 1) + 1, li, mi);
	assign(l, r, v, (i << 1) + 2, mi + 1, ri);

	ll lv = tree[(i << 1) + 1].first, rv = tree[(i << 1) + 2].first;
	tree[i].first = min(lv, rv);
}

int min_(int l, int r, int i, int li, int ri) {
	if (r < li || ri < l)
		return INT32_MAX;

	if (l <= li && ri <= r)
		return tree[i].first;

	propagate(i);

	int mi = (li + ri) / 2;
	ll r1 = min_(l, r, (i << 1) + 1, li, mi);
	ll r2 = min_(l, r, (i << 1) + 2, mi + 1, ri);

	return min(r1, r2);
}

int main() {
	cin >> n >> m;

	n_ = 1;
	while (n_ < n)
		n_ <<= 1;

	tree = vector<pair<int, ll>>(2 * n_ - 1, { INT32_MAX, INT32_MAX });
	int j = n_ - 1;

	for (int i = 0; i < n; i++)
		tree[i + j].first = 0;

	for (int i = j - 1; i >= 0; i--) {
		int l = (i << 1) + 1, r = (i << 1) + 2;
		tree[i].first = min(tree[l].first, tree[r].first);
	}

	while (m--) {
		int c, l, r, v;
		cin >> c >> l >> r;

		switch (c)
		{
			case 1:
				cin >> v;
				assign(l, r - 1, v, 0, 0, n_ - 1);
				break;

			case 2:
				cout << min_(l, r - 1, 0, 0, n_ - 1) << "\n";
				break;
		}
	}

	return 0;
}