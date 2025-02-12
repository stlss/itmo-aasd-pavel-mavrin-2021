#include <bits/stdc++.h>

using namespace std;

int main() {
	int n;
	cin >> n;

	stack<int> s1, s2;
	int answer = 0;

	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;

		if (s1.empty()) {
			s1.push(x);
			s2.push(1);
			continue;
		}

		if (s1.top() != x && s2.top() >= 3) {
			int cnt = s2.top();
			answer += cnt;

			while (cnt--) {
				s1.pop();
				s2.pop();
			}
		}

		if (s1.top() == x)
			s2.push(s2.top() + 1);
		else
			s2.push(1);

		s1.push(x);
	}

	if (s2.top() >= 3)
		answer += s2.top();

	cout << answer << endl;

	return 0;
}