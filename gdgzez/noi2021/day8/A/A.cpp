#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <ctime>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 5e6 + 10;

int n, m;
int a[maxn], b[maxn];
inline char nc(){
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
#define getchar nc
inline int read()
{
	char c = getchar();
	int res = 0;
	while (!isdigit(c)) c = getchar();
	while ( isdigit(c)) res = res * 10 + (c - 48), c = getchar();
	return res;
}
namespace fk
{
	const int maxN = 1e6 + 5;
	int N, ca[maxN], cb[maxN];

	int prime[maxN], mu[maxN], to[maxN], p_cnt, tn[maxN];
	bool notp[maxN];

	int cnt[maxn];
//	vector <int> Div[1000005];
	int pool[5000000], *cur = pool, *Div[maxN];
	int D[maxN], C[maxN];
	void init(int n)
	{
		mu[1] = to[1] = tn[1] = D[1] = 1;
		REP(i, 2, n)
		{
			if (!notp[i])
			{
				prime[++p_cnt] = i;
				mu[i] = -1;
				to[i] = i;
				tn[i] = i;
				D[i] = 2;C[i] = 1;
			}
			REP(j, 1, p_cnt)
			{
				int t = i * prime[j];
				if (t > n) break;
				notp[t] = 1;
				if (i % prime[j])
				{
					mu[t] = -mu[i];
					to[t] = to[i] * prime[j];
					tn[t] = tn[i] * prime[j];
					D[t] = D[i] * 2;C[t] = 1;
				}
				else
				{
					D[t] = D[i] / (C[i] + 1) * (C[i] + 2);
					C[t] = C[i] + 1;
					tn[t] = tn[i];
					if (to[i] % prime[j] == 0) to[t] = to[i] / prime[j];
					else to[t] = to[i] * prime[j];
					break;
				}
			}
		}
//		REP(i, 1, n) if (mu[i]) for (int j = i; j <= n; j += i) if (tn[j] == j) cnt[j]++;
		REP(i, 1, n) if (i == tn[i])
		{
			Div[i] = cur;
			if (i < n) cur += D[i];
		}
//		REP(i, 1, n) Div[i].resize(cnt[i]), cnt[i] = 0;
		REP(i, 1, n) if (mu[i]) for (int j = i; j <= n; j += i) if (tn[j] == j) Div[j][cnt[j]++] = i;
	}

	int mem[maxN];
	int main()
	{
		REP(i, 1, n) N = max(N, a[i]), ca[a[i]]++;
		REP(i, 1, m) N = max(N, b[i]), cb[b[i]]++;
		init(N);
		i64 ans = 0;
	
		/*
		REP(T, 1, N) for (auto d : Div[T])
			REP(i, 1, N / T) REP(j, 1, N / T) if (to[i * j] == to[T / d])
			ans += mu[d] * ca[i * T] * cb[j * T];
			*/

		int c = 0;
		REP(T, 1, N)
		{
			const int lll = N / T;
			REP(j, 1, lll) mem[to[j * T]] += cb[j * T];
			int tt = tn[T];
			REP(I, 0, cnt[tt] - 1)
			{
				int d = Div[tt][I], fk;
				REP(i, 1, lll) if (fk = mem[to[i * d]])
				{
					c++;
					ans += (i64)mu[d] * ca[i * T] * fk;
//					REP(j, 1, N / T) if (to[j * T] == to[i * d])
//						ans += mu[d] * ca[i * T] * cb[j * T];
				}
			}
			REP(j, 1, lll) mem[to[j * T]] = 0;
		}
		cerr << c << endl;

		cout << ans << endl;
		cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
		return 0;
	}
}
int main()
{
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
	n = read();m = read();
	REP(i, 1, n) a[i] = read();
	REP(i, 1, m) b[i] = read();
	return fk :: main();
	return 0;
}
