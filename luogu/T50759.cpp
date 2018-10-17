#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

#define int long long
using namespace std;
const int MOD = 1e9 + 7, maxn = 1e5 + 10, maxm = 1e5 + 10, maxk = 1e5 + 10;

pair <int, int> a[maxk];
bool cmp(pair <int, int> A, pair <int, int> B) {return A.first < B.first || A.first == B.first && A.second < B.second;}

int power_pow(int a, int b)
{
	int ans = 1, base = a % MOD;
	while (b)
	{
		if (b & 1) ans = ans * base % MOD;
		base = base * base % MOD;
		b >>= 1;
	}
	return (ans + MOD) % MOD;
}

#define inv(x) power_pow(x, MOD - 2)

int n, m, k;

int fac[maxn * 2 + 100], Inv[maxn * 2 + 100];

void init(int N)
{
	fac[0] = 1;
	Inv[0] = 1;
	REP(i, 1, N)
	{
		fac[i] = fac[i-1] * i % MOD;
		Inv[i] = inv(fac[i]);
	}
}

int C(int N, int M)
{
	int ans = fac[N] * Inv[M] % MOD * Inv[N - M] % MOD;
	return (ans + MOD) % MOD;
}

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

signed main()
{
#ifdef CraZYali
	freopen("T50759.in", "r", stdin);
	freopen("T50759.out", "w", stdout);
#endif
	cin >> n >> m >> k;
	init(n + m + 100);
	REP(i, 1, k) a[i].first = read<int>(), a[i].second = read<int>();//scanf("%lld%lld", &a[i].first, &a[i].second);
	sort(a + 1, a + 1 + k, cmp);
	REP(i, 1, k)
		if (a[i-1].first != a[i].first && a[i-1].second > a[i].second)
		{
			cout << 0;
			return 0;
		}
	register int ans = 1, nx = 1, ny = 1;

	++k;
	a[k] = make_pair(n, m);
	REP(i, 1, k)
	{
		register int tx = a[i].first, ty = a[i].second;
		ans = ans * C(tx - nx + ty - ny, tx - nx) % MOD;
		nx = tx;ny = ty;
	}

	cout << (ans + MOD) % MOD;
	return 0;
}
