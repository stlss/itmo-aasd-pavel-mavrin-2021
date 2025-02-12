#include <bits/stdc++.h>

using namespace std;

int n, m, n_;
vector<int> tree;

void inverse(int i) {
	i += n_ - 1;
	tree[i] = abs(tree[i] - 1);

	while (i != 0) {
		i = (i - 1) >> 1;
		int l = (i << 1) + 1, r = (i << 1) + 2;
		tree[i] = tree[l] + tree[r];
	}
}

int find_one(int k) {
	int i = 0, l = 1, r = 2;

	while (l < tree.size()) {
		if (tree[l] >= k)
			i = l;
		else
			i = r, k -= tree[l];

		l = (i << 1) + 1, r = (i << 1) + 2;
	}

	return i - n_ + 1;
}

int main() {
	cin >> n >> m;

	n_ = 1;
	while (n_ < n)
		n_ <<= 1;

	tree = vector<int>(2 * n_ - 1);
	int j = tree.size() - n_;

	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;

		tree[i + j] = x;
	}

	for (int i = j - 1; i >= 0; i--) {
		int l = (i << 1) + 1, r = (i << 1) + 2;
		tree[i] = tree[l] + tree[r];
	}


	while (m--) {
		int c, x;
		cin >> c >> x;

		switch (c)
		{
			case 1:
				inverse(x);
				break;

			case 2:
				cout << find_one(x + 1) << "\n";
				break;
		}
	}

	return 0;
}