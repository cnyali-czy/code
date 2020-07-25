/*
	Problem:	5325-new.cpp
	Time:		2020-04-04 20:27
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <unordered_map>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e7 + 10, maxP = 7e5;
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
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)
#define i64 long long

int prime[maxP], lp, p_cnt, N, mu[maxn], phi[maxn];
i64 n, k;
unsigned smu[maxn], sphi[maxn];
bool notp[maxn];
unsigned H[maxP][40];

int lim;
unsigned sgn(i64 x) {return x & 1 ? -1 : 1;}
void init(int N)
{
	::N = N;
	mu[1] = smu[1] = phi[1] = sphi[1] = 1;
	REP(i, 2, N)
	{
		if (!notp[i]) mu[prime[++p_cnt] = i] = -1, phi[i] = i - 1;
		REP(j, 1, p_cnt)
		{
			int tmp = i * prime[j];if (tmp > N) break;
			notp[tmp] = 1;
			if (i % prime[j]) mu[tmp] = -mu[i], phi[tmp] = phi[i] * (prime[j] - 1);
			else {phi[tmp] = phi[i] * prime[j];break;}
		}
		smu[i] = smu[i - 1] + mu[i];
		sphi[i] = sphi[i - 1] + phi[i];
	}
}
void init2()
{
	REP(i, 1, p_cnt)
	{
		i64 p = prime[i];
		if (p * p > n)
		{
			lp = i - 1;
			break;
		}
		H[i][0] = 1;
		for (int k = 1; p <= n; p *= prime[i], k++)
			H[i][k] = (k <= lim ? sgn(k) : 0) + H[i][k - 1];
//			REP(c, 0, k - 1) H[i][k] -= H[i][c] * G[k - c];
	}
}

namespace SMU
{
	unsigned mem[maxn];
	unsigned S(i64 n)
	{
		if (n <= N) return smu[n];
		unsigned &res = mem[::n / n];
		if (res) return res;
		res = 1;
		int div = sqrt(n);
		REP(i, 2, div) res -= S(n / i);
		for (i64 i = div + 1, j; i <= n; i = j + 1)
		{
			j = n / (n / i);
			res -= (j - i + 1) * S(n / i);
		}
		return res;
	}
}

unsigned ans;
i64 curn;
void dfs(i64 d, unsigned H, int lst)
{
	if (!H) return;
	ans += H * SMU :: S(curn / d);
	if (lst == lp) return;
	REP(i, lst + 1, lp)
	{
		if (1ll * prime[i] * prime[i] > curn / d) break;
		i64 dd = d * prime[i] * prime[i];
		for (int k = 2; dd <= curn; k++, dd *= prime[i])
			dfs(dd, H * ::H[i][k], i);
	}
}

i64 stk[214514], top;
int pos[214514];
unsigned mem[214514];

namespace SPHI
{
	unsigned mem[maxn];
	unsigned s(i64 n)
	{
		if (n <= N) return sphi[n];
		unsigned &res = mem[::n / n];
		if (res) return res;
		res = (n * (n + 1) / 2) % (1 << 30);
		for (i64 i = 2, j; i <= n; i = j + 1)
		{
			j = n / (n / i);
			res -= s(n / i) * (j - i + 1);
		}
		return res;
	}
}
unordered_map <i64, unsigned> jjs;

int main()
{
#ifdef CraZYali
	file("B");
#endif
	cin >> n >> k;
	for (i64 i = 1, j; i <= n; i = j + 1)
	{
		j = n / (n / i);
		stk[++top] = n / i;
		pos[top] = i;
	}
	stk[++top] = 1;
	pos[top] = n;
	init(max((int)100, (int)(2 * pow(n, 2. / 3))));
	curn = n;
	for(lim=1;lim<=k;lim++)init2(),dfs(1,1,0);
	cout<<n<<' '<<ans<<endl;ans=0;
	/*
	REP(i, 1, top)
	{
		curn = pos[i];
		for (lim = 1; lim <= k; lim++)
		{
			init2();
			dfs(1, 1, 0);
		}
		jjs[curn] = ans;
		mem[i] = ans;
#ifdef CraZYali
		cout << curn << ' ' << ans << endl;
#endif
		ans = 0;
	}
	for (i64 i = 1, j; i <= n; i = j + 1)
	{
		j = n / (n / i);
		ans += (jjs[j] - jjs[i - 1]) * (2 * SPHI :: s(n / i) - 1);
	}
	*/
	/*
	REP(I, 1, top - 1)
	{
		int i = pos[i], j = pos[i + 1];
		ans += (mem[I] - mem[I - 1]) * (2 * SPHI :: s(stk[i]) - 1);
	}
	*/
	cout << ans << endl;
	cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
	return 0;
}
