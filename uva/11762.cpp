#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <stack>
#include <map>
#include <set>

using namespace std;
const int maxn = 1000000 + 100;

template <typename T> T read()
{
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c)) {
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c)) {
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}
int m, n, cnt;

bool isprime[maxn];
vector <int> prime;

double f[maxn];
bool vis[maxn];

int p[maxn];
/*
double dp(int x)
{
	if (x == 1) return 0.0;
	if (vis[x]) return f[x];
	cerr << x << endl;
	vis[x] = 1;
	register int g(0);
	bool flag = 1;
	REP(i, 1, cnt)
		if (prime[i] > x) break;
		else if (x % prime[i] == 0)
		{
			g++;
			f[x] += dp(x / prime[i]);
		}
	return f[x] = (f[x] + p[x]) / g;
}
*/

stack <int> S;
inline double dp(int x)
{
	if (x == 1) return 0.0;
	if (vis[x]) return f[x];
	while (S.size()) S.pop();
	S.push(x);
	while (!S.empty())
	{
		register int T = S.top();
		if (vis[T]) {S.pop();continue;}
		register int g(0);
		f[T] = 0;
		bool flag = 1;
		REP(i, 1, cnt)
			if (prime[i] > T) break;
			else if (T % prime[i] == 0)
			{
				if (vis[T / prime[i]])
				{
					g++;
					f[T] += f[T / prime[i]];
				}
				else
				{
					flag = 0;
					S.push(T / prime[i]);
					break;
				}
			}
		if (flag)
		{
			vis[T] = 1;
			f[T] = (f[T] + p[T]) / g;
			S.pop();
		}
	}
	vis[x] = 1;
	return f[x];
}

int main()
{
#ifdef CraZYali
	freopen("11762.in", "r", stdin);
	freopen("11762.out", "w", stdout);
#endif
	vis[1] = 1;
	register int T = read<int>(), Case = 0;
	REP(i, 2, 1000000) isprime[i] = 1;
	prime.push_back(-233);
	REP(i, 2, 1000000)
		if (isprime[i])
		{
			for (register int j = 2; j * i <= 1000000 ; j++) isprime[i * j] = 0;
			prime.push_back(i);
		}
	REP(i, 1, 1000000) p[i] = p[i-1] + isprime[i];
	cnt = prime.size() - 1;
	while (T--)
	{
		n = read<int>();
		printf("Case %d: %.10lf\n", ++Case, n ^ 1 ? dp(n) : 0.0);
		fflush(stdout);
	}
	return 0;
}
