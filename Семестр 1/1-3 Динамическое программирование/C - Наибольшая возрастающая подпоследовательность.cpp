#include <bits/stdc++.h>

using namespace std;

int main() {
	int n;
	cin >> n;

	vector<int> v(n);
	for (auto& x : v)
		cin >> x;

	vector<int> dp(n, 1);
	vector<int> p(n);

	for (int i = n - 1; i >= 0; i--) {
		int index = -1;

		for (int j = i + 1; j < n; j++)
			if (v[j] > v[i] && (index == -1 || dp[j] > dp[index]))
				index = j;

		if (index != -1) {
			dp[i] = dp[index] + 1;
			p[i] = index;
		}
	}

	auto iter = max_element(dp.begin(), dp.end());
	int index = iter - dp.begin();

	cout << *iter << endl;

	while (p[index] != 0) {
		cout << v[index] << " ";
		index = p[index];
	}

	cout << v[index] << endl;

	return 0;
}