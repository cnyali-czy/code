/*
	Problem:	C.cpp
	Time:		2020-06-11 16:03
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <cstring>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <cstdio>
#define i64 long long
using namespace std;
const int maxn = 3e5 + 10;

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

int n;
char s[maxn];

namespace SAM
{
	const int maxn = ::maxn << 1;
	int ch[maxn][26], fail[maxn], len[maxn], last = 1, cur = 1, anc[maxn][21], pos[maxn], f[maxn];
	bool vis[maxn];
	void extend(int c, int id)
	{
		int u = ++cur, v = last;
		pos[id] = u;
		len[u] = len[v] + 1;
		for (; v && !ch[v][c]; v = fail[v]) ch[v][c] = u;
		if (!v) fail[u] = 1;
		else
		{
			int Old = ch[v][c];
			if (len[Old] == len[v] + 1) fail[u] = Old;
			else
			{
				int New(++cur);
				len[New] = len[v] + 1;
				copy(ch[Old], ch[Old] + 26, ch[New]);
				fail[New] = fail[Old];
				fail[Old] = fail[u] = New;
				for (; v && ch[v][c] == Old; v = fail[v]) ch[v][c] = New;
			}
		}
		anc[u][0] = fail[u];
		last = u;
	}
#define L(x) (len[fail[x]] + 1)
#define R(x) len[x]
	void build()
	{
		REP(i, 1, cur) anc[i][0] = fail[i], f[i] = len[fail[i]];
		REP(j, 1, 20) DEP(i, cur, 1)
			anc[i][j] = anc[anc[i][j - 1]][j - 1];
	}
	int find(int x, int l)
	{
		if (L(x) <= l && l <= R(x)) return x;
		DEP(i, 20, 0) if (anc[x][i] && R(anc[x][i]) >= l) x = anc[x][i];
		return x;
	}
#ifdef CraZYali
	vector <string> v[maxn];
	void output()
	{
		REP(i, 1, n) REP(j, i, n)
		{
			int p = 1;
			string ccc = "";
			REP(k, i, j)
			{
				ccc += s[k];
				p = ch[p][s[k] - 'a'];
			}
			v[p].emplace_back(ccc);
		}
		REP(i, 1, cur) printf("%d%c", pos[i], i == end_i ? '\n' : ' ');
		REP(i, 1, cur) printf("%d%c", fail[i], i == end_i ? '\n' : ' ');
		REP(i, 1, cur) printf("%d%c", len[i], i == end_i ? '\n' : ' ');
		REP(i, 1, cur) printf("%d %d\n", L(i), R(i));
		REP(i,1,cur)
		{
			sort(v[i].begin(),v[i].end(),[](string a,string b){return a.size()<b.size();});
			v[i].resize(unique(v[i].begin(),v[i].end())-v[i].begin());
			printf("%d: ", i);
			for(auto j:v[i])cout<<j<<' ';puts("");
		}
	}
#endif
}

#define ui64 unsigned long long 
const ui64 base = 1e9 + 7;
ui64 bin[maxn];

struct
{
	ui64 H[maxn];
	void init(char s[])
	{
		H[0] = 0;
		REP(i, 1, n) H[i] = H[i - 1] * base + s[i];
	}
	ui64 query(int l, int r) {return H[r] - H[l - 1] * bin[r - l + 1];}
}h1, h2;
bool judge(int l, int r) {return h1.query(l, r) == h2.query(n - r + 1, n - l + 1);}

int good[maxn];

int main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();
	scanf("%s", s + 1);
	REP(i, 1, n) SAM :: extend(s[i] - 'a', i);
	SAM :: build();
//	SAM :: output();
	bin[0] = 1;
	REP(i, 1, n) bin[i] = 1ll * bin[i - 1] * base;
	h1.init(s);reverse(s + 1, s + 1 + n);h2.init(s);reverse(s + 1, s + 1 + n);
	REP(i, 1, n) good[i] = 1;
	REP(i, 1, n)
	{
		int l = 1, r = min(i, n + 1 - i), gd = 1;
		while (l <= r)
		{
			int mid = l + r >> 1;
			if (judge(i - mid + 1, i + mid - 1)) {gd = mid;l = mid + 1;}
			else r = mid - 1;
		}
		chkmax(good[i + gd - 1], gd + gd - 1);
	}
	REP(i, 1, n - 1) if (s[i] == s[i + 1])
	{
		int l = 1, r = min(i, n - i), gd = 1;
		while (l <= r)
		{
			int mid = l + r >> 1;
			if (judge(i - mid + 1, i + mid)) {gd = mid;l = mid + 1;}
			else r = mid - 1;
		}
		chkmax(good[i + gd], gd + gd);
	}
	DEP(i, n - 1, 1) chkmax(good[i], good[i + 1] - 2);
//	REP(i, 1, n) printf("%d%c", good[i], i == n ? '\n' : ' ' );
//	REP(i, 1, SAM :: cur) printf("%d%c", SAM :: f[i], i == n ? '\n' : ' ' );
	i64 ans = 0;
	REP(i, 1, n)
	{
		int p = SAM :: find(SAM :: pos[i], good[i]);
		/*
		for (int q = SAM :: fail[p]; q && !SAM :: vis[q]; SAM :: vis[q] = 1, q = SAM :: fail[q]) ans += SAM :: len[q] - SAM :: len[SAM :: fail[q]];
		ans += good[i] - SAM :: f[p] + 1;
		SAM :: f[p] = good[i];
		*/
		if (!SAM :: vis[p])
		{
			if (SAM :: f[p] <= good[i])
			{
				ans += good[i] - SAM :: f[p];
				SAM :: f[p] = good[i];
			}
			if (SAM :: f[p] == SAM :: len[p]) SAM :: vis[p] = 1;
		}
		for (int y = SAM :: fail[p]; y && !SAM :: vis[y]; y = SAM :: fail[y])
		{
			ans += SAM :: len[y] - SAM :: f[y];
			SAM :: f[y] = SAM :: len[y];
			SAM :: vis[y] = 1;			
		}
		printf("%lld\n", ans);
//		printf("%d%c", p, i == n ? '\n' : ' ');
	}
	return 0;
}
