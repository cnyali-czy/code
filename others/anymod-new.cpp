#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <map>
#include <ctime>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdio>
#define i64 long long
#define u64 unsigned i64
#define poly vector <int>

using namespace std;
const int maxn = 1 << 18;

	template <typename T>
inline T read()
{
	T ans = 0, flag = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

const u64 LIM = 17e18;
inline int deg(const poly &f) {return (int)f.size() - 1;}

int p;
const int p1 = 998244353, p2 = 104857601, p3 = 1004535809;

i64 power_pow(i64 base, int b, const int MOD)
{
	i64 ans = 1;
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		if (b >>= 1) (base *= base) %= MOD;
	}
	return ans;
}
#define inv(x, P) power_pow(x, P - 2, P)
const __int128 i1 = inv(1ll * p2 * p3 % p1, p1);
const __int128 i2 = inv(1ll * p1 * p3 % p2, p2);
const __int128 i3 = inv(1ll * p1 * p2 % p3, p3);
const __int128 lcm = (__int128)p1 * p2 * p3;
const __int128 w1 = i1 * p2 * p3 % lcm, w2 = i2 * p1 * p3 % lcm, w3 = i3 * p1 * p2 % lcm; 
struct num
{
	u64 v1, v2, v3;
	num() {}
	num(const u64 &v1, const u64 &v2, const u64 &v3) : v1(v1), v2(v2), v3(v3) {}
	inline num operator + (num B) {return num(v1 + B.v1, v2 + B.v2, v3 + B.v3);}
	inline num operator - (num B) {return num(v1 - B.v1, v2 - B.v2, v3 - B.v3);}
	inline num operator * (num B) {return num(v1 * B.v1 % p1, v2 * B.v2 % p2, v3 * B.v3 % p3);}
	int real()
	{
		static const int MOD = p;
		return (v1 * w1 + v2 * w2 + v3 * w3) % lcm % MOD;
	}
};
const num M(p1, p2, p3);
namespace Poly
{
	void NTT(num a[], int n, int flg)
	{
		if (flg < 0) reverse(a + 1, a + n);
		static int R[maxn];

		REP(i, 1, n - 1)
		{
			R[i] = (R[i >> 1] >> 1) | (i & 1 ? (n >> 1) : 0);
			if (i < R[i]) swap(a[i], a[R[i]]);
		}
		static bool vis[30];
		static num pool[maxn << 1 | 10], *cur = pool, *w[30];
		for (int i = 1, c = 0; i < n; i <<= 1, c++)
		{
			//	static num w[maxn];

			if (!vis[c])
			{
				vis[c] = 1;
				w[c] = cur;cur += i;
				w[c][0] = num(1, 1, 1);
				num wn = num(
						power_pow(3, (p1 - 1) >> (c + 1), p1), 
						power_pow(3, (p2 - 1) >> (c + 1), p2), 
						power_pow(3, (p3 - 1) >> (c + 1), p3)
						);
				REP(l, 1, i - 1) w[c][l] = w[c][l - 1] * wn;
			}
			for (int k = 0; k < n; k += i + i)
				for (int l = 0; l < i; l++)
				{
					num x = a[k + l], y = a[k + l + i] * w[c][l];
					a[k + l] = x + y;
					a[k + l + i] = x + M - y;
				}
		}
		REP(i, 0, n - 1) a[i].v1 %= p1, a[i].v2 %= p2, a[i].v3 %= p3;
		if (flg < 0)
		{
			num iv(inv(n, p1), inv(n, p2), inv(n, p3));
			REP(i, 0, n - 1) a[i] = a[i] * iv;
		}
	}
}
using Poly :: NTT;

poly operator * (poly f, poly g)
{
	static const int MOD = p;
	int N = deg(f), M = deg(g), K = N + M;
	int len = 1;
	while (len <= N + M) len <<= 1;
	static num F[maxn], G[maxn];
	REP(i, 0, len - 1) F[i] = G[i] = num(0, 0, 0);
	REP(i, 0, N) F[i] = num(f[i] % p1, f[i] % p2, f[i] % p3);
	REP(i, 0, M) G[i] = num(g[i] % p1, g[i] % p2, g[i] % p3); 
	NTT(F, len, 1);NTT(G, len, 1);
	REP(i, 0, len - 1) F[i] = F[i] * G[i];
	NTT(F, len, -1);

	f.resize(K + 1);
	REP(i, 0, K) f[i] = F[i].real();
	return f;
}
void output(const poly &f)
{
	REP(i, 0, deg(f)) printf("%d%c", f[i], i == end_i ? '\n' : ' ' );
}
int ans[maxn];
poly mem[maxn];

poly operator ^ (poly base, int b)
{
	b--;
	poly ans = base;
	while (b)
	{
		if (b & 1) ans = ans * base;
		if (b >>= 1) base = base * base;
	}
	return ans;
}

int main()
{
#ifdef CraZYali
	freopen("anymod-new.in", "r", stdin);
	freopen("anymod-new.out", "w", stdout);
#endif
	int n = read<int>(), m = read<int>();p = read<int>();const int MOD = p;
	poly f(n + 1, 0), g(m + 1, 0);
	REP(i, 0, n)
	{
		f[i] = read<int>();
		if (f[i] >= MOD) f[i] %= MOD;
	}
	REP(i, 0, m)
	{
		g[i] = read<int>();
		if (g[i] >= MOD) g[i] %= MOD;
	}
	output(f * g);
	return 0;
}
