#include <bits/stdc++.h>

using namespace std;

template<typename T>
class min_stack
{
public:
	min_stack() {

	}

	void push(T item) {
		s1.push(item);
		
		if (s2.size() == 0 || s2.top() > item)
			s2.push(item);
		else
			s2.push(s2.top());
	}

	void pop() {
		s1.pop();
		s2.pop();
	}

	T min() {
		return s2.top();
	}

private:
	stack<T> s1, s2;
};

int main() {
	int n;
	cin >> n;

	min_stack<int> s;

	while (n--) {
		int c;
		cin >> c;

		switch (c)
		{
			case 1:
				int x;
				cin >> x;

				s.push(x);
				break;
			case 2:
				s.pop();
				break;
			case 3:
				cout << s.min() << "\n";
				break;
		}
	}

	return 0;
}