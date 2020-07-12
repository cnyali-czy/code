#define REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;
const int maxn = 1000 + 10;

template <typename T> T read()
{
	T ans(0), flag(1);
	char c(getchar());
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

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int m, n, k;

bool c[maxn][maxn];

bool dfs(vector <int> s, int k)
{
	int n = s.size() - 1;
	if (k < 0) return 0;
	int ans = 0;
	REP(i, 1, n) if (s[i] > 1)
	{
		int x = s[i];
		s[i]--;
		ans ^= dfs(s, k - i);
		s[i]--;
		s[i * 2]++;
		ans ^= dfs(s, k);
		return ans;
	}
	k = -k;
	REP(i, 1, 10) k += (1 << i - 1) * s[i];
	int num = 0;
	bool flag = 0;
	REP(i, 1, 10)
	{
		if ((k >> (i - 1) & 1) && !s[i]) return 0;
		if (s[i]) num++;
	}
	DEP(i, 10, 1) if (s[i])
	{
		num--;
		if (!(k >> (i - 1) & 1))
		{
			if (num || !flag) return 0;
		}
		else
		{
			flag = 1;
			int lst = 0;
			DEP(j, i - 1, 1) if (s[j])
			{
				if (k >> (j - 1) & 1) break;
				lst = j;
			}
			DEP(j, lst - 1, 1) if (s[j]) return 0;
		}
	}
	return 1;
}

int main()
{
#ifdef CraZYali
	file("B");
#endif
	REP(i, 0, 1000)
	{
		c[i][0] = 1;
		REP(j, 1, i) c[i][j] = c[i - 1][j] ^ c[i - 1][j - 1];
	}
	register int T = read<int>();
	while (T--)
	{
		n = read<int>();k = read<int>();
		vector <int> s(11, 0);s[1] = n;
		printf("%d\n", dfs(s, k));
	}
	return 0;
}
