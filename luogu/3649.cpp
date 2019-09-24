#define  REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
const int maxn = 3e5 + 10;

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int n;
char s[maxn];

const int siz = 26;

int ch[maxn][siz], len[maxn], fail[maxn], even, odd, cur, last;
inline void init()
{
	s[0] = -1;
	fail[0] = 1;
	len[cur = 1] = -1;
}

inline int getfail(int x, int n)
{
	while (s[n - len[x] - 1] != s[n]) x = fail[x];
	return x;
}

inline int newnode(int _len)
{
	len[++cur] = _len;
	return cur;
}

int cnt[maxn];
inline void extend(int pos)
{
	int p(getfail(last, pos));
	if (!ch[p][s[pos]])
	{
		int q(newnode(len[p] + 2));
		fail[q] = ch[getfail(fail[p], pos)][s[pos]];
		ch[p][s[pos]] = q;
	}
	++cnt[last = ch[p][s[pos]]];
}

int main()
{
#ifdef CraZYali
	file("3649");
#endif
	init();
	scanf("%s", s + 1);
	
	REP(i, 1, n = strlen(s + 1))
	{
		s[i] -= 'a';
		extend(i);
	}
	long long ans(0);
	DREP(i, cur, 2)
	{
		cnt[fail[i]] += cnt[i];
		chkmax(ans, 1ll * cnt[i] * len[i]);
	}
	cout << ans << endl;
	return 0;
}
