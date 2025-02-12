#include <bits/stdc++.h>

using namespace std;

int main() {
	int n;
	cin >> n;

	deque<int> dq1, dq2;

	while (n--) {
		char x;
		cin >> x;

		int i;
		switch (x)
		{
			case '+':
				cin >> i;

				if (dq1.empty() && dq2.empty())
					dq1.push_back(i);
				else {
					if (dq1.size() == dq2.size()) {
						dq1.push_back(dq2.front());
						dq2.pop_front();
					}
					dq2.push_back(i);
				}

				break;

			case '*':
				cin >> i;

				if (dq1.size() == dq2.size())
					dq1.push_back(i);
				else
					dq2.push_front(i);

				break;

			case '-':
				cout << dq1.front() << "\n";

				dq1.pop_front();
				if (dq1.size() < dq2.size()) {
					dq1.push_back(dq2.front());
					dq2.pop_front();
				}

				break;
		}

	}

	return 0;
}