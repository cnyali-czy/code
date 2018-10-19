#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1e7 + 10;

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

template <typename T> void write(T x)
{
	if (x < 0) putchar('-'), write(-x);
	else if (x / 10) write(x / 10);
	putchar(x % 10 + '0');
}

int m, n, k;
char s[maxn];

int ans[maxn], cnt;

namespace bf
{
	bool is[maxn];
	bool check(int T)
	{
		REP(i, 1, n - T)
			if (s[i] ^ s[i + T]) return 0;
		return 1;
	}
	void work()
	{
		REP(i, 1, n)
			REP(X, 1, 26)
			{
				register char temp = 'a' + X - 1;
				if (temp == s[i]) continue;
				else
				{
					swap(s[i], temp);

					REP(T, 1, n - 1)
						if (!is[T] && check(T))
						{
							is[T] = 1;
							ans[++cnt] = T;
						}
					swap(s[i], temp);
				}
			}

		cout << cnt << endl;
		if (cnt)
		{
			int c = cnt / 100000 + (cnt % 100000 ? 1 : 0), now = c;

			sort(ans + 1, ans + cnt + 1);
			while (now <= cnt)
			{
				printf("%d ", ans[now]);
				now += c;
			}
		}
	}
}

namespace bf1
{
	void work()
	{
		REP(T, 1, n - 1)
		{
			register int x = 0, pos[2];
			REP(i, 1, n - T)
				if (s[i] ^ s[i + T])
				{
					pos[++x] = i;
					if (x > 2) break;
				}
			if (x == 1) ans[++cnt] = T;
			else if (x == 2 && pos[2] - pos[1] == T) ans[++cnt] = T;
		}
		cout << cnt << endl;
		if (cnt)
		{
			register int divide = cnt / 100000 + (cnt % 100000 ? 1 : 0), now = divide;
			while (now <= cnt) {printf("%d ", ans[now]);now += divide;}
		}
	}
}

signed main()
{
#ifdef CraZYali
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	scanf("%s", s + 1);
	n = strlen(s + 1);
	if (n <= 100) bf::work();
	else bf1::work();
	return 0;
}
