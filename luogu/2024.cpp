#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 5e4 + 10;

int fa[maxn * 3];
int find(int x) {return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);}
inline void uni(int x, int y) {fa[find(x)] = find(y);}

/*
 * 一倍同类
 * 二倍猎物
 * 三倍天敌
 */


int m, n, k;
bool doit(int opt, int x, int y)
{
	if (x > n || y > n) return 0;
	if (opt == 1)
		if (find(x + n) == find(y) || find(x) == find(y + n)) return 0;
		else
		{
			uni(x, y);
			uni(x + n, y + n);
			uni(x + n + n, y + n + n);
		}
	else
		if (find(x) == find(y) || find(x) == find(y + n)) return 0;
		else
		{
			uni(x + n, y);
			uni(x + n + n, y + n);
			uni(x, y + n + n);
		}
	return 1;
}

int main()
{
#ifdef CraZYali
	freopen("2024.in", "r", stdin);
	freopen("2024.out", "w", stdout);
#endif
	cin >> n >> k;
	REP(i, 1, n * 3) fa[i] = i;
	int ans = 0;
	while (k --> 0)
	{
		register int opt, x, y;
		scanf("%d%d%d", &opt, &x, &y);
		ans += !doit(opt, x, y);
	}
	cout << ans;
	return 0;
}
