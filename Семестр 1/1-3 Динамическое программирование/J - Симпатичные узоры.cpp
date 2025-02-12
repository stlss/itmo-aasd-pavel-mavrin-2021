#include <bits/stdc++.h>

using namespace std;

int main() {
	int n, m;
	cin >> n >> m;

	if (m < n)
		swap(n, m);

	int l = 1 << n;
	vector<vector<int>> t(l, vector<int>(l));

	for (int p1 = 0; p1 < l; p1++) {
		for (int p2 = 0; p2 < l; p2++) {
			bool b = true;
			int cnt = (p1 & 1) == (p2 & 1);

			for (int i = 1; i < n; i++) {
				if (((p1 >> i) & 1) != ((p2 >> i) & 1) || ((p1 >> i) & 1) != ((p2 >> (i - 1)) & 1)) {
					if (cnt >= 2)
						b = false;

					cnt = ((p1 >> i) & 1) == ((p2 >> i) & 1);
				}
				else
					cnt++;
			}

			t[p1][p2] = b && cnt < 2;
		}
	}

	vector<vector<int>> dp(m, vector<int>(l));
	for (int p = 0; p < l; p++)
		dp[0][p] = 1;

	for (int j = 1; j < m; j++)
		for (int p1 = 0; p1 < l; p1++)
			for (int p2 = 0; p2 < l; p2++)
				dp[j][p1] += dp[j - 1][p2] * t[p1][p2];

	int answer = 0;
	for (int p = 0; p < l; p++)
		answer += dp.back()[p];

	cout << answer << endl;

	return 0;
}