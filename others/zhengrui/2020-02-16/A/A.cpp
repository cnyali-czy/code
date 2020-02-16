/*
	Problem:	A.cpp
	Time:		2020-02-16 12:14
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
#include <cstring>
#include <cmath>
#include <iostream>
#include <cstdio>
#define int long long
using namespace std;
const int maxn = 1000 + 10;

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

int n, a, b, h[maxn], dp[maxn][maxn];

int solve(int x)
{
	int tmp = (x - 1) / b;
	x = (x - 1) % b + 1;
	return tmp - (int)ceil(x * 1. / a);
}
pair <int, int> item[maxn];
inline bool cmp(pair <int, int> A, pair <int, int> B) {return A.first - A.second < B.first - B.second;} 
priority_queue <int> Q;
signed main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();a = read<int>();b = read<int>();
	int ans = 0, hp = 1;
	REP(i, 1, n)
	{
		int h = read<int>();
		int plus = (h + b - 1) / b;
		int sh = (h- (plus - 1) * b + a - 1) / a + 1;
		hp += plus;
		if (hp >= sh) hp -= sh, Q.emplace(sh), ans++;
		else if (!Q.empty() && sh < Q.top()) hp += Q.top() - sh, Q.pop(), Q.emplace(sh);
	}
	cout << ans << endl;
	return 0;
	sort(item + 1, item + 1 + n, cmp);
	REP(i, 1, n) cerr<<item[i].first<<' '<<item[i].second<<endl;
	REP(i, 1, n) hp += item[i].first;
	REP(i, 1, n)
	{
		hp -= item[i].first;
		hp += item[i].second;
		if (hp < 0)
		{
			cout << i - 1 << endl;
			return 0;
		}
	}
	cout << n << endl;
	return 0;
	memset(dp, -1, sizeof dp);
	dp[0][0] = 1;
	REP(i, 0, n - 1)
		REP(j, 0, n) if (dp[i][j] >= 0)
		{
			chkmax(dp[i + 1][j], dp[i][j] + (int)ceil(h[i + 1] * 1. / b));
			chkmax(dp[i + 1][j + 1], dp[i][j] + solve(h[i + 1]));
		}
	DEP(i, n, 1) if (dp[n][i] >= 0)
	{
		cout << i << endl;
		return 0;
	}
	cout << 0 << endl;
	return 0;
}
