
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
	int t;
	cin >> t;
	for (size_t it = 0; it < t; it++)
	{
		int n, m;
		cin >> n >> m;
		vector<vector<int> > G = vector<vector<int>>(n);
		int* deg = new int[n];
		for (size_t i = 0; i < n; i++)
		{
			deg[i] = 0;
		}
		for (size_t im = 0; im < m; im++)
		{
			int u, v;
			cin >> u >> v;
			G[v-1].push_back(u);
			deg[u-1]++;
		}
		queue<int> que;
		for (size_t i = 0; i < n; i++)
		{
			if (deg[n - i - 1] == 0) {
				que.push(n - i - 1 + 1);
			}
		}
		int* rank = new int[n];
		int ir = 0;
		while (!que.empty()) {
			int top = que.front();
			que.pop();
			rank[ir] = top;
			ir++;
			for (size_t i = 0; i < G[top-1].size(); i++)
			{
				deg[G[top-1][i]-1]--;
				if (deg[G[top-1][i]-1] == 0) {
					que.push(G[top-1][i]);
				}
			}
		}
		for (size_t i = 0; i < n; i++)
		{
			cout << rank[n - i - 1] << " ";
		}
		cout << endl;
		delete deg;
		delete rank;
	}
	return 0;
}