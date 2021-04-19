#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cassert>
#include <map>
#include <ctime>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdio>
#define i64 long long
#define u64 unsigned i64
#define fi first
#define se second

using namespace std;
const int maxn = 4096;

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

const int p = 1e9 + 7;
const int p1 = 998244353;

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
namespace Poly
{
	void NTT(u64 a[], int n, int flg)
	{
		static u64 A[maxn];
		REP(i, 0, n - 1) A[i] = a[i];
		if (flg < 0) reverse(A + 1, A + n);
		static int R[maxn];

		REP(i, 1, n - 1)
		{
			R[i] = (R[i >> 1] >> 1) | (i & 1 ? (n >> 1) : 0);
			if (i < R[i]) swap(A[i], A[R[i]]);
		}
		static bool vis[30];
		static int pool[maxn << 1 | 10], *cur = pool, *w[30];
		for (int i = 1, c = 0; i < n; i <<= 1, c++)
		{
			//	static num w[maxn];

			if (!vis[c])
			{
				vis[c] = 1;
				w[c] = cur;cur += i;
				w[c][0] = 1;
				const i64 wn = power_pow(3, (p1 - 1) >> (c + 1), p1);
				REP(l, 1, i - 1) w[c][l] = w[c][l - 1] * wn % p1;
			}
			for (int k = 0; k < n; k += i + i)
				for (int l = 0; l < i; l++)
				{
					u64 x = A[k + l], y = A[k + l + i] * w[c][l] % p1;
					A[k + l] = x + y;
					A[k + l + i] = x + p1 - y;
				}
		}
		REP(i, 0, n - 1) a[i] = A[i] % p1;
		if (flg < 0)
		{
			const i64 iv = inv(n, p1);
			REP(i, 0, n - 1) a[i] = a[i] * iv % p1;
		}
	}
}
using Poly :: NTT;


namespace run
{
	const int maxn = 2e5 + 10;
	int n, a[maxn], b[maxn];
	int f[4096][4096];
	int fac[23333 + 5], invs[23333 + 5], Invs[23333 + 5];
	struct __init__
	{
		__init__(const int N = 23333)
		{
			fac[0] = invs[0] = Invs[0] = 1;
			fac[1] = invs[1] = Invs[1] = 1;
			REP(i, 2, N)
			{
				fac[i] = 1ll * i * fac[i - 1] % p;
				invs[i] = 1ll * (p - p / i) * invs[p % i] % p;
				Invs[i] = 1ll * invs[i] * Invs[i - 1] % p;
			}
		}
	}__INIT__;
	inline i64 C(int n, int m) {return n < m || m < 0 ? 0 : 1ll * fac[n] * Invs[m] % p * Invs[n - m] % p;}
	void DFT(int a[4096][4096], int la, int lb, int flg)
	{
		static u64 g[4096];
		REP(i, 0, la - 1)
		{
			REP(j, 0, lb - 1) g[j] = a[i][j];
			NTT(g, lb, flg);
			REP(j, 0, lb - 1) a[i][j] = g[j];
		}
		REP(j, 0, lb - 1)
		{
			REP(i, 0, la - 1) g[i] = a[i][j];
			NTT(g, la, flg);
			REP(i, 0, la - 1) a[i][j] = g[i];
		}
	}
	const int B = 1000;
	vector <pair <pair <int, int>, int > > vec;
	bool fk[2333][2333];
	int main()
	{
		n = read<int>();
		int ma = 0, mb = 0;
		REP(i, 1, n)
		{
			ma = max(ma, a[i] = read<int>());
			mb = max(mb, b[i] = read<int>());
		}
		int la = 1;while (la <= ma + ma) la <<= 1;
		int lb = 1;while (lb <= mb + mb) lb <<= 1;
		REP(i, 1, n) f[a[i]][b[i]]++;
		REP(i, 1, n) if (f[a[i]][b[i]] > B)
		{
			vec.emplace_back(make_pair(a[i], b[i]), f[a[i]][b[i]]);
			f[a[i]][b[i]] = 0;
			fk[a[i]][b[i]] = 1;
		}
		DFT(f, la, lb, 1);
		REP(i, 0, la - 1) REP(j, 0, lb - 1) f[i][j] = 1ll * f[i][j] * f[i][j] % p1;
		DFT(f, la, lb, -1);
		i64 ans = 0;
		REP(i, 0, ma + ma) REP(j, 0, mb + mb)
		{
			i64 fk = f[i][j];
			if (fk)
				(ans += fk * C(i + j, i)) %= p;
		}
		i64 res = 0;
		for (auto i : vec)
			REP(j, 1, n) if (!fk[a[j]][b[j]]) (res += i.se * C(i.fi.fi + a[j] + i.fi.se + b[j], i.fi.fi + a[j])) %= p;
		(res *= 2) %= p;
		for (auto i : vec) for (auto j : vec)
			(res += C(i.fi.fi + j.fi.fi + i.fi.se + j.fi.se, i.fi.fi + j.fi.fi) * i.se % p * j.se) %= p;
		(ans += res) %= p;

		REP(i, 1, n) ans -= C(a[i] + b[i] + a[i] + b[i], a[i] + a[i]);
		ans = ans % p * (p + 1 >> 1) % p;
		cout << (ans + p) % p << endl;
		return 0;
	}
}
int main()
{
#ifdef CraZYali
	freopen("1983.in", "r", stdin);
	freopen("1983.out", "w", stdout);
#endif
	return run :: main();
}
