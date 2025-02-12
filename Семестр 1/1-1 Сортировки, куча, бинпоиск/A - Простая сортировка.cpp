#include <bits/stdc++.h>

using namespace std;

void merge_sort(vector<int>& v) {
	if (v.size() < 2)
		return;

	vector<int> v1(v.size() / 2);
	vector<int> v2(v.size() - v1.size());

	copy(v.begin(), v.begin() + v1.size(), v1.begin());
	copy(v.begin() + v1.size(), v.end(), v2.begin());

	merge_sort(v1);
	merge_sort(v2);

	int i = 0, j = 0;
	while (i + j < v.size()) {
		if (j == v2.size() || (i < v1.size() && v1[i] < v2[j])) {
			v[i + j] = v1[i];
			i++;
		}
		else {
			v[i + j] = v2[j];
			j++;
		}
	}
}

int main() {
	int n;
	cin >> n;

	vector<int> v(n);
	for (auto& x : v)
		cin >> x;

	merge_sort(v);

	for (auto& x : v)
		cout << x << " ";
	cout << endl;

	return 0;
}