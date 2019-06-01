
#include <iostream>
#include <vector>
using namespace std;

struct max_subseq_sum_res
{
	int sum, begin, end;
};

//求最长子序列之和，但是子序列应该是可以不连续的，所以题目的说法有点问题
max_subseq_sum_res max_subseq_sum(const vector<int>& seq) {
	max_subseq_sum_res res = { 0,0,0 };
	if (seq.size() == 0) {
		return res;
	}
	int max, p1, p2;
	int now, i1, i2;
	max = now = seq[0];
	p1 = p2 = 0;
	i1 = 0;
	for (i2 = 1; i2 < seq.size(); i2++)
	{
		if (now < 0) {
			now = seq[i2];
			i1 = i2;
		}
		else {
			now += seq[i2];
		}
		if (now > max) {
			max = now;
			p1 = i1;
			p2 = i2;
		}
	}
	res.sum = max;
	res.begin = i1;
	res.end = i2;
	return res;
}

int main() {
	int t;
	cin >> t;
	for (size_t i = 0; i < t; i++)
	{
		int n;
		cin >> n;
		vector<int> seq;
		for (size_t j = 0; j < n; j++)
		{
			seq.push_back(0);
			cin >> seq[j];
		}
		auto res = max_subseq_sum(seq);
		cout << res.sum << " " << res.begin+1 << " " << res.end-1 << endl;
	}
	return 0;
}