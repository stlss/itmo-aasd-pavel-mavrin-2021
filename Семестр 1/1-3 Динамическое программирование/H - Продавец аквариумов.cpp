#include <bits/stdc++.h>

using namespace std;

int main() {
	int n;
	cin >> n;

	vector<vector<int>> vv(n, vector<int>(n));
	for (auto& v : vv)
		for (auto& x : v)
			cin >> x;

	int m = 1 << n;
	vector<vector<int>> dp(m, vector<int>(n, INT32_MAX));
	vector<vector<int>> p(m, vector<int>(n));

	for (int i = 0; i < n; i++) {
		int x = 1 << i;
		dp[x][i] = 0;
		p[x][i] = i;
	}

	for (int x = 1; x < m; x++) {
		for (int i = 0; i < n; i++) {
			int y = x | (1 << i);

			if (x == y)
				continue;

			for (int j = 0; j < n; j++) {
				if (dp[x][j] != INT32_MAX && dp[x][j] + vv[i][j] < dp[y][i]) {
					dp[y][i] = dp[x][j] + vv[i][j];
					p[y][i] = j;
				}
			}
		}
	}

	vector<int> answer(n);
	auto iter = min_element(dp.back().begin(), dp.back().end());

	int x = m - 1;
	int i = iter - dp.back().begin();

	for (int j = 0; j < n; j++) {
		answer[j] = i;

		int oldI = i;
		i = p[x][i];

		x = x ^ (1 << oldI);
	}

	cout << *iter << endl;

	for (auto& x : answer)
		cout << x + 1 << " ";
	cout << endl;

	return 0;
}