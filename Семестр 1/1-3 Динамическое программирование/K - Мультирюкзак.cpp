#include <bits/stdc++.h>

using namespace std;

int main() {
	int n, s;
	cin >> n >> s;

	vector<int> v(n);
	for (auto& x : v)
		cin >> x;

	int m = 1 << n;
	vector<pair<int, int>> dp(m, { INT32_MAX, INT32_MAX });
	vector<pair<int, int>> p(m);
	dp[0] = { 0, 0 };

	for (int x = 1; x < m; x++) {
		for (int i = 0; i < n; i++) {
			int y = x ^ (1 << i);
			auto pr = dp[y];

			if (pr.second + v[i] > s)
				pr.first++, pr.second = v[i];
			else
				pr.second += v[i];

			if (pr < dp[x]) {
				dp[x] = pr;
				p[x] = { y, i };
			}
		}
	}

	vector<vector<int>> answer(dp.back().first + 1);
	int x = m - 1;

	int i = 0;
	while (x != p[x].first) {
		answer[i].push_back(p[x].second);

		int y = p[x].first;
		if (dp[x].first != dp[y].first)
			i++;

		x = y;
	}

	cout << answer.size() << endl;

	for (auto& it : answer) {
		cout << it.size() << " ";

		for (auto& x : it)
			cout << x + 1 << " ";
		cout << endl;
	}

	return 0;
}