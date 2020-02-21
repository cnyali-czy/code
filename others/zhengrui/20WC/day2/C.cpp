/*
	Problem:	C.cpp
	Time:		2020-02-20 23:17
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 10;

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

int n, q, T, fa[maxn], show[maxn], nxt[maxn];
int find(int x) {return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);}
inline void uni(int x, int y) {fa[find(x)] = find(y);}

int main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();q = read<int>();T = read<int>();
	REP(i, 1, n) fa[i] = i;
	int ans = 0;
	while (q--)
	{
		int u = (read<int>() + T * ans - 1) % n + 1;
		int v = (read<int>() + T * ans - 1) % n + 1;
		uni(u, v);
		REP(i, 1, n) show[i] = n + 1;
		DEP(i, n, 1)
		{
			nxt[i] = show[find(i)];
			show[find(i)] = i;
		}
		ans = n;
		REP(i, 1, n)
			REP(j, 1, i) if (nxt[j] != n + 1 && nxt[j] > i) {chkmin(ans, i - j + 1);break;}
		REP(i, 1, n) printf("%d%c", nxt[i], i == n ? '\n' : ' ');
		cout << ans << '\n';
	}
	return 0;
}
