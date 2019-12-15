#pragma GCC optimize("O3", "inline")
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#include <vector>
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#define ll long long
using namespace std;
inline char Getchar()
{
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
const int MOD = 1e9 + 7, maxn = 1e5 + 10, inv2 = (MOD + 1) / 2, inv4 = 1ll * inv2 * inv2 % MOD;
const ll lim = 1ll * MOD * (MOD - 1);
inline int mymin(int x, int y) {if (x < y) return x;return y;}
bool notp[maxn];
int prime[maxn], p_cnt, mu[maxn], Mmu[maxn];
vector <int> store[maxn];
struct __init__
{
	__init__(const int n = 1e5)
	{
		Mmu[1] = mu[1] = 1;
		REP(i, 2, n)
		{
			if (!notp[i]) mu[prime[++p_cnt] = i] = -1;
			REP(j, 1, p_cnt)
			{
				int tmp = i * prime[j];
				if (tmp > n) break;
				notp[tmp] = 1;
				if (i % prime[j]) mu[tmp] = -mu[i];
				else break;
			}
			Mmu[i] = 1ll * mu[i] * i * i % MOD;
		}
		REP(i, 1, n)
		{
			store[i] = vector<int>(128);
			register int top(0);
			for (register int j = 1; j * j <= i; j++)
				if (i % j == 0)
				{
					store[i][top++] = j;
					store[i][top++] = i / j;
				}
			if (store[top-1] == store[top-2]) top--;
			store[i].resize(top - (store[i][top-1] == store[i][top-2]));
		}
	}
}__INIT__;

inline int g(ll n, ll m) {return (n * (n + 1) % MOD) * (m * (m + 1) % MOD) % MOD * inv4 % MOD;}
/*
inline int sum(int n, int m)
{
	if (n > m) swap(n, m);
	int res(0);
	for (int i = 1, j; i <= n; i = j + 1)
	{
		j = mymin(n / (n / i), m / (m / i));
		(res += 1ll * g(n / i, m / i) * (ssr[j] - ssr[i-1]) % MOD) %= MOD;
	}
	return res;
}
inline int calc(int n, int m, int a)
{
	if (n > m) swap(n, m);
	if (a > n) a = n;
	int res(0);
	for (int i = 1, j; i <= a; i = j + 1)
	{
		j = mymin(n / (n / i), m / (m / i));
		(res += 1ll * sum(n / i, m / i) * (i + j) % MOD * (j - i + 1) % MOD * inv2 % MOD) %= MOD;
	}
	return (MOD + res) % MOD;
}
*/
namespace peach
{
	const int N = 2.1e7;
	int rt[maxn], ls[N], rs[N], s[N], cur;
#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r
#define mid (l + r >> 1)
	void update(int pre, int &p, int l, int r, int pos, int val)
	{
		p = ++cur;
		ls[p] = ls[pre];
		rs[p] = rs[pre];
		s[p] = (s[pre] + val) % MOD;
		if (l == r) return;
		if (pos <= mid)	update(ls[pre], lson, pos, val);
		else			update(rs[pre], rson, pos, val);
	}
	inline void init(const int n = 1e5)
	{
		REP(i, 1, n)
		{
			//			if (i % 100 == 0) fprintf(stderr, "cur = %d & %d working!\n", cur, i);
			bool first(1);
			for (auto j : store[i])
			{
				int d = i / j;
				if (first)
				{
					first = 0;
					update(rt[i-1], rt[i], 1, n, j, 1ll * j * Mmu[d] % MOD);
				}
				else
					update(rt[i], rt[i], 1, n, j, 1ll * j * Mmu[d] % MOD);
			}
			//			if (i % 100 == 0) fprintf(stderr, "cur = %d & %d done!\n", cur, i);
		}
	}
	ll query(int u, int v, int l, int r, int L, int R)
	{
		ll res;
		if (r <= R) res = s[v] - s[u];
		else if (R <= mid) return query(ls[u], ls[v], l, mid, L, R);
		else res = query(ls[u], ls[v], l, mid, L, R) + query(rs[u], rs[v], mid + 1, r, L, R);
		if (res >= lim) res %= MOD;
		return res;
	}
	inline int calc(int n, int m, int a)
	{
		if (n > m) swap(n, m);
		if (a > n) a = n;
		register long long res(0);
		for (register int T = 1, Tj; T <= n; T = Tj + 1)
		{
			Tj = mymin(n / (n / T), m / (m / T));
			res += 1ll * g(n / T, m / T) * (query(rt[T-1], rt[Tj], 1, 100000, 1, a) % MOD) % MOD;
			if (res >= lim) res %= MOD;
		}
		/*
		   REP(T, 1, n)//T = i d
		   for (auto i : store[T]) if (i <= a)
		   {
		   int d = T / i;
		   (res += i * mu[d] * d % MOD * d % MOD * g(n / T, m / T) % MOD) %= MOD;
		   }
		   }
		   */
		return (MOD + res % MOD) % MOD;
}
}
inline int read()
{
	char c(Getchar());
	int res(0);
	while (!isdigit(c)) c = Getchar();
	while (isdigit(c)) res = res * 10 + c - 48, c = Getchar();
	return res;
}
#define BUFSIZE 300000
namespace fob {char b[BUFSIZE]={},*f=b,*g=b+BUFSIZE-2;}
#define pob (fwrite(fob::b,sizeof(char),fob::f-fob::b,stdout),fob::f=fob::b,0)
#define pc(x) (*(fob::f++)=(x),(fob::f==fob::g)?pob:0)
struct foce {~foce() {pob; fflush(stdout);}} _foce;
namespace ib {char b[100];}
inline void pint(int x)
{
	if(x==0) {pc(48); return;}
	char *s=ib::b;
	while(x) *(++s)=x%10, x/=10;
	while(s!=ib::b) pc((*(s--))+48);
}
signed main()
{
#ifdef CraZYali
	freopen("gcdlcm.in", "r", stdin);
	freopen("gcdlcm.out", "w", stdout);
#endif
	peach::init();
	int T = read();
	while (T--)
	{
		int n(read()), m(read()), a(read());
		pint(peach::calc(n, m, a));
		pc(10);
		//		printf("%d\n", peach::calc(n, m, a));
	}
	pob;
	return 0;
}
