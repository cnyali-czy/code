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
#include <queue>
#include <map>
#include <set>

using namespace std;
const int maxn = 100010;

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
int m, n, k;
int ne[maxn], in[maxn];
bool exist[maxn];

void DEL(int x)
{
	in[ne[x]]--;
	exist[x] = 0;
	if (!in[ne[x]]) DEL(ne[x]);
}

int ans[maxn];
int count_in_the_circle(int now, int s)
{
	ans[now] = s;
	if (ans[ne[now]]) return s;
	return ans[now] = count_in_the_circle(ne[now], s + 1);
}
int calc(int x)
{
	if (ans[x]) return ans[x];
	return ans[x] = 1 + calc(ne[x]);
}

int main()
{
#ifdef CraZYali
	freopen("2921.in", "r", stdin);
	freopen("2921.out", "w", stdout);
#endif
	n = read<int>();
	REP(i, 1, n) exist[i] = !(!(++in[ne[i] = read<int>()]));
	REP(i, 1, n)
		if (!in[i] && exist[i]) DEL(i);
	REP(i, 1, n)
		if (in[i] && !ans[i]) count_in_the_circle(i, 1);
	REP(i, 1, n)
		if (!in[i] && !ans[i]) calc(i);
	REP(i, 1, n) printf("%d\n", ans[i]);
	return 0;
}
