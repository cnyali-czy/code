#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#include <bits/stdc++.h>

using namespace std;

const int maxn = 500000 + 10, maxm = 500000 + 10;

int read()
{
	register char c = getchar();
	register int res = 0;
	while (!isdigit(c)) c = getchar();
	while (isdigit(c)) res = res * 10 + c - 48, c = getchar();
	return res;
}

int m, n, a[maxn], ans[maxm];

struct Question
{
	int pos, l, r;
	Question(){}
	Question(int _pos) : pos(_pos) {l = read();r = read();}
}Q[maxm];

bool cmp1(Question A, Question B) {return A.l < B.l || A.l == B.l && A.r < B.r;}
bool cmp2(Question A, Question B) {return A.r < B.r;}

int belong[maxm], Left[maxm], Right[maxm], block_siz, block_cnt;

void get_belong()
{
	sort(Q + 1, Q + 1 + m, cmp1);
	block_siz = sqrt(n);
	register int l = 1, r = 1;
	while (r < m)
		if (Q[r + 1].l - Q[l].l < block_siz) r++;
		else
		{
			block_cnt++;
			REP(i, l, r) belong[i] = block_cnt;
			Left[block_cnt] = l;Right[block_cnt] = r;
			l = r = r + 1;
		}
	if (l <= m)
	{
		block_cnt++;
		REP(i, l, m) belong[i] = block_cnt;
		Left[block_cnt] = l;Right[block_cnt] = m;
	}
}

int cnt[maxn], res;

inline void add(int P)
{
	if (!cnt[a[P]]) res++;
	cnt[a[P]]++;
}
inline void del(int P)
{
	cnt[a[P]]--;
	if (!cnt[a[P]]) res--;
}

int vis[1000000 + 10], cur;

int main()
{
#ifdef CraZYali
	freopen("1972-new.in", "r", stdin);
	freopen("1972-new.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n) a[i] = read(), a[i] = (vis[a[i]] ? vis[a[i]] : vis[a[i]] = ++cur);
	cin >> m;
	REP(i, 1, m) Q[i] = Question(i);
	get_belong();
	REP(i, 1, block_cnt) sort(Q + Left[i], Q + Right[i] + 1, cmp2);
	REP(i, 1, block_cnt)
	{
		REP(i, 1, cur) cnt[i] = 0;res = 0;
		register int l = Q[Left[i]].l, r = Q[Left[i]].r;
		REP(j, l, r) add(j);
		ans[Q[Left[i]].pos] = res;
		REP(j, Left[i] + 1, Right[i])
		{
			while (l > Q[j].l) add(--l);
			while (l < Q[j].l) del(l++);
			while (r < Q[j].r) add(++r);
			ans[Q[j].pos] = res;
		}
	}
	REP(i, 1, m) printf("%d\n", ans[i]);
	return 0;
}
