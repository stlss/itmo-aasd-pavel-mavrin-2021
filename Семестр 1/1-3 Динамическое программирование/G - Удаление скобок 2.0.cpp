#include <bits/stdc++.h>

using namespace std;

int main() {
	string s;
	cin >> s;

	int n = s.size();

	vector<vector<vector<int>>> dp(n, vector<vector<int>>(n));
	map<char, char> d{ {'(', ')'}, {'[', ']'}, {'{', '}'} };

	for (int i = 0; i < n; i++)
		dp[i][i] = { i };

	for (int i = 0; i + 1 < n; i++) {
		if (d[s[i]] == s[i + 1])
			dp[i][i + 1] = {};
		else
			dp[i][i + 1] = { i, i + 1 };
	}

	for (int j = 2; j < n; j++) {
		for (int i = 0; i + j < n; i++) {
			int l = i, r = i + j;

			int m = l;
			for (int k = l; k < r; k++)
				if (dp[l][k].size() + dp[k + 1][r].size() < dp[l][m].size() + dp[m + 1][r].size())
					m = k;

			int size1 = dp[l][m].size() + dp[m + 1][r].size();
			int size2 = dp[l + 1][r - 1].size();

			if (d[s[l]] != s[r])
				size2 += 2;

			if (size1 < size2) {
				dp[l][r] = vector<int>(size1);
				merge(dp[l][m].begin(), dp[l][m].end(), dp[m + 1][r].begin(), dp[m + 1][r].end(), dp[l][r].begin());
			}
			else if (d[s[l]] != s[r]) {
				dp[l][r] = vector<int>(size2);
				vector<int> v{ l, r };

				merge(dp[l + 1][r - 1].begin(), dp[l + 1][r - 1].end(), v.begin(), v.end(), dp[l][r].begin());
			}
			else
				dp[l][r] = dp[l + 1][r - 1];
		}
	}

	vector<bool> v(n, true);
	for (auto& x : dp[0][n - 1])
		v[x] = false;

	for (int i = 0; i < n; i++)
		if (v[i])
			cout << s[i];

	cout << endl;

	return 0;
}