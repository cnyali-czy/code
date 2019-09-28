#define  REP(i, s, e) for (int i = s; i <= e ; i++)
#define DREP(i, s, e) for (int i = s; i >= e ; i=--)

#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <bits/stdc++.h>
#define int long long

using namespace std;
const int maxn = 100000 + 10;

template <typename T> inline T read()
{
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}

struct Matrix
{
	int a[2][2], l1, l2;
	void clear() { memset(a, 0, sizeof(a)); }
}mat[maxn], matn[maxn], f0, fn;
int n, m, Q, MOD, C1, C2;
map <int, int> mp;
int ans[maxn << 1], len;
void power_pow(Matrix &ret, Matrix x, Matrix y)
{
	ret.clear();
	ret.l1 = x.l1; ret.l2 = y.l2;
	REP(i, 0, ret.l1 - 1)
		REP(j, 0, ret.l2 - 1)
		REP(k, 0, x.l2 - 1)
		ret.a[i][j] = (ret.a[i][j] + x.a[i][k] * y.a[k][j] % MOD) % MOD;
}
int get(int x)
{
	power_pow(fn, matn[x/m], mat[x%m]);
	power_pow(fn, f0, fn);
	return ((fn.a[0][0] * fn.a[0][1] % MOD - C1 * (C2 - C1) % MOD) % MOD + MOD) % MOD;
}
signed main()
{
#ifdef CraZYali
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
#endif
	cin >> n >> m >> Q >> MOD >> C1 >> C2;
	f0.l1 = 1; f0.l2 = 2;
	f0.a[0][0] = C1;
	f0.a[0][1] = C2;
	mat[0].l1 = mat[0].l2 = 2;
	mat[0].a[0][0] = mat[0].a[1][1] = 1;
	mat[1].l1 = mat[1].l2 = 2;
	mat[1].a[0][1] = mat[1].a[1][0] = mat[1].a[1][1] = 1;
	REP(i, 2, m) power_pow(mat[i], mat[i-1], mat[1]);
	matn[0].l1 = matn[0].l2 = 2;
	matn[0].a[0][0] = matn[0].a[1][1] = 1;
	matn[1] = mat[m];
	REP(i, 2, n) power_pow(matn[i], matn[i-1], matn[1]);
	while (Q --> 0)
	{
		int x(read<int>()), y(read<int>());
		int fx = mp.count(x) ? mp[x] : x, fy = mp.count(y) ? mp[y] : y;
		mp[x] = fy; mp[y] = fx;
	}
	printf("%lld ", get(mp.count(1) ? mp[1] : 1));
	int i = 1, j = 1;
	while(i != n || j != m)
		if (i == n)
		{
			int ret((i-1)*m+(++j));
			printf("%lld ", get(mp.count(ret) ? mp[ret] : ret));
		}
		else if (j == m)
		{
			int ret((i++)*m+j);
			printf("%lld ", get(mp.count(ret) ? mp[ret] : ret));
		}
		else
		{
			int ret1((i-1)*m+j+1);
			int nx1(get(mp.count(ret1) ? mp[ret1] : ret1));
			int ret2(i*m+j);
			int nx2(get(mp.count(ret2) ? mp[ret2] : ret2));
			if(nx1 < nx2) printf("%lld ", nx1), j++;
			else printf("%lld ", nx2), i++;
		}
	return 0;
} 
