#include <bits/stdc++.h>

using namespace std;

int main() {
	int n;
	cin >> n;

	deque<int> dq;
	vector<int> v(1e5 + 1);
	int cnt1 = 0, cnt2 = 0;
	
	while (n--) {
		int c, id;
		cin >> c;

		switch (c)
		{
			case 1:
				cin >> id;

				v[id] = cnt1++;
				dq.push_back(id);
				break;

			case 2:
				dq.pop_front();
				cnt2++;
				break;

			case 3:
				dq.pop_back();
				cnt1--;
				break;

			case 4:
				cin >> id;

				cout << v[id] - cnt2 << "\n";
				break;

			case 5:
				cout << dq.front() << "\n";
				break;
		}
	}

	return 0;
}