/*
 * File Name:	3261.cpp
 * Author	:	CraZYali
 * Year		:	2019.09.18 22:28
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 300000 + 10 << 1, LOG = 25, maxN = maxn * LOG;

template <typename T> inline T read()
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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout);

int ch[maxN][2], s[maxN];
#define ls(p) ch[p][0]
#define rs(p) ch[p][1]

int cur;
void update(int pre, int &p, int val, int dep)
{
	p = ++cur;
	s[p] = s[pre] + 1;
	ls(p) = ls(pre);
	rs(p) = rs(pre);
	if (dep == -1) return;
	bool flag = val & (1 << dep);
	update(ch[pre][flag], ch[p][flag], val, dep - 1);
}
int query(int u, int v, int val, int dep)
{
	if (dep == -1) return 0;
	bool flag = val & (1 << dep);
	if (s[ch[v][flag ^ 1]] - s[ch[u][flag ^ 1]]) return query(ch[u][flag ^ 1], ch[v][flag ^ 1], val, dep - 1) + (1 << dep);
	else return query(ch[u][flag], ch[v][flag], val, dep - 1);
}
int n, m, rt[maxn], sum[maxn];

int main()
{
#ifdef CraZYali
	file("3261");
#endif
	cin >> n >> m;n++;
	sum[1] = 0;
	REP(i, 2, n) sum[i] = sum[i-1] ^ read<int>();
	REP(i, 1, n) update(rt[i-1],rt[i],sum[i],LOG);
	while(m--)
	{
		char c(getchar());
		while (c != 'A' && c != 'Q') c = getchar();//cerr<<c<<endl,c = getchar();//!isalpha(c)) c = getchar();
		if (c == 'A')
		{
			++n;
			update(rt[n-1], rt[n], sum[n] = (sum[n-1] ^ read<int>()), LOG);
		}
		else
		{
			int l(read<int>()), r(read<int>());
			printf("%d\n", query(rt[l-1], rt[r], sum[n] ^ read<int>(), LOG));
		}
	}
	return 0;
}
