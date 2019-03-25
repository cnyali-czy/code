// luogu-judger-enable-o2
#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <stack>
#include <cmath>

using namespace std;
const int maxn = 50000 + 10, maxm = 50000 + 10, maxblock = 1400;

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

int n, a[maxn], m, q, cur;

pair <int, int> R[maxm];
int cnt[1000000 + 5], nowans;
void add(int col) {nowans += !cnt[col]++;}
void del(int col) {nowans -= !--cnt[col];}

struct Question
{
	int l, r, time, pos;
	Question(){}
	Question(int _pos) : pos(_pos), l(read<int>()), r(read<int>()), time(cur) {}
}Q[maxm];
bool cmp1(Question A, Question B) {return A.l < B.l;}
bool cmp2(Question A, Question B) {return A.r < B.r;}

int Left[maxblock], Right[maxblock], block_siz, block_cnt;
void get_belong()
{
	sort(Q + 1, Q + 1 + q, cmp1);
	block_siz = pow(n, 2./3);
	int l = 1, r = 1;
	while (r < q)
		if (Q[r+1].l - Q[l].l <= block_siz) r++;
		else
		{
			block_cnt++;
			Left[block_cnt] = l;Right[block_cnt] = r;
			l = ++r;
		}
	if (l <= q)
	{
		block_cnt++;
		Left[block_cnt] = l;Right[block_cnt] = q;
	}
}
int l, r;
void timego(bool flag = 1)
{
	int i = R[++cur].second;
	if (flag && l <= i && i <= r) del(a[i]);
	swap(a[i], R[cur].first);
	if (flag && l <= i && i <= r) add(a[i]);
}
void timeback(bool flag = 1)
{
	int i = R[cur--].second;
	if (flag && l <= i && i <= r) del(a[i]);
	swap(a[i], R[cur+1].first);
	if (flag && l <= i && i <= r) add(a[i]);
}

int ans[maxm];

int main()
{
#ifdef CraZYali
	freopen("1903.in", "r", stdin);
	freopen("1903.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, n) a[i] = read<int>();
	REP(i, 1, m)
	{
		char c = getchar();
		while (c != 'Q' && c != 'R') c = getchar();
		if (c == 'R')
		{
			int pos(read<int>()), col(read<int>());
			R[++cur] = make_pair(col, pos);
		}
		else {++q;Q[q] = Question(q);}
	}
	get_belong();
	cur = 0;
	/*
	   timego(0);
	   REP(i, 1, n) printf("%d%c", a[i], i == n ? '\n' : ' ' );
	   timego(0);
	   REP(i, 1, n) printf("%d%c", a[i], i == n ? '\n' : ' ' );
	   timego(0);
	   REP(i, 1, n) printf("%d%c", a[i], i == n ? '\n' : ' ' );
	   timego(0);
	   REP(i, 1, n) printf("%d%c", a[i], i == n ? '\n' : ' ' );
	   timeback();
	   REP(i, 1, n) printf("%d%c", a[i], i == n ? '\n' : ' ' );
	   timeback();
	   REP(i, 1, n) printf("%d%c", a[i], i == n ? '\n' : ' ' );
	   timeback();
	   REP(i, 1, n) printf("%d%c", a[i], i == n ? '\n' : ' ' );
	   timeback();
	   REP(i, 1, n) printf("%d%c", a[i], i == n ? '\n' : ' ' );
	   */
	REP(i, 1, block_cnt)
	{
		sort(Q + Left[i], Q + Right[i] + 1, cmp2);
		l = Q[Left[i]].l, r = Q[Left[i]].r;int tim = Q[Left[i]].time;
		while (cur < tim) timego(0);
		while (cur > tim) timeback(0);
		REP(j, l, r) add(a[j]);
		ans[Q[Left[i]].pos] = nowans;

		REP(j, Left[i] + 1, Right[i])
		{
			while (cur < Q[j].time) timego();
			while (cur > Q[j].time) timeback();
			while (l < Q[j].l) del(a[l++]);
			while (l > Q[j].l) add(a[--l]);
			while (r < Q[j].r) add(a[++r]);
			/*
			   puts("");
			   printf("%d %d %d\n", l, r, nowans);
			   REP(i, 1, n) printf("%d%c", a[i], i == n ? '\n' :' ' );
			   puts("");
			   */
			ans[Q[j].pos] = nowans;
		}
		REP(j, l, r) del(a[j]);
	}
	REP(i, 1, q) printf("%d\n", ans[i]);
	return 0;
}

