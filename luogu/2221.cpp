#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

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

template <typename T> void write(T x)
{
	if (x < 0) putchar('-'), write(-x);
	else
	{
		if (x / 10) write(x / 10);
		putchar(x % 10 + '0');
	}
}

int m, n, k;

int sigma_i(int S, int T) {return (S + T) * (T - S + 1) / 2;}
int sigma_i_2(int x) {return x * (x + 1) * (x + x + 1) / 6;}
int sigma_i_2(int S, int T) {return sigma_i_2(T) - sigma_i_2(S - 1);}

#define ls p << 1
#define rs p << 1 | 1
#define mid (l + r >> 1)
#define lson ls, l, mid
#define rson rs, mid + 1, r

int sum1[maxn << 2], sum2[maxn << 2], sum3[maxn << 2], tag[maxn << 2];

void maintain(int p, int l, int r, int val)
{
	tag[p] += val;
	sum1[p] += val * (r - l + 1);
	sum2[p] += val * sigma_i(l, r);
	sum3[p] += val * sigma_i_2(l, r);
}

void pushdown(int p, int l, int r)
{
	if (tag[p])
	{
		maintain(lson, tag[p]);
		maintain(rson, tag[p]);
		tag[p] = 0;
	}
}

void pushup(int p, int l, int r)
{
	sum1[p] = sum1[ls] + sum1[rs];
	sum2[p] = sum2[ls] + sum2[rs];
	sum3[p] = sum3[ls] + sum3[rs];
}

void update(int p, int l, int r, int L, int R, int val)
{
	if (L <= l && r <= R) maintain(p, l, r, val);
	else
	{
		pushdown(p, l, r);
		if (L <= mid) update(lson, L, R, val);
		if (R >  mid) update(rson, L, R, val);
		pushup(p, l, r);
	}
}

int Sum1, Sum2, Sum3;

void query(int p, int l, int r, int L, int R)
{
	if (L <= l && r <= R) Sum1 += sum1[p], Sum2 += sum2[p], Sum3 += sum3[p];
	else
	{
		pushdown(p, l, r);
		if (L <= mid) query(lson, L, R);
		if (R >  mid) query(rson, L, R);
	}
}

int gcd(int a, int b) {return !b ? a : gcd(b, a % b);}

signed main()
{
#ifdef CraZYali
	freopen("2221.in", "r", stdin);
	freopen("2221.out", "w", stdout);
#endif
	cin >> n >> m;
	while (m --> 0)
	{
		register char c = getchar();
		while (c != 'C' && c != 'Q') c = getchar();
		if (c == 'C')
		{
			register int l = read<int>(), r = read<int>() - 1, val = read<int>();
			update(1, 1, n, l, r, val);
		}
		else
		{
			register int l = read<int>(), r = read<int>() - 1;
			Sum1 = Sum2 = Sum3 = 0;
			query(1, 1, n, l, r);
			register int ans = (r - l + 1 - r * l) * Sum1 + (r + l) * Sum2 - Sum3;
			printf("%lld/%lld\n", ans / gcd(ans, (r - l + 1) * (r - l + 2) / 2), (r - l + 1) * (r - l + 2) / 2 / gcd(ans, (r - l + 1) * (r - l + 2) / 2));
		}
	}
	return 0;
}
