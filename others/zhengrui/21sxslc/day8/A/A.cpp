#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <map>
#include <iostream>
#include <cstdio>
#define int long long

using namespace std;
const int maxn = 1e5 + 10, MOD = 1e9 + 7;

int n;
pair <int, int> a[maxn];int m;
#define fi first
#define se second

inline int read() {int x;scanf("%lld", &x);return x;}
map <int, int> fk;

int pre[maxn], suf[maxn];

int p[60], rk, bin2[maxn];
int fac[maxn], invs[maxn], Invs[maxn];
void init(int n)
{
	fac[0] = invs[0] = Invs[0] = 1;
	fac[1] = invs[1] = Invs[1] = 1;
	REP(i, 2, n)
	{
		fac[i] = 1ll * i * fac[i - 1] % MOD;
		invs[i] = 1ll * (MOD - MOD / i) * invs[MOD % i] % MOD;
		Invs[i] = 1ll * invs[i] * Invs[i - 1] % MOD;
	}
	bin2[0] = 1;REP(i, 1, n) bin2[i] = 2 * bin2[i - 1] % MOD;
}
inline int C(int n, int m) {return fac[n] * Invs[m] % MOD * Invs[n - m] % MOD;}

void ins(int x)
{
	DEP(i, 59, 0) if (x >> i & 1)
		if (!p[i]) {p[i] = x;rk++;return;}
		else x ^= p[i];
}
int N;
int calc(int x,int FUCKCZY)
{
	//cerr<<FUCKCZY<<endl;
	int tx = x;
	DEP(i, 59, 0) if (tx >> i & 1) tx ^= p[i];
	if (tx) return 0;
	return bin2[N - rk] - (x==FUCKCZY);
}

signed main()
{
#ifdef CraZYali
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	cin >> n;init(n);
	REP(i, 1, n) fk[read()]++;
	for (auto i : fk)
		a[++m] = make_pair(i.fi, i.se);
	REP(i, 1, m) pre[i] = pre[i - 1] ^ (a[i].se & 1 ? a[i].fi : 0);
	DEP(i, m, 1) suf[i] = suf[i + 1] ^ (a[i].se & 1 ? a[i].fi : 0);
	int ans = 0;
	if (!pre[m]) ans++;
	DEP(i, m, 1)
	{
		int T = a[i].se;
		REP(k, 0, T - 1) // color k into white
		{
			int xs = C(T, k);
			//pure
			int cur = a[i].fi - (T - k + 1 & 1);
			if (!(pre[i - 1] ^ (k & 1 ? a[i].fi : 0) ^ cur ^ suf[i + 1])) ans += xs;
			//not pure
			cur = a[i].fi - (T - k & 1);
			int need = pre[i - 1] ^ cur ^ (k & 1 ? a[i].fi : 0);
			//cerr<<i <<' '<<need<<" "<<suf[i+1]<<" "<<xs<<endl;
			(ans += xs * calc(need,suf[i+1])) %= MOD;
		}
		ins(a[i].fi);N += T;
	}
	cout << ans % MOD << endl;
	return 0;
}
