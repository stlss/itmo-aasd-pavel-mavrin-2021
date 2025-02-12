#include <bits/stdc++.h>

using ll = long long;

using namespace std;

int main() {
	int n, k;
	cin >> n >> k;

	vector<ll> dp(n);
	for (int i = 1; i < n - 1; i++)
		cin >> dp[i];

	vector<int> p(n);
	multiset<pair<ll, int>> ms{ {0, 0} };

	for (int i = 1; i < n; i++) {
		auto pr = *--ms.end();

		dp[i] += pr.first;
		p[i] = pr.second;

		ms.insert({ dp[i], i });

		if (i >= k)
			ms.erase({ dp[i - k], i - k });
	}

	stack<int> path;
	int i = n - 1;

	while (i != 0) {
		path.push(i + 1);
		i = p[i];
	}

	path.push(1);

	cout << dp.back() << endl;
	cout << path.size() - 1 << endl;

	while (!path.empty()) {
		cout << path.top() << " ";
		path.pop();
	}

	cout << endl;

	return 0;
}