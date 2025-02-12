#include <bits/stdc++.h>

using namespace std;

struct request {
	int number, value, l, r;
};

struct segment {
	int value, index, operated;

	void merge(segment s1, segment s2) {
		if (s1.value < s2.value)
			swap(s1, s2);

		value = s1.value;
		index = s1.index;
	}
};

int n, m, n_;
vector<request> v;
vector<segment> tree;

void propagate(int i) {
	int l = (i << 1) + 1, r = (i << 1) + 2;
	int v = tree[i].operated;

	tree[l].value += v, tree[l].operated += v;
	tree[r].value += v, tree[r].operated += v;
	tree[i].operated = 0;
}

void add(int l, int r, int v, int i, int li, int ri) {
	if (r < li || ri < l)
		return;

	if (l <= li && ri <= r) {
		tree[i].value += v, tree[i].operated += v;
		return;
	}

	propagate(i);

	int mi = (li + ri) / 2;
	add(l, r, v, (i << 1) + 1, li, mi);
	add(l, r, v, (i << 1) + 2, mi + 1, ri);

	auto lv = tree[(i << 1) + 1];
	auto rv = tree[(i << 1) + 2];
	tree[i].merge(lv, rv);
}

int main() {
	int shift = 200000;

	cin >> m;

	v = vector<request>(2 * m);
	for (int i = 0; i < m; i++) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;

		x1 += shift, y1 += shift, x2 += shift, y2 += shift;

		v[2 * i] = request{ y1, 1, x1, x2 };
		v[2 * i + 1] = request{ y2, -1, x1, x2 };
	}

	sort(v.begin(), v.end(), [](request r1, request r2) { return r1.number != r2.number ? r1.number < r2.number : r1.value > r2.value; });

	n = 2 * (shift + 2);

	n_ = 1;
	while (n_ < n)
		n_ <<= 1;

	tree = vector<segment>(2 * n_ - 1);
	int j = tree.size() - n_;

	for (int i = 0; i < n_; i++)
		tree[i + j].index = i;

	for (int i = j - 1; i >= 0; i--) {
		int l = (i << 1) + 1, r = (i << 1) + 2;
		tree[i].merge(tree[l], tree[r]);
	}

	pair<int, pair<int, int>> answer{ 0, { 0, 0 } };
	int number = v.front().number, value = 1;

	for (auto& r : v) {
		if (r.value != value) {
			if (answer.first < tree.front().value) {
				answer.first = tree.front().value;
				answer.second = { tree.front().index, r.number };
			}

			number = r.number, value = r.value;
		}

		add(r.l, r.r, r.value, 0, 0, n_ - 1);
	}

	answer.second.first -= shift, answer.second.second -= shift;

	cout << answer.first << "\n";
	cout << answer.second.first << " " << answer.second.second << "\n";

	return 0;
}