#include <bits/stdc++.h>

using namespace std;

struct parent_info {
	int l = 0, r = 0, k = 0;
	bool b = false;

	parent_info() {

	}

	parent_info(int l, int r, int k, bool b = false) {
		this->l = l;
		this->r = r;
		this->k = k;
		this->b = b;
	}

	friend bool operator!=(const parent_info p1, const parent_info p2) {
		return !(p1.l == p2.l && p1.r == p2.r && p1.k == p1.k);
	}
};

int main() {
	int n;
	cin >> n;

	if (n == 0) {
		cout << 0 << endl;
		cout << 0 << " " << 0 << endl;

		return 0;
	}

	if (n == 1) {
		int x;
		cin >> x;

		cout << x << endl;
		cout << (x > 100 ? 1 : 0) << " " << 0 << endl;

		return 0;
	}

	vector<int> v(n);
	int m = 1;

	for (auto& x : v) {
		cin >> x;

		if (x > 100)
			m++;
	}

	vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(m, INT32_MAX)));
	vector<vector<vector<parent_info>>> p(n, vector<vector<parent_info>>(n, vector<parent_info>(m)));

	for (int i = 0; i < n; i++) {
		if (v[i] > 100) {
			dp[i][i][1] = v[i];
			p[i][i][1] = parent_info(i, i, 1);
		}
		else {
			dp[i][i][0] = v[i];
			p[i][i][0] = parent_info(i, i, 0);
		}

	}

	for (int j = 1; j < n; j++) {
		for (int i = 0; i + j < n; i++) {
			int l = i, r = i + j;
			bool b1 = v[l] > 100, b2 = v[r] > 100;

			for (int k = 0; k < m; k++) {
				if (dp[l + 1][r][k] != INT32_MAX && v[l] + dp[l + 1][r][k] < dp[l][r][k + b1]) {
					dp[l][r][k + b1] = v[l] + dp[l + 1][r][k];
					p[l][r][k + b1] = parent_info(l + 1, r, k);
				}

				if (dp[l][r - 1][k] != INT32_MAX && dp[l][r - 1][k] + v[r] < dp[l][r][k + b2]) {
					dp[l][r][k + b2] = dp[l][r - 1][k] + v[r];
					p[l][r][k + b2] = parent_info(l, r - 1, k);
				}
			}

			for (int k = 1; k < m; k++) {
				if (dp[l][r - 1][k] != INT32_MAX && dp[l][r - 1][k] < dp[l][r][k - 1]) {
					dp[l][r][k - 1] = dp[l][r - 1][k];
					p[l][r][k - 1] = parent_info(l, r - 1, k, true);
				}
			}
		}
	}

	auto iter = min_element(dp[0][n - 1].begin(), dp[0][n - 1].end());
	int k1 = iter - dp[0][n - 1].begin();

	while (k1 + 1 < m && dp[0][n - 1][k1] == dp[0][n - 1][k1 + 1])
		k1++;

	stack<parent_info> s;
	s.push(p[0][n - 1][k1]);

	while (s.top() != p[s.top().l][s.top().r][s.top().k])
		s.push(p[s.top().l][s.top().r][s.top().k]);

	vector<int> answer;
	while (!s.empty()) {
		if (s.top().b)
			answer.push_back(s.top().r + 2);

		s.pop();
	}

	int k2 = answer.size();

	cout << dp[0][n - 1][k1] << endl;

	cout << k1 << " " << k2 << endl;

	for (auto& x : answer)
		cout << x << "\n";
	cout << endl;

	return 0;
}