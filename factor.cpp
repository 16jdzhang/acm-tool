
#include <iostream>

#include <vector>
#include <math.h>
using namespace std;

vector<int> get_facters(int val) {
	vector<int> res;
	if (val < 0) {
		return res;
	}
	double sqrtv = sqrt(val);
	int range = (int)(sqrtv);
	for (size_t i = 1; i <= range; i++)
	{
		if (val % i == 0) {
			res.push_back(i);
		}
	}
	if ((range + 1)*(range + 1) == val) {
		res.push_back(range + 1);
	}
	for (int i = res.size() - 1; i >= 0 ; i--)
	{
		int f = val / res[i];
		if (f != res[i]) {
			res.push_back(f);
		}
	}
	return res;
}

int Maximum_Common_Factor(const vector<int>& f1, const vector<int>& f2) {
	int i1 = f1.size() - 1;
	int i2 = f2.size() - 1;
	while (i1 >= 0 && i2 >= 0)
	{
		if (f1[i1] == f2[i2]) {
			return f1[i1];
		}
		if (f1[i1] > f2[i2]) {
			--i1;
		}
		else {
			--i2;
		}
	}
	return 0;
}

int main() {
	vector<int> r = get_facters(100);
	for (size_t i = 0; i < r.size(); i++)
	{
		cout << r[i] << " ";
	}
	cout << endl;
	cout << Maximum_Common_Factor(get_facters(100), get_facters(7));
	return 0;
}