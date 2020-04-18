#define REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;
const int maxn = 1e5 + 10;
template <typename T> T read()
{
	T ans(0), flag(1);
	char c(getchar());
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

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int m, n, q;

int prime[maxn], p_cnt, mu[maxn];
pair <int, int> o[maxn];
bool notp[maxn];
void init(int n)
{
	mu[1] = 1;
	REP(i, 2, n)
	{
		if (!notp[i]) mu[prime[++p_cnt] = i] = -1;
		REP(j, 1, p_cnt)
		{
			int tmp = i * prime[j];if (tmp > n) break;
			notp[tmp] = 1;
			if (i % prime[j]) mu[tmp] = -mu[i];
			else break;
		}
	}
	REP(i, 1, n)
	{
		o[i].second = i;
		REP(j, 1, n / i) o[i * j].first += i;
	}
}
struct Query
{
	int n, m, a, id;
	inline bool operator < (const Query &B) const {return a < B.a;}
}Q[maxn];
int ans[maxn];

int c[maxn], g[maxn];
void add(int x, int y)
{
	g[x] += y;
	while (x <= n)
	{
		c[x] += y;
		x += x & -x;
	}
}
int sum(int l, int r)
{
	int res = 0;
	l--;
	while (r > l) res += c[r], r &= (r - 1);
	while (l > r) res -= c[l], l &= (l - 1);
	return res;
}
inline int min(const int &x, const int &y) {if (x < y) return x;return y;}
int main()
{
#ifdef CraZYali
	file("3312");
#endif
	q = read<int>();
	REP(i, 1, q)
	{
		Q[i].n = read<int>();
		Q[i].m = read<int>();
		if (Q[i].n > Q[i].m) swap(Q[i].n, Q[i].m);
		chkmax(n, Q[i].n);
		Q[i].a = read<int>();
		Q[i].id = i;
	}
	init(n);
	sort(Q + 1, Q + 1 + q);
	sort(o + 1, o + 1 + n);
	int a = 0;
	const int lim = (1ll << 31) - 1;
	REP(i, 1, q)
	{
		while (a < Q[i].a)
		{
			++a;
			static int lst = 1;
			while (lst <= n && o[lst].first <= a)
			{
				int g = o[lst].second;
				for (int T = g, d = 1; T <= n; T += g, d++) add(T, o[lst].first * mu[d]);
				lst++;
			}
		}
		unsigned long long res = 0;
		const int n = Q[i].n, m = Q[i].m, mid = sqrt(n + .5);
		REP(i, 1, mid) res += (n / i) * (m / i) * g[i];
		for (int i = mid + 1, j; i <= n; i = j + 1)
		{
			const int ccc = n / i, ddd = m / i;
			j = min(n / ccc, m / ddd);
			res += 1ll * sum(i, j) * ccc * ddd;
		}
		ans[Q[i].id] = res & lim;
	}
	REP(i, 1, q) printf("%d\n", ans[i]);
	return 0;
}
