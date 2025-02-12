#include <bits/stdc++.h>

using ull = unsigned long long;

using namespace std;

ull n, k;
vector<int> v1, v2;

ull f1(ull x) {
	ull num = 0;

	for (auto& it : v1) {
		if (it >= x)
			continue;

		auto iter = upper_bound(v2.begin(), v2.end(), x - it);
		num += iter - v2.begin();
	}

	return num;
}

bool f2(ull x) {
	for (auto& it : v1) {
		if (it >= x)
			continue;

		if (binary_search(v2.begin(), v2.end(), x - it))
			return true;
	}

	return false;
}

int main() {
	cin >> n >> k;

	v1 = vector<int>(n);
	for (auto& x : v1)
		cin >> x;

	v2 = vector<int>(n);
	for (auto& x : v2)
		cin >> x;

	sort(v2.begin(), v2.end());

	ull r = 1;
	while (f1(r) < k)
		r <<= 1;
	ull l = r >> 1;

	while (l + 1 != r) {
		ull m = l + (r - l) / 2;

		if (f1(m) < k)
			l = m;
		else
			r = m;
	}
	
	do {
		l++;
	} while (!f2(l));

	cout << l << endl;

	return 0;
}