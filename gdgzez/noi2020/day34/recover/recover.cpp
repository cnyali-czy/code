/*
	Problem:	recover.cpp
	Time:		2020-07-27 08:36
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <cstdlib>
#include "recover.h"
#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

	template <typename T>
inline T read()
{
	T ans = 0, flag = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

bool G[2005][2005];
int a[2005];

bool vis[2005], tmp[2005];
vector <pair <int, int> > recover(int n)
{
	vector <pair <int, int> > ans;
	while (1)
	{
		int rt = 0;
		REP(i, 1, n) if (!vis[i]) {rt = i;break;}
		if (!rt) break;
		vector <int> qaq(1, rt);
		vis[rt] = 1;
		REP(i, 1, n) if (!vis[i])
		{
			qaq.emplace_back(i);
			auto res = query(qaq);
			if (res.first > 0)
			{
				G[res.first][res.second] = 1;
				G[res.second][res.first] = 1;
				qaq.pop_back();
			}
			else vis[i] = 1;
		}
		REP(i, 1, n) if (!vis[i])
		{
			vector <int> QAQ = qaq;
			qaq.clear();
			for (auto j : QAQ) if (!G[i][j]) qaq.emplace_back(j);
			while (qaq.size())
			{
				qaq.emplace_back(i);
				auto res = query(qaq);
				qaq.pop_back();
				if (res.first < 0) break;
				G[res.first][res.second] = 1;
				G[res.second][res.first] = 1;
				int ccc = res.first;
				if (ccc == i) ccc = res.second;
				vector <int> aqa;
				for (auto j : qaq) if (j != ccc) aqa.emplace_back(j);
				swap(qaq, aqa);
			}
			qaq = QAQ;
		}
	}
	REP(i, 1, n) REP(j, i + 1, n) if (G[i][j]) ans.emplace_back(i, j);
	return ans;
}

#ifdef CraZYali
#include <bits/stdc++.h>
#include "recover.h"

// if c++11 is not enabled, use vector< pair<int, int> > instead of vector<pair<int, int>> to avoid compile error

using namespace std;

namespace workspace {

	vector<pair<int, int>> E;
	int n, m, k, qcnt;

	pair<int, int> query(vector<int> S){
		++qcnt;
		vector<char> vis(n + 1);
		for (int i = 0; i < S.size(); ++i) {
			vis[S[i]] = 1;
		}
		for (int i = 0; i < E.size(); ++i) {
			if (vis[E[i].first] && vis[E[i].second]) {
				return E[i];
			}
		}
		return make_pair(-1, -1);
	}

	void main(){
		freopen("recover.in", "r", stdin);
		freopen("recover.out", "w", stdout);
		cin >> n >> m >> k;
		for (int i = 1; i <= m; ++i) {
			int u, v;
			cin >> u >> v;
			if (u > v) swap(u, v);
			E.push_back(make_pair(u, v));
		}
		sort(E.begin(), E.end());
		vector<pair<int, int>> W = recover(n);
		for (int i = 0; i < W.size(); ++i) {
			if (W[i].first > W[i].second) {
				swap(W[i].first, W[i].second);
			}
		}
		sort(W.begin(), W.end());
		if (E == W) {
			cout << "OK\n";
		} else {
			cout << "WA\n";
		}
		cout << qcnt << "\n";
		double Q = qcnt / n;
		if (Q < 2 * k + 1) puts("1 100");
		else if (Q <= 6 * k) printf("2 %.2lf\n", 40 + 120 * k / Q);
		else printf("3 %.2lf\n", 100 / (log(Q) - log(k)));
	}

}

pair<int, int> query(vector<int> S){
	return workspace::query(S);
}
int main(){
	workspace::main();
}
#endif
