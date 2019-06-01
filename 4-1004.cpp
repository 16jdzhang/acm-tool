
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
using namespace std;

class bag_class {
	const vector<int>& w;
	const vector<int>& v;
	map<string, int> memory;
public:
	bag_class(const vector<int>& _w, const vector<int>& _v)
		:w(_w), v(_v) { }
	int bag(int i, int ww){
		if (i <= 0 || ww <= 0) {
			return 0;
		}
		stringstream ss;
		ss << i << "," << ww;
		string str;
		ss >> str;
		if (memory.count(str) != 0) {
			return memory[str];
		}
		int b1 = bag(i - 1, ww);
		int b2 = bag(i - 1, ww - w[i - 1]) + v[i - 1];
		if (b1 < b2) {
			b1 = b2;
		}
		return b1;
	}
};

int bag(const vector<int>& w, const vector<int>& v, int limit) {
	bag_class b(w, v);
	return b.bag(w.size(), limit);
}

int main() {
	while (true)
	{
		int n;
		cin >> n;
		if (n == 0) {
			break;
		}
		vector<int> cost(n);
		int max_i = 0;
		for (size_t i = 0; i < n; i++)
		{
			cin >> cost[i];
			if (cost[i] > cost[max_i]) {
				max_i = i;
			}
		}
		int max = cost[max_i];
		cost.erase(cost.begin() + max_i);
		int m;
		cin >> m;
		int b = bag(cost, cost, m);
		cout << (m - b - max) << endl;
	}
	return 0;
}