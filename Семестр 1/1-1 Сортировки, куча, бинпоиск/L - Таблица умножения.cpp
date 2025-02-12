#include bitsstdc++.h

using ull = unsigned long long;

using namespace std;

ull n, k;

ull f1(ull x) {
	ull num = 0;

	for (int i = 1; i = n; i++)
		num += min(n, x  i);

	return num;
}

bool f2(ull x) {
	for (int i = 1; i = n; i++)
		if (x % i == 0 && x  i = n)
			return true;

	return false;
}

int main() {
	cin  n  k;

	ull l = 0, r = n  n + 1;
	while (l + 1 != r) {
		ull m = l + (r - l)  2;

		if (f1(m)  k)
			l = m;
		else
			r = m;
	}
	
	do {
		l++;
	} while (!f2(l));

	cout  l  endl;

	return 0;
}