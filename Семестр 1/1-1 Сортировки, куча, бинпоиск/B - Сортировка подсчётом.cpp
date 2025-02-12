#include <bits/stdc++.h>

using namespace std;

void count_sort(vector<int>& v) {
	vector<int> cnt(101);

	for (auto& x : v)
		cnt[x]++;

	int i = 0;
	for (int j = 0; j < 101; j++)
		for (int k = 0; k < cnt[j]; k++)
			v[i++] = j;
}

int main() {
	int n;
	cin >> n;

	vector<int> v(n);
	for (auto& x : v)
		cin >> x;

	count_sort(v);

	for (auto& x : v)
		cout << x << " ";
	cout << endl;

	return 0;
}