//test
#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>
#include <map>

using namespace std;
const int MOD = 1e9 + 7, maxn = 1000000 + 10;

int n0, n, n1, m, a[20][2], b[50], id[50];
long long e[50][3], v[maxn], f[10][maxn];
vector <int> vec[50];
map <int, int> s;

inline int power_pow(long long base, int b)
{
	long long ans(1);
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		(base *= base) %= MOD;
		b >>= 1;
	}
	return ans;
}
#define inv(x) power_pow(x, MOD - 2)

const long long inv9 = power_pow(9, MOD - 2);

int fa[maxn];
int find(int x) {return fa[x] == x ? x : fa[x] = find(fa[x]);}
inline void uni(int x, int y) {fa[find(x)] = find(y);}

inline int calcv(int x) {return (power_pow(10, x) - 1) * inv9 % MOD;}

#define file(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)

int main()
{
#ifdef CraZYali
	file("A");
#endif
	cin >> n0 >> m;
	REP(i, 1, m)
	{
		scanf("%d%d", &a[i][0], &a[i][1]);
		s[a[i][0]-1] = s[a[i][1]] = 0;
	}
	n = -1;
	for (auto &i : s) b[i.second = ++n] = i.first;
	DREP(i, n, 1) b[i] -= b[i-1];
	REP(i, 1, m)
	{
		a[i][0] = s[a[i][0] - 1] + 1;
		a[i][1] = s[a[i][1]];
		vec[a[i][1]].push_back(a[i][0]);
	}
	m = 0;
	REP(i, 1, n) fa[i] = i;
	DREP(i, n, 1)
	{
		sort(vec[i].begin(), vec[i].end(), greater<int>());
		while (vec[i].size() > 1)
		{
			int t = vec[i].size() - 1;
			if (vec[i][t] < vec[i][0])
				vec[vec[i][0] - 1].emplace_back(vec[i][t]);
			vec[i].pop_back();
		}
		if (!vec[i].empty()) uni(i, vec[i][0] - 1);
	}
	REP(i, 0, n) if (find(i) == i) id[i] = ++n1;
	REP(i, 0, n) id[i] = id[fa[i]];
	REP(i, 1, n)
	{
		e[i][0] = id[i - 1];
		e[i][1] = id[i];
		long long x = calcv(b[i]);
		e[i][2] = (x + 1) * inv(x) % MOD;
	}
	const int lim = 1 << n1;
	REP(S, 0, lim - 1)
	{
		v[S] = 1;
		REP(i, 1, n)
			if ((S & (1 << e[i][0] - 1)) && (S & (1 << e[i][1] - 1)))
				(v[S] *= e[i][2]) %= MOD;
	}
	REP(S, 0, lim - 1)
		if (S & (1 << id[0] - 1))
			f[0][S] = v[S];
	long long t;
	REP(i, 1, 8)
		REP(j, 0, lim - 1) if (t = f[i-1][j])
		for (int k(j); k < lim; k = (k + 1) | j)
			(f[i][k] += t * v[k ^ j] % MOD) %= MOD;
	REP(i, 1, n) n0 -= b[i];
	long long ans = power_pow(10, n0);
	REP(i, 1, n) (ans *= calcv(b[i])) %= MOD;
	cout << (1ll * f[8][lim-1] * ans % MOD + MOD) % MOD << endl;
	return 0;
}
