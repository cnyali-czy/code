#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>
#define int long long

using namespace std;
const int maxn = 50000 + 10, maxm = 50000 + 10, maxblock = 223;

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

int m, n, a[maxn];

struct Question
{
	int pos, l, r;
	Question(){}
	Question(int _pos) : pos(_pos) {l = read<int>();r = read<int>();}
}Q[maxm];
bool cmp1(Question A, Question B) {return A.l < B.l || A.l == B.l && A.r < B.r;}
bool cmp2(Question A, Question B) {return A.r < B.r;}
bool cmp3(Question A, Question B) {return A.pos < B.pos;}

int belong[maxn], Left[maxblock], Right[maxblock], block_siz, block_cnt;
void get_belong()
{
	sort(Q + 1, Q + 1 + m, cmp1);
	block_siz = sqrt(n);
	register int l = 1, r = 1;
	while (r < m)
		if (Q[r + 1].l - Q[l].l <= block_siz) r++;
		else
		{
			block_cnt++;
			Left[block_cnt] = l;Right[block_cnt] = r;
			REP(i, l, r) belong[i] = block_cnt;
			l = ++r;
		}
	if (l <= m)
	{
		block_cnt++;
		Left[block_cnt] = l;Right[block_cnt] = m;
		REP(i, l, m) belong[i] = block_cnt;
	}
}

int ans[maxm], cnt[maxn], res;
void add(int x) {res += cnt[x]++;}
void del(int x) {res -= --cnt[x];}

int gcd(int a, int b) {return !b ? a : gcd(b, a % b);}

signed main()
{
#ifdef CraZYali
	freopen("4402.in", "r", stdin);
	freopen("4402.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, n) a[i] = read<int>();
	REP(i, 1, m) Q[i] = Question(i);
	get_belong();
	REP(i, 1, block_cnt)
	{
		sort(Q + Left[i], Q + Right[i] + 1, cmp2);
		register int l = Q[Left[i]].l, r = Q[Left[i]].r;
		REP(j, 1, n) cnt[j] = 0;res = 0;
		REP(j, l, r) add(a[j]);
		ans[Q[Left[i]].pos] = res;
		REP(j, Left[i] + 1, Right[i])
		{
			while (l > Q[j].l) add(a[--l]);
			while (l < Q[j].l) del(a[l++]);
			while (r < Q[j].r) add(a[++r]);
			ans[Q[j].pos] = res;
		}
	}
	sort(Q + 1, Q + 1 + m, cmp3);
	REP(i, 1, m)
	{
		register int len = Q[i].r - Q[i].l + 1;
		if (ans[i]) printf("%lld/%lld\n", ans[i] / gcd(ans[i], len * (len - 1) / 2), len * (len - 1) / 2 / gcd(ans[i], len * (len - 1) / 2));
		else printf("0/1\n");
	}
	return 0;
}
