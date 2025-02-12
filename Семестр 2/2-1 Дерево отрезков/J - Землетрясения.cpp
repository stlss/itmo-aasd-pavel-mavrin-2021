#include <bits/stdc++.h>

using namespace std;

struct earthquakes {
	vector<int> tree;
	vector<pair<int, int>> pairsIndexTime;
	int n_ = 1, index = -1;

	void add_earthquake(int power) {
		int i = index--;
		i += tree.size() >> 1;
		tree[i] = power;

		while (i != 0) {
			i = (i - 1) >> 1;
			int l = (i << 1) + 1, r = (i << 1) + 2;
			tree[i] = max(tree[l], tree[r]);
		}
	}

	pair<int, int> find_earthquake(int l, int power, int i, int li, int ri) {
		if (ri < l || tree[i] < power)
			return { INT32_MAX, INT32_MAX };

		if (li == ri)
			return pairsIndexTime[li];

		int mi = (li + ri) / 2;
		auto res = find_earthquake(l, power, (i << 1) + 1, li, mi);

		if (res.first != INT32_MAX)
			return res;

		return find_earthquake(l, power, (i << 1) + 2, mi + 1, ri);
	}
};

int n, m, n_;
vector<earthquakes> tree;
vector<vector<int>> events;
vector<int> buildTimes, answer;

void add_earthquake_1(int l, int r, int index, int time, int i, int li, int ri) {
	if (r < li || ri < l)
		return;

	if (l <= li && ri <= r) {
		tree[i].pairsIndexTime.push_back({ index, time });
		tree[i].index++;
		return;
	}

	int mi = (li + ri) / 2;
	add_earthquake_1(l, r, index, time, (i << 1) + 1, li, mi);
	add_earthquake_1(l, r, index, time, (i << 1) + 2, mi + 1, ri);
}

void add_earthquake_2(int l, int r, int power, int i, int li, int ri) {
	if (r < li || ri < l)
		return;

	if (l <= li && ri <= r) {
		tree[i].add_earthquake(power);
		return;
	}

	int mi = (li + ri) / 2;
	add_earthquake_2(l, r, power, (i << 1) + 1, li, mi);
	add_earthquake_2(l, r, power, (i << 1) + 2, mi + 1, ri);
}

void add_building(int i, int h, int buildTime) {
	int oldI = i;
	i += n_ - 1;

	auto earthquake = tree[i].find_earthquake(0, h, 0, 0, tree[i].n_ - 1);
	if (i != 0) {
		do {
			i = (i - 1) >> 1;
			auto earthquake_ = tree[i].find_earthquake(0, h, 0, 0, tree[i].n_ - 1);

			if (earthquake_ < earthquake)
				earthquake = earthquake_;

		} while (i != 0);
	}

	if (earthquake.second < buildTimes[oldI])
		answer[earthquake.first]++;

	buildTimes[oldI] = buildTime;
}

int main() {
	cin >> n >> m;

	n_ = 1;
	while (n_ < n)
		n_ <<= 1;

	tree = vector<earthquakes>(2 * n_ - 1);
	events = vector<vector<int>>(m);
	buildTimes = vector<int>(n, INT32_MAX);
	int cntEarthquake = 0;

	for (int i = 0; i < m; i++) {
		int c;
		cin >> c;

		switch (c)
		{
			case 1:
				events[i] = vector<int>(3);
				cin >> events[i][1] >> events[i][2];
				break;

			case 2:
				events[i] = vector<int>(4);
				cin >> events[i][1] >> events[i][2] >> events[i][3];
				add_earthquake_1(events[i][1], events[i][2] - 1, cntEarthquake++, i, 0, 0, n_ - 1);
				break;
		}

		events[i][0] = c;
	}

	for (auto& es : tree) {
		while (es.n_ < es.pairsIndexTime.size())
			es.n_ <<= 1;

		es.tree = vector<int>(2 * es.n_ - 1, -1);
	}

	answer = vector<int>(cntEarthquake);

	for (int i = m - 1; i >= 0; i--) {
		switch (events[i][0])
		{
			case 1:
				add_building(events[i][1], events[i][2], i);
				break;

			case 2:
				add_earthquake_2(events[i][1], events[i][2] - 1, events[i][3], 0, 0, n_ - 1);
				break;
		}
	}

	for (auto& x : answer)
		cout << x << "\n";

	return 0;
}