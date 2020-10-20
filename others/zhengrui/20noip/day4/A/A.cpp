#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)


#include <cstring>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e6 + 10;

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

namespace SAM
{
	const int maxn = ::maxn << 1;
	int ch[maxn][26], len[maxn], fail[maxn], cur = 1, lst = 1;
	void extend(int c)
	{
		int u = ++cur, v = lst;
		len[u] = len[v] + 1;
		lst = u;
		for (; v && !ch[v][c]; v = fail[v]) ch[v][c] = u;
		if (!v) fail[u] = 1;
		else if (len[ch[v][c]] == len[v] + 1) fail[u] = ch[v][c];
		else
		{
			int New(++cur), Old(ch[v][c]);
			copy(ch[Old], ch[Old] + 26, ch[New]);
			len[New] = len[v] + 1;
			fail[New] = fail[Old];
			fail[Old] = fail[u] = New;
			for (; v && ch[v][c] == Old; v = fail[v]) ch[v][c] = u;
		}
	}
	bool notleaf[maxn];
	int getans()
	{
		REP(i, 2, cur) notleaf[fail[i]] = 1;
		int ans = 0;
		REP(i, 1, cur) ans += !notleaf[i];
		return ans;
	}
}
int n;
char s[maxn];

int main()
{
#ifdef CraZYali
	file("A");
#endif
	scanf("%s", s + 1);
	n = strlen(s + 1);
	REP(i, 1, n) SAM :: extend(s[i] - 'a');
	cout << SAM :: getans() << endl;
	return 0;
}
