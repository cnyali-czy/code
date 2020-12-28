/*
	Problem:	F2.cpp
	Time:		2020-12-03 21:45
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <queue>
#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 105;

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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, r, na, nb;
pair <int, int> A[maxn], B[maxn];
#define fi first
#define se second

int main()
{
#ifdef CraZYali
	file("F2");
#endif
	cin >> n >> r;
	REP(i, 1, n)
	{
		int a = read<int>(), b = read<int>();
		if (b >= 0) A[++na] = make_pair(a, b);
		else B[++nb] = make_pair(a, -b);
	}
	sort(A + 1, A + 1 + na);
	sort(B + 1, B + 1 + nb, [&](pair <int, int> a, pair <int, int> b) {return a.fi - a.se < b.fi - b.se;});
	int res = 0;
	priority_queue <int> q;
	REP(i, 1, na) if (r >= A[i].first) res++, r += A[i].second;
	int ans = res;
	REP(i, 1, nb)
	{
		while (q.size())
		{
			if (r >= B[i].first && r >= B[i].second) break;
			r += q.top();q.pop();res--;
		}
		if (r >= B[i].first && r >= B[i].second)
		{
			r -= B[i].second;
			res++;
			q.emplace(B[i].first);
		}
		ans = max(ans, res);
	}
	cout << ans << endl;
	return 0;
}
