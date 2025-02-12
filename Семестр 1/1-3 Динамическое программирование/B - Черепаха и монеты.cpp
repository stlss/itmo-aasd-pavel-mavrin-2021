#include <bits/stdc++.h>

using ll = long long;

using namespace std;

int main() {
	int n, m;
	cin >> n >> m;

	vector<vector<ll>> dp(n, vector<ll>(m));
	for (auto& v : dp)
		for (auto& x : v)
			cin >> x;

	vector<vector<char>> p(n, vector<char>(m));

	for (int j = 1; j < m; j++) {
		dp[0][j] += dp[0][j - 1];
		p[0][j] = 'R';
	}

	for (int i = 1; i < n; i++) {
		dp[i][0] += dp[i - 1][0];
		p[i][0] = 'D';

		for (int j = 1; j < m; j++) {
			if (dp[i - 1][j] > dp[i][j - 1]) {
				dp[i][j] += dp[i - 1][j];
				p[i][j] = 'D';
			}
			else {
				dp[i][j] += dp[i][j - 1];
				p[i][j] = 'R';
			}
		}
	}

	int i = n - 1, j = m - 1;
	stack<char> s;

	while (!(i == 0 && j == 0)) {
		s.push(p[i][j]);

		if (p[i][j] == 'D')
			i--;
		else
			j--;
	}

	cout << dp.back().back() << endl;
	
	while (!s.empty()) {
		cout << s.top();
		s.pop();
	}

	cout << endl;

	return 0;
}