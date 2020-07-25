#pragma GCC optimize(3)

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

#include <ctime>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <bitset>

using namespace std;
//const int maxn = 1.82e7 + 10, maxP = 1.17e6;
const int maxn = 2e7 + 10, maxP = 1.5e6;

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)
#define i64 long long

int prime[maxP], lp, p_cnt, N;
short tot[maxn], Max[maxn], cur[maxn];
i64 n, k;
unsigned smu[maxn], sphi[maxn];
bitset <maxn> notp;
short H[maxP][36];

int lim;
unsigned sf[maxn];
void init(int N)
{
	::N = N;
	smu[1] = sphi[1] = 1;
	sf[1] = k;
	REP(i, 2, N)
	{
		if (!notp[i])
		{
			prime[++p_cnt] = i;
			tot[i] = -1;
			Max[i] = cur[i] = 1;
			smu[i] = -1;
			sphi[i] = i - 1;
		}
		REP(j, 1, p_cnt)
		{
			int tmp = i * prime[j];if (tmp > N) break;
			notp[tmp] = 1;
			tot[tmp] = -tot[i];
			Max[tmp] = Max[i];
			if (i % prime[j])
			{
				cur[tmp] = 1;
				smu[tmp] = -smu[i];
				sphi[tmp] = sphi[i] * (prime[j] - 1);
			}
			else
			{
				cur[tmp] = cur[i] + 1;
				if (Max[tmp] < cur[tmp]) Max[tmp] = cur[tmp];
				sphi[tmp] = sphi[i] * prime[j];
				break;
			}
		}
		smu[i] += smu[i - 1];
		sphi[i] += sphi[i - 1];
		sf[i] = sf[i - 1];
		if (Max[i] <= k) sf[i] += tot[i] * (k - Max[i] + 1);
	}
#ifdef CraZYali
	cerr << N << ' ' << p_cnt << endl;
#endif
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
			H[i][k] = (k <= lim ? (k & 1 ? -1 : 1) : 0) + H[i][k - 1];
	}
}

namespace SMU
{
	unsigned mem[maxn];
	unsigned S(unsigned i64 n)
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
	short H;
	int lst;
	inline bool operator < (const status &B) const {return d < B.d;}
}que[220000];
int head, tail;

void bfs()
{
	que[head = tail = 0] = status{1, 1, 0};
	while (head <= tail)
	{
		i64 d = que[head].d;
		short H = que[head].H;
		int lst = que[head].lst;
		head++;
		const i64 End = curn / d;
		REP(i, lst + 1, lp)
		{
			i64 pp = 1ll * prime[i] * prime[i];
			if (pp > End) break;
			register i64 dd = d * pp;
			for (register int k = 2; dd <= curn; k++, dd *= prime[i])
				if (::H[i][k]) que[++tail] = status{dd, H * ::H[i][k], i};
		}
	}
}

i64 pos[200000], top;
unsigned mem[200000];

namespace SPHI
{
	unsigned mem[maxn];
	unsigned s(unsigned i64 n)
	{
		if (n <= N) return sphi[n];
		unsigned &res = mem[::n / n];
		if (res) return res;
		res = (n * (n + 1) / 2) & ((1 << 30) - 1);
		int div = sqrt(n);
		REP(i, 2, div) res -= s(n / i);
		for (i64 i = div + 1, j; i <= n; i = j + 1)
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
	init(max((int)100, (int)(4.05 * pow(n, 2. / 3))));
#ifdef CraZYali
	cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
#endif
	int lst = 1;
	unsigned Ans = 0;
	REP(i, 1, top)
		if (pos[i] <= N) mem[i] = sf[pos[i]];
		else
		{
			REP(j, i, top) mem[j] += SMU :: S(pos[j]);
			for (lim = 2; lim <= k; lim++)
			{
				if (lim <= 34)
				{
					curn = n;
					init2();
					bfs();
					sort(que, que + tail + 1);
				}
				if (lim <= 33)
				{
					REP(j, i, top)
					{
						i64 curn = pos[j];
						REP(i, 0, tail)
							if (que[i].d <= curn) ans += que[i].H * SMU :: S(curn / que[i].d);
							else break;
						mem[j] += ans;
						ans = 0;
					}
				}
				else
				{
					REP(j, i, top)
					{
						curn = pos[j];
						REP(i, 0, tail)
							if (que[i].d <= curn) ans += que[i].H * SMU :: S(curn / que[i].d);
							else break;
						mem[j] += ans * (k - lim + 1);
						ans = 0;
					}
					break;
				}
			}
			break;
		}
	REP(I, lst + 1, top) 
		Ans += (mem[I] - mem[I - 1]) * (2 * SPHI :: s(n / pos[I]) - 1);
	cout << Ans % (1 << 30) << endl;
#ifdef CraZYali
	cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
	cerr << tail << endl;
#endif
	return 0;
}
