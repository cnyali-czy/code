#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp>

using namespace std;
const int maxn = 1e6 + 10, maxS = 1000 + 10, maxm = 1e6 + 10;
const long long MOD = 1e9 + 7;

long long power_pow(long long a, long long b)
{
	long long ans = 1, base = a % MOD;
	while (b)
	{
		if (b & 1) ans = ans * base % MOD;
		base = base * base % MOD;
		b >>= 1;
	}
	return ans;
}

long long inv(int x) {return power_pow(x, MOD - 2);}

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

template <typename T> void write(T x)
{
	if (x < 0) putchar('-'), write(-x);
	else if (x / 10) write(x / 10);
	putchar(x % 10 + '0');
}

int m, n, k;

long long a[maxn], Sum[maxn];

long long fac[maxm], Inv[maxm], inv2 = inv(2);
long long alls(long long s, long long t) {return (Sum[t] - Sum[s - 1] + MOD) % MOD;}
long long allm(long long s, long long t) {return (fac[t] * Inv[s - 1] % MOD + MOD) % MOD;}
long long mul[maxn << 2], sum[maxn << 2], Max[maxn << 2], Min[maxn << 2];
#define ls p << 1
#define rs p << 1 | 1
#define mid (l + r >> 1)
#define lson ls, l, mid
#define rson rs, mid + 1, r

void pushup(int p, int l, int r)
{
	sum[p] = (sum[ls] + sum[rs]) % MOD;
	mul[p] = mul[ls] * mul[rs] % MOD;
	Max[p] = max(Max[ls], Max[rs]);
	Min[p] = min(Min[ls], Min[rs]);
}

void build(int p, int l, int r)
{
	if (l == r) mul[p] = Max[p] = Min[p] = a[l], sum[p] = (long long)sqrt(a[l]) + a[l];
	else
	{
		build(lson);
		build(rson);
		pushup(p, l, r);
	}
}

void update(int p, int l, int r, int pos, int val)
{
	if (l == r) mul[p] = Max[p] = Min[p] = a[l], sum[p] = (long long)sqrt(val) + val;
	else
	{
		if (pos <= mid) update(lson, pos, val);
		else update(rson, pos, val);
		pushup(p, l, r);
	}
}

long long querymin(int p, int l, int r, int L, int R)
{
	if (L <= l && r <= R) return Min[p];
	else
	{
		if (L >  mid) return querymin(rson, L, R);
		if (R <= mid) return querymin(lson, L, R);
		return min(querymin(lson, L, R), querymin(rson, L, R));
	}
}

long long querymax(int p, int l, int r, int L, int R)
{
	if (L <= l && r <= R) return Max[p];
	else
	{
		if (L >  mid) return querymax(rson, L, R);
		if (R <= mid) return querymax(lson, L, R);
		return max(querymax(lson, L, R), querymax(rson, L, R));
	}
}

long long querysum(int p, int l, int r, int L, int R)
{
	if (L <= l && r <= R) return sum[p];
	else
	{
		if (L >  mid) return querysum(rson, L, R);
		if (R <= mid) return querysum(lson, L, R);
		return (querysum(lson, L, R) + querysum(rson, L, R)) % MOD;
	}
}

long long querymul(int p, int l, int r, int L, int R)
{
	if (L <= l && r <= R) return mul[p];
	else
	{
		if (L >  mid) return querymul(rson, L, R);
		if (R <= mid) return querymul(lson, L, R);
		return (querymul(lson, L, R) * querymul(rson, L, R)) % MOD;
	}
}

int main()
{
#ifdef CraZYali
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
#endif
	cin >> n >> m;
	fac[0] = 1;Inv[0] = 1;
	REP(i, 1, m) fac[i] = fac[i - 1] * (long long) i % MOD, Sum[i] = (Sum[i-1] + i + (long long)sqrt(i)) % MOD, Inv[i] = inv(fac[i]);
	REP(i, 1, n) a[i] = read<long long>();

	build(1, 1, n);

	register int Q = read<int>();
	while (Q --> 0)
	{
		register int opt = read<int>(), l = read<int>(), r = read<int>();
		if (opt == 1)
		{
			register long long ts = querysum(1, 1, n, l, r), tm = querymul(1, 1, n, l, r);
			ts = (ts + MOD) % MOD;tm = (tm + MOD) % MOD;
			long long L = querymin(1, 1, n, l, r), R = querymax(1, 1, n, l, r);
			if (alls(L, R) == ts && allm(L, R) == tm) printf("YES\n");
			else printf("NO\n");
		}
		else update(1, 1, n, l, r);
	}

	return 0;
}
