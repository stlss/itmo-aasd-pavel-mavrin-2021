#include <bits/stdc++.h>

using namespace std;

template<typename T>
class segment_tree
{
public:
	segment_tree(vector<T> v, T(*operation)(T, T), T neutral) {
		n = 1;
		while (n < v.size())
			n <<= 1;

		tree = vector<T>((n << 1) - 1, neutral);
		copy(v.begin(), v.end(), tree.end() - n);

		this->operation = operation;

		for (int i = tree.size() - n - 1; i >= 0; i--) {
			int l = (i << 1) + 1, r = (i << 1) + 2;
			tree[i] = operation(tree[l], tree[r]);
		}
	}

	T segment_value(int l, int r) {
		l += n - 1, r += n - 1;
		T v1 = tree[l], v2 = tree[r];

		if (l == r)
			return v1;

		while (true) {
			int oldL = l, oldR = r;
			l = (l - 1) >> 1, r = (r - 1) >> 1;

			if (l == r)
				break;

			if (oldL & 1)
				v1 = operation(v1, tree[(l << 1) + 2]);

			if ((oldR & 1) == 0)
				v2 = operation(v2, tree[(r << 1) + 1]);
		}

		return operation(v1, v2);
	}

	void set(int i, T v) {
		i += n - 1;
		tree[i] = v;

		while (i != 0) {
			i = (i - 1) >> 1;
			int l = (i << 1) + 1, r = (i << 1) + 2;
			tree[i] = operation(tree[l], tree[r]);
		}
	}

private:
	int n;
	vector<T> tree;
	T(*operation)(T, T);
};

pair<int, int> func(pair<int, int> p1, pair<int, int> p2) {
	if (p1.first == p2.first)
		return { p1.first, p1.second + p2.second };

	return p1 < p2 ? p1 : p2;
}

int main() {
	int n, m;
	cin >> n >> m;

	vector<pair<int, int>> v(n);
	for (auto& x : v) {
		cin >> x.first;
		x.second = 1;
	}

	pair<int, int>(*operation)(pair<int, int>, pair<int, int>) { func };
	segment_tree<pair<int, int>> st(v, operation, { INT32_MAX, 0 });

	while (m--) {
		int c, x, y;
		cin >> c >> x >> y;

		switch (c)
		{
			case 1:
				st.set(x, { y, 1 });
				break;

			case 2:
				auto v = st.segment_value(x, y - 1);
				cout << v.first << " " << v.second << "\n";
				break;
		}
	}

	return 0;
}