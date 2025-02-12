#include <bits/stdc++.h>

using namespace std;

struct segment {
	int sum = 0, count = 0, length = 1;
	bool prefix = false, suffix = false;
	bool assignedValue = false, isNeedPropagate = false;

	void assign(bool v) {
		sum = length * v, count = v;
		prefix = v, suffix = v;
		assignedValue = v, isNeedPropagate = true;
	}

	void merge(segment s1, segment s2) {
		sum = s1.sum + s2.sum;
		count = s1.count + s2.count;

		if (s1.suffix && s2.prefix)
			count--;

		prefix = s1.prefix, suffix = s2.suffix;
	}
};

int n, m, n_;
vector<segment> tree;

void propagate(int i) {
	if (!tree[i].isNeedPropagate)
		return;

	tree[(i << 1) + 1].assign(tree[i].assignedValue);
	tree[(i << 1) + 2].assign(tree[i].assignedValue);
	tree[i].isNeedPropagate = false;
}

void draw(int l, int r, bool v, int i, int li, int ri) {
	if (r < li || ri < l)
		return;

	if (l <= li && ri <= r) {
		tree[i].assign(v);
		return;
	}

	propagate(i);

	int mi = (li + ri) / 2;
	draw(l, r, v, (i << 1) + 1, li, mi);
	draw(l, r, v, (i << 1) + 2, mi + 1, ri);

	tree[i].merge(tree[(i << 1) + 1], tree[(i << 1) + 2]);
}

int main() {
	n = 2 * 500001;
	cin >> m;

	int n_ = 1;
	while (n_ < n)
		n_ <<= 1;

	tree = vector<segment>(2 * n_ - 1);

	for (int i = n_ - 2; i >= 0; i--) {
		int l = (i << 1) + 1, r = (i << 1) + 2;
		tree[i].length = tree[l].length + tree[r].length;
	}

	while (m--) {
		char c;
		int x, len;
		cin >> c >> x >> len;

		bool v = c == 'B';
		int l = x + 500000;
		int r = l + len - 1;

		draw(l, r, v, 0, 0, n_ - 1);

		cout << tree[0].count << " " << tree[0].sum << "\n";
	}

	return 0;
}