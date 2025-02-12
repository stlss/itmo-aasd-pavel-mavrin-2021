#include <bits/stdc++.h>

using ull = unsigned long long;

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

int main() {
	int n, m;
	cin >> n >> m;

	vector<ull> v(n);
	for (auto& x : v)
		cin >> x;

	segment_tree<ull> st(v, [](ull x1, ull x2) { return x1 + x2; }, 0);

	while (m--) {
		int c, x, y;
		cin >> c >> x >> y;

		switch (c)
		{
			case 1:
				st.set(x, y);
				break;

			case 2:
				cout << st.segment_value(x, y - 1) << "\n";
				break;
		}
	}

	return 0;
}