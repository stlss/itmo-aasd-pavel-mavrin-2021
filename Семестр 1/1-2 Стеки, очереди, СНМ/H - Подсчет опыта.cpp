#include <bits/stdc++.h>

using namespace std;

struct element_set {
	element_set* parent = this;
	int exp1 = 0, exp2 = 0;
	int size = 1;

	element_set* get_main_parent() {
		auto e = this->parent;

		while (e != e->parent)
			e = e->parent;

		return e;
	}

	void _union(element_set* e) {
		auto e1 = this->get_main_parent();
		auto e2 = e->get_main_parent();

		if (e1 == e2)
			return;

		if (e2->size > e1->size)
			swap(e1, e2);


		e1->size += e2->size;

		e2->parent = e1;
		e2->exp2 = e1->exp1;
	}

	void add_exp(int exp) {
		auto e = this->get_main_parent();
		e->exp1 += exp;
	}

	int get_exp() {
		int r = this->exp1;
		auto e = this;

		while (e != e->parent) {
			r += e->parent->exp1 - e->exp2;
			e = e->parent;
		}

		return r;
	}
};

int main() {
	int n, m;
	cin >> n >> m;

	vector<element_set*> v(n + 1);
	for (int i = 0; i <= n; i++)
		v[i] = new element_set();

	while (m--) {
		int x, y;
		string s;

		cin >> s;

		if (s == "join") {
			cin >> x >> y;

			v[x]->_union(v[y]);
		}

		if (s == "add") {
			cin >> x >> y;

			v[x]->add_exp(y);
		}

		if (s == "get") {
			cin >> x;

			cout << v[x]->get_exp() << "\n";
		}
	}

	return 0;
}