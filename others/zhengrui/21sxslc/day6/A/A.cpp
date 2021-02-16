/*
	Problem:	A.cpp
	Time:		2021-02-16 20:03
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <iostream>
#include <cstdio>

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
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, N;
vector <int> vx[50], vy[50];

int at(int x, int i) {return x >> i & 1;}

int main()
{
#ifdef CraZYali
	file("A");
#endif
	cin >> n ;
	int l = 1, ccc = 0;
	while ((l << 1) < n) l <<= 1, ccc++;
	while (l)
	{
		REP(i, 0, n - 1) if (at(i, ccc) ^ at(i, ccc + 1))
		{
			vx[N].emplace_back(i);
			if ( ((i & (l - 1)) ^ (l - 1)) || at(i, ccc) ) vy[N + 1].emplace_back(i);
		}
		else
		{
			vx[N + 1].emplace_back(i);
			if ( ((i & (l - 1)) ^ (l - 1)) || at(i, ccc) ) vy[N].emplace_back(i);
		}
		l >>= 1, ccc--;N += 2;
	}
	int ans = 0;
	REP(i, 0, N - 1) if (vx[i].size() && vy[i].size()) ans++;
	cout << ans << endl;
	static bool a[3005][3005];
	REP(i, 0, N - 1) if (vx[i].size() && vy[i].size())
	{
		cout << vx[i].size() << ' ' << vy[i].size();
		for (auto j : vx[i]) cout << ' ' << j + 1;
		for (auto j : vy[i]) cout << ' ' << j + 1;
		puts("");
//		for (int x : vx[i]) for (int y : vy[i]) a[x + 1][y + 1] = 1;
	}
//	REP(i, 1, n) REP(j, 1, n) printf("%d%c", a[i][j], j == end_j ? '\n' : ' ');
	return 0;
}
