#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 100000 + 10;

template <typename T> T read()
{
	T ans = 0, p = 1;
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

struct node *null;
const int maxnode = 28000000;

int rt[maxnode], ls[maxnode], rs[maxnode], sum[maxnode], cur, LL[30], RR[30];

#define mid (l + r >> 1)
#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r

void update(int &p, int l, int r, int pos, int num)
{
	if (!p) p = ++cur;
	sum[p] += num;
	if (l == r) return;
	else if (pos <= mid)	update(lson, pos, num);
	else					update(rson, pos, num);
}

int n, m, a[maxn], pos[maxn];
long long ans;

int query(int l, int r, int val, bool mode)
{
	int lsz(0), rsz(0), s(0);
	for (int i = l-1; i > 0; i -= i & -i) LL[++lsz] = rt[i];
	for (int i = r	; i > 0; i -= i & -i) RR[++rsz] = rt[i];
	l = 1, r = n;
	while (l < r)
		if (val > mid)
		{
			if (mode)
			{
				REP(i, 1, lsz) s -= sum[ls[LL[i]]];
				REP(i, 1, rsz) s += sum[ls[RR[i]]];
			}
			REP(i, 1, lsz) LL[i] = rs[LL[i]];
			REP(i, 1, rsz) RR[i] = rs[RR[i]];
			l = mid + 1;
		}
		else
		{
			if (!mode)
			{
				REP(i, 1, lsz) s -= sum[rs[LL[i]]];
				REP(i, 1, rsz) s += sum[rs[RR[i]]];
			}
			REP(i, 1, lsz) LL[i] = ls[LL[i]];
			REP(i, 1, rsz) RR[i] = ls[RR[i]];
			r = mid ;
		}
	return s;
}

int main()
{
#ifdef CraZYali
	freopen("3157.in", "r", stdin);
	freopen("3157.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, n)
	{
		pos[a[i] = read<int>()] = i;
		ans += 1ll * query(1, i-1, a[i], 0);
		for (int j = i; j <= n; j += j & -j) update(rt[j], 1, n, a[i], 1);
	}
	while (m --> 0)
	{
		printf("%lld\n", ans);
		int x = read<int>(), p = pos[x];
		ans -= query(1, p - 1, x, 0);
		ans -= query(p + 1, n, x, 1);
		for (int i = p; i <= n; i += i & -i) update(rt[i], 1, n, x, -1);
	}
	return 0;
}
