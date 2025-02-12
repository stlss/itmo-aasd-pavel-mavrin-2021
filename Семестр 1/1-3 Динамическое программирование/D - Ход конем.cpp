#include <bits/stdc++.h>

using namespace std;

int main() {
	int n;
	cin >> n;
	
	vector<vector<int>> dp(n, vector<int>(10));
	vector<vector<int>> d
	{
		{ 4, 6 },
		{ 6, 8 },
		{ 7, 9 },
		{ 4, 8 },
		{ 0, 3, 9 },
		{ },
		{ 0, 1, 7 },
		{ 2, 6 },
		{ 1, 3 },
		{ 2, 4 },
	};

	for (int i = 0; i < 10; i++)
		if (i != 0 && i != 8)
			dp[0][i] = 1;

	int mod = 1e9;
	for (int i = 1; i < n; i++)
		for (int j = 0; j < 10; j++)
			for (auto& x : d[j])
				dp[i][x] = (dp[i][x] + dp[i - 1][j]) % mod;

	int answer = 0;
	for (auto& x : dp.back())
		answer = (answer + x) % mod;

	cout << answer << endl;

	return 0;
}