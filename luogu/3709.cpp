#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
const int maxn = 200000 + 10, maxm = 200000 + 10, maxblock = 450;

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
	else
	{
		if (x / 10) write(x / 10);
		putchar(x % 10 + '0');
	}
}

int m, n, cur, a[maxn];

set <int> S;
set <int> :: iterator it;
map <int, int> to;

struct Question
{
	int l, r, pos;
	Question(){}
	Question(int _pos) : pos(_pos) {l = read<int>();r = read<int>();}
}Q[maxm];
bool cmp1(Question A, Question B) {return A.l < B.l;}
bool cmp2(Question A, Question B) {return A.r < B.r;}

int belong[maxm], Left[maxblock], Right[maxblock], ans[maxm], block_siz, block_cnt;

void get_belong()
{
	sort(Q + 1, Q + 1 + m, cmp1);
	block_siz = sqrt(n);
	register int l = 1, r = 1;
	while (r < m)
		if (Q[r + 1].l - Q[l].l > block_siz)
		{
			block_cnt++;
			Left[block_cnt] = l;Right[block_cnt] = r;
			REP(i, l, r) belong[i] = block_cnt;
			l = ++r;
		}
		else r++;
	if (l <= m)
	{
		block_cnt++;
		Left[block_cnt] = l;Right[block_cnt] = m;
		REP(i, l, m) belong[i] = block_cnt;
	}
}

int cnt[maxn], num[maxn], Ans;

void add(int val)
{
	num[cnt[val]]--;
	if (cnt[val] == Ans) Ans++;
	num[++cnt[val]]++;
}
void del(int val)
{
	num[cnt[val]]--;
	if (cnt[val] == Ans && !num[cnt[val]]) Ans--;
	num[--cnt[val]]++;
}

int main()
{
#ifdef CraZYali
	freopen("3709.in", "r", stdin);
	freopen("3709.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, n) S.insert(a[i] = read<int>());
	for (it = S.begin(); it != S.end() ; it++)
		to[*it] = ++cur;
	REP(i, 1, n) a[i] = to[a[i]];
	REP(i, 1, m) Q[i] = Question(i);

	get_belong();

	REP(i, 1, block_cnt)
		sort(Q + Left[i], Q + Right[i] + 1, cmp2);

	register int l, r;
	REP(i, 1, block_cnt)
	{
		l = Q[Left[i]].l, r = Q[Left[i]].r;
		REP(j, l, r) add(a[j]);
		ans[Q[Left[i]].pos] = -Ans;
		REP(j, Left[i] + 1, Right[i])
		{
			while (l > Q[j].l) add(a[--l]);
			while (l < Q[j].l) del(a[l++]);
			while (r > Q[j].r) del(a[--r]);
			while (r < Q[j].r) add(a[++r]);
			ans[Q[j].pos] = -Ans;
		}
		REP(j, l, r) del(a[j]);
		Ans = 0;
	}

	REP(i, 1, m) printf("%d\n", ans[i]);
	return 0;
}
