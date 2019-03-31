#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e6 + 10, maxN = 1e6 + 10;

template <typename T> inline T read()
{
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}

int n, s[maxn];

bool in[maxN];
void input(int x)
{
	if (in[x]) return;
	in[x] = 1;
	REP(i, 0, 17)
		if (x & (1 << i)) input(x - (1 << i));
}
int calc(int x)
{
	int res = 0;
	DREP(i, 17, 0)
		if (x & (1 << i) && in[res + (1 << i)])
			res += 1 << i;
	return res;
}

namespace violence
{
	void work()
	{
		REP(i, 1, n)
		{
			int res = 0;
			REP(j, 0, i) chkmax(res, s[j] + (s[j] ^ s[i]));
			printf("%d ", res);
		}
	}
}

int main()
{
#ifdef CraZYali
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n) s[i] = s[i-1] ^ read<int>();
	if (n <= 5000) violence::work();
	else
	{
		REP(i, 1, n)
		{
			input(s[i-1]);
			int cur(0), res(0);
			REP(j, 0, 17)
				if (s[i] & (1 << j)) res += 1 << j;
				else cur += 1 << j;
			printf("%d ", calc(cur) * 2 + res);
		}
	}

	return 0;
}
