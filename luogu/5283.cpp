#define  REP(i, s, e) for (int i = (s), end_##i = (e); i <= end_##i; i++)
#define DREP(i, s, e) for (int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdio>
#include <queue>

using namespace std;
const int maxn = 5e5 + 10, LOG = 32, maxN = maxn * (LOG + 2);

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
long long sum[maxn];

int rt[maxn], ch[maxN][2], s[maxN], best[maxN], cur;
void insert(int pre, int &p, long long val, int dep = LOG)
{
	p = ++cur;
	ch[p][0] = ch[pre][0];
	ch[p][1] = ch[pre][1];
	s[p] = s[pre] + 1;
	if (dep == -1) return best[p] = k, void();
	bool t((val >> dep) & 1);
	insert(ch[pre][t], ch[p][t], val, dep - 1);
}

int pos;
long long query(int u, int v, long long val, int dep = LOG)
{
	if (dep == -1) return (pos = best[v]) * 0;
	bool t((val >> dep) & 1);
	if (s[ch[v][t ^ 1]] - s[ch[u][t ^ 1]]) return query(ch[u][t ^ 1], ch[v][t ^ 1], val, dep - 1) + (1ll << dep);
	else return query(ch[u][t], ch[v][t], val, dep - 1);
}

struct node
{
	long long val;
	int l, r, bst, real;
	bool operator < (node B) const {return val < B.val;}
};
priority_queue <node> q;

inline void push(int l, int r, int real)
{
	if (l > r) return;
	long long val = query(rt[l], rt[r+1], sum[real]);
	q.push(node{val, l, r, pos, real});
}

signed main()
{
#ifdef CraZYali
	file("5283");
#endif
	cin >> n >> m;
	insert(0, rt[1], 0ll);
	REP(i, 1, n)
	{
		k = i;
		insert(rt[i], rt[i+1], sum[i] = sum[i-1] ^ read<long long>());
		push(0, i, i);
	}
	long long ans(0);
	while (m--)
	{
		node top = q.top();q.pop();
		ans += top.val;
		push(top.l, top.bst-1, top.real);
		push(top.bst+1, top.r, top.real);
	}
	cout << ans << endl;
	return 0;
}
