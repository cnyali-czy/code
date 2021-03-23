#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 1e5 + 10, MOD = 1e9 + 7;

int n, a[3][maxn];
inline int id(int x, int y) {return x * n + y;}
inline void get(int id, int &x, int &y)
{
	if (id <= n) x = 0, y = id;
	else if (id <= n + n) x = 1, y = id - n;
	else x = 2, y = id - n - n;
}

void cdq(int l, int r)
{
	int mid = l + r >> 1;



	if (l == r) return;
	cdq(l, mid);cdq(mid + 1, r);
}

int main()
{
#ifdef CraZYali
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 0, 2) REP(j, 1, n) scanf("%d", a[i] + j);
	cdq(1, n);
	return 0;
}
