#include <bits/stdc++.h>

using ull = unsigned long long;

using namespace std;

int n, m, n_;
vector<ull> tree;

void set_(int i, ull v) {
	i += n_ - 1;
	tree[i] = v;

	while (i != 0) {
		i = (i - 1) >> 1;
		int l = (i << 1) + 1, r = (i << 1) + 2;
		tree[i] = max(tree[l], tree[r]);
	}
}

int find_no_less_x(int x, int l, int i, int li, int ri) {
	if (tree[i] < x || ri < l)
		return -1;

	if (li == ri)
		return li;

	int m = (li + ri) / 2;
	int result = find_no_less_x(x, l, (i << 1) + 1, li, m);

	if (result == -1)
		result = find_no_less_x(x, l, (i << 1) + 2, m + 1, ri);

	return result;
}

int main() {
	cin >> n >> m;

	n_ = 1;
	while (n_ < n)
		n_ <<= 1;

	tree = vector<ull>(2 * n_ - 1);
	int j = tree.size() - n_;

	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;

		tree[i + j] = x;
	}

	for (int i = j - 1; i >= 0; i--) {
		int l = (i << 1) + 1, r = (i << 1) + 2;
		tree[i] = max(tree[l], tree[r]);
	}


	while (m--) {
		int c, x, y;
		cin >> c >> x >> y;

		switch (c)
		{
			case 1:
				set_(x, y);
				break;

			case 2:
				cout << find_no_less_x(x, y, 0, 0, n_ - 1) << "\n";
				break;
		}
	}

	return 0;
}