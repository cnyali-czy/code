#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;
const int maxn = 50000 + 10, maxS = 1000000;

template <typename T> T read()
{
	T ans = 0, p = 1;
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

struct seg
{
	int l, r, pos;
	seg(){}
	seg(int _l, int _r, int _pos) :pos(_pos) {l = min(_l, _r);r = max(_l, _r);}
	bool operator < (seg B) const {return r > B.r;}
}s[maxn];
bool cmp(seg A, seg B) {return A.l < B.l || A.l == B.l && A.r < B.r;}
priority_queue <seg> q;
priority_queue <int, vector <int>, greater <int> > S;

int n;

int ans[maxn];

int main()
{
#ifdef CraZYali
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n) s[i] = seg(read<int>(), read<int>(), i);
	sort(s + 1, s + 1 + n, cmp);
	REP(i, 1, n) S.push(i);
	int cur = 1;
	REP(i, 1, maxS)
	{
		while (!q.empty() && i > q.top().r)
		{
			S.push(ans[q.top().pos]);
			q.pop();
		}
		while (cur <= n && s[cur].l <= i)
		{
			q.push(s[cur]);
			ans[s[cur++].pos] = S.top();
			S.pop();
		}
	}
	ans[0] = ans[1];
	REP(i, 2, n) chkmax(ans[0], ans[i]);
	REP(i, 0, n) printf("%d\n", ans[i]);
	return 0;
}
