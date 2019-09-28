#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstring>
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

int pos[1 << 21];

int main()
{
#ifdef CraZYali
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n) s[i] = s[i-1] ^ read<int>();
	if (0 && n <= 5000) violence::work();
	else if (0 && n <= 1e5)
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
	else
	{
		memset(pos, 0x3f, sizeof(pos));
		REP(i, 1, n)
			chkmin(pos[s[i]], i);
		REP(j, 0, 19)
			for (int i = 1048575; i >= 0 ;i--)
				if (i & (1 << j)) chkmin(pos[i ^ (1 << j)], pos[i]);
		REP(i, 1, n)
		{
			int t(0), ans(0);
			DREP(j, 19, 0)
				if ((1 << j) & s[i]) ans += (1 << j);
				else if (pos[t ^ (1 << j)] <= i)
				{
					t ^= (1 << j);
					ans += (1 << j + 1);
				}
			printf("%d ", ans);
		}
	}
	return 0;
}
