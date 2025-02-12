#include <bits/stdc++.h>

using namespace std;

template<typename T>
class max_heap
{
public:
	max_heap() {

	}

	void insert(T item) {
		v.push_back(item);
		sift_up(v.size() - 1);
	}

	T extract() {
		auto result = v[0];

		swap(v[0], v[v.size() - 1]);
		v.pop_back();
		sift_down(0);

		return result;
	}

private:
	vector<int> v;

	void sift_up(int i) {
		while (i != 0 && v[(i - 1) / 2] < v[i]) {
			swap(v[(i - 1) / 2], v[i]);
			i = (i - 1) / 2;
		}
	}

	void sift_down(int i) {
		while (true) {
			int left = 2 * i + 1;
			int right = 2 * i + 2;

			if (left >= v.size())
				break;

			int j = left;
			if (right < v.size() && v[right] > v[j])
				j = right;

			if (v[i] < v[j]) {
				swap(v[i], v[j]);
				i = j;
			}
			else
				break;
		}
	}
};



int main() {
	int n;
	cin >> n;

	max_heap<int> mh;

	while (n--) {
		int c;
		cin >> c;

		switch (c)
		{
			case 0:
				int item;
				cin >> item;

				mh.insert(item);
				break;

			case 1:
				auto max = mh.extract();
				cout << max << endl;
				break;
		}
	}

	return 0;
}