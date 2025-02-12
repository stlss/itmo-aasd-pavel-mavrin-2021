#include <bits/stdc++.h>

using namespace std;

stack<int> s;
int x1, x2;

void foo() {
	x2 = s.top();
	s.pop();

	x1 = s.top();
	s.pop();
}

int main() {
	int n;
	cin >> n;

	stack<int> s1, s2;
	vector<string> answer(2 * n);
	int max = 0;

	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;

		s2.push(x);
	}

	for (int i = 0; i < n; i++) {
		s1.push(s2.top());
		s2.pop();
	}

	int i = 0;
	while (!s1.empty()) {
		while (!s2.empty() && s2.top() < s1.top()) {
			if (s2.top() < max) {
				cout << "impossible" << endl;
				return 0;
			}

			max = s2.top();
			s2.pop();

			answer[i++] = "pop";
		}

		s2.push(s1.top());
		s1.pop();

		answer[i++] = "push";
	}

	while (!s2.empty()) {
		if (s2.top() < max) {
			cout << "impossible" << endl;
			return 0;
		}

		max = s2.top();
		s2.pop();

		answer[i++] = "pop";
	}

	for (auto& x : answer)
		cout << x << "\n";

	return 0;
}