#include <bits/stdc++.h>

using namespace std;

unsigned long long get_count_inversions(vector<int>& v) {
	if (v.size() < 2)
		return 0;

	vector<int> v1(v.size() / 2);
	vector<int> v2(v.size() - v1.size());

	copy(v.begin(), v.begin() + v1.size(), v1.begin());
	copy(v.begin() + v1.size(), v.end(), v2.begin());

	unsigned long long result = 0;

	result += get_count_inversions(v1);
	result += get_count_inversions(v2);

	int i = 0, j = 0;
	while (i + j < v.size()) {
		if (j == v2.size() || (i < v1.size() && v1[i] < v2[j])) {
			v[i + j] = v1[i];
			i++;
		}
		else {
			v[i + j] = v2[j];
			j++;

			result += v1.size() - i;
		}
	}

	return result;
}

int main() {
	int n;
	cin >> n;

	vector<int> v(n);
	for (auto& x : v)
		cin >> x;

	auto answer = get_count_inversions(v);
	
	cout << answer << endl;

	return 0;
}