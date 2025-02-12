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
	string input, word;
	getline(cin, input);

	istringstream stream(input);

	while (stream >> word) {
		switch (word[0])
		{
			case '+':
				foo();
				s.push(x1 + x2);
				break;

			case '-':
				foo();
				s.push(x1 - x2);
				break;

			case '*':
				foo();
				s.push(x1 * x2);
				break;

			default:
				s.push(stoi(word));
				break;
		}
		
	}

	cout << s.top() << endl;

	return 0;
}