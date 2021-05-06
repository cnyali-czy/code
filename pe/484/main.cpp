/*
	Problem:	main.cpp
	Time:		2021-05-04 15:32
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <cstdio>
#define int __int128

using namespace std;
const int maxn = 70710700, maxp = 4157480;

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

int p_cnt, p[maxp], n;
bool notp[maxn];

vector <int> h[maxp];
void init(int N)
{
	REP(i, 2, N)
	{
		if (!notp[i]) p[++p_cnt] = i;
		const int lim = N / i;
		REP(j, 1, p_cnt)
		{
			if (p[j] > lim) break;
			int t = i * p[j];
			notp[t] = 1;
			if (i % p[j] == 0) break;
		}
	}
	REP(i, 1, p_cnt)
	{
		int p = ::p[i];
		h[i].push_back(0);
		h[i][0] = 1;
		static int f[55];
		f[0] = 1;
		const int lim = n / p;
		for (int k = 1, pk = p; pk <= n; k++, pk *= p)
		{
			h[i].push_back(0);
			f[k] = pk / p * __gcd(k, p);
			if (pk > lim) break;
		}
		for (int k = 2, pk = p * p; pk <= n; k++, pk *= p)
		{
			int res = f[k];
			REP(j, 0, k - 1)
				res -= h[i][j];
			h[i][k] = res;
			if (pk > lim) break;
		}
	}
}
int ans;
void dfs(int x, int h, int lst)
{
	ans += (n / x) * h;
	const int lim = n / x;
	static int dfn=0;++dfn;
	REP(i, lst + 1, p_cnt)
	{
		int p = ::p[i];
		if (p * p > lim) break;
		for (int k = 2, pk = p * p; pk <= lim; k++, pk *= p)
		{
			dfs(x * pk, h * ::h[i][k] , i);
		}
	}
}

signed main()
{
#ifdef CraZYali
	file("main");
#endif
	n = 1;//5000000000000000;
	init(sqrt(n) + 5);
	dfs(1, 1, 0);
	string res="";
	int x = ans;
	REP(i, 0, 200) res += (char)(x % 10 + 48), x /= 10;
	reverse(res.begin(), res.end());
	while(res[0]=='0')res=res.substr(1);
	cout << res << endl;


	return 0;
}
