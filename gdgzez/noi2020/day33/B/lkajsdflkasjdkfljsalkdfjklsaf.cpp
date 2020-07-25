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

int prime[maxP], lp, p_cnt, N, mu[maxn], phi[maxn], Min[maxn];
i64 n, k;
unsigned smu[maxn], sphi[maxn];
bool notp[maxn];
unsigned H[maxP][40];

int lim;
unsigned sgn(i64 x) {return x & 1 ? -1 : 1;}
unsigned sf[maxn];
unsigned f(int x)
{
	if (x == 1) return k;
	int Max = 1, tot = 0;
	while (x > 1)
	{
		int c = 0, t = Min[x];
		while (x % t == 0)
		{
			c++;
			x /= t;
		}
		if (Max < c) Max = c;
		if (Max > k) return 0;
		tot += c;
	}
	return ((tot & 1) ? -1 : 1) * (k - Max + 1);
}
void init(int N)
{
	::N = N;
	mu[1] = smu[1] = phi[1] = sphi[1] = Min[1] = 1;
	sf[1] = f(1);
	REP(i, 2, N)
	{
		if (!notp[i]) mu[prime[++p_cnt] = i] = -1, phi[i] = i - 1, Min[i] = i;
		REP(j, 1, p_cnt)
		{
			int tmp = i * prime[j];if (tmp > N) break;
			notp[tmp] = 1;
			if (i % prime[j]) mu[tmp] = -mu[i], phi[tmp] = phi[i] * (prime[j] - 1), Min[tmp] = prime[j];
			else {phi[tmp] = phi[i] * prime[j];Min[tmp] = Min[i];break;}
		}
		smu[i] = smu[i - 1] + mu[i];
		sphi[i] = sphi[i - 1] + phi[i];
		sf[i] = sf[i - 1] + f(i);
	}
}
i64 curn;
void init2()
{
	REP(i, 1, p_cnt)
	{
		i64 p = prime[i];
		if (p * p > curn)
		{
			lp = i - 1;
			break;
		}
		H[i][0] = 1;
		for (int k = 1; p <= curn; p *= prime[i], k++)
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

struct status
{
	i64 d;
	unsigned H;
	int lst;
	inline bool operator < (const status &B) const {return d < B.d;}
}que[514514];
int head, tail, Max;

int pn;
pair <i64, unsigned> power[514514];

void bfs()
{
	pn = 0;
	que[head = tail = 0] = status{1, 1, 0};
	while (head <= tail)
	{
		i64 d = que[head].d;
		unsigned H = que[head].H;
		int lst = que[head].lst;
		head++;
		if (!H) continue;
		power[++pn] = make_pair(d, H);
//		ans += H * SMU :: S(curn / d);
		if (lst == lp) continue;
		REP(i, lst + 1, lp)
		{
			if (1ll * prime[i] * prime[i] > curn / d) break;
			i64 dd = d * prime[i] * prime[i];
			for (int k = 2; dd <= curn; k++, dd *= prime[i])
				if (::H[i][k]) que[++tail] = status{dd, H * ::H[i][k], i};
			//		else break;
			//		dfs(dd, H * ::H[i][k], i);
		}
	}
}
void Orzjjs()
{
	REP(i, 0, tail)
	{
		i64 d = que[i].d;
		unsigned H = que[i].H;
		if (d <= curn) ans += H * SMU :: S(curn / d);
		else break;
	}
	return;
}

i64 pos[214514], top;
unsigned mem[214514];

namespace SPHI
{
	unsigned mem[maxn];
	unsigned s(unsigned i64 n)
	{
		if (n <= N) return sphi[n];
		unsigned &res = mem[::n / n];
		if (res) return res;
		res = (n * (n + 1) / 2) % (1 << 30);
		for (i64 i = 2, j; i <= n; i = j + 1)
		{
			j = n / (n / i);
			res -= s(n / i) * (unsigned)(j - i + 1);
		}
		return res;
	}
}

int main()
{
#ifdef CraZYali
	file("B");
#endif
	cin >> n >> k;
	for (i64 i = 1, j; i <= n; i = j + 1)
	{
		j = n / (n / i);
		pos[++top] = i - 1;
	}
	pos[++top] = n;
	init(max((int)100, (int)(2 * pow(n, 2. / 3))));
#ifdef CraZYali
	cerr << N << endl;
#endif
	REP(i, 1, top)
	{
		curn = pos[i];
		if (curn <= N) mem[i] = sf[curn];
		else
		{
			for (lim = 1; lim <= k; lim++)
			{
				curn = n;
				init2();
				bfs();
				sort(que, que + tail + 1);
//				sort(power + 1, power + 1 + pn);
				int sta = 1;
				REP(j, i, top)
				{
					curn = pos[j];
					Orzjjs();
					mem[j] += ans;
					ans = 0;
				//	bfs();
				//	dfs(1, 1, 0);
				}
			}
			break;
			//mem[i] = ans;
		}
		/*
#ifdef CraZYali
cout << curn << ' ' << ans << endl;
if (i % 500 == 0) fprintf(stderr, "Done %d / %d = %.2lf%%\n", i, top, i * 100. / top);
#endif*/
		ans = 0;
	}
	REP(I, 2, top)
		ans += (mem[I] - mem[I - 1]) * (2 * SPHI :: s(n / pos[I]) - 1);
	cout << ans % (1 << 30) << endl;
#ifdef CraZYali
	cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
	cerr << tail << endl;
#endif

	return 0;
}
