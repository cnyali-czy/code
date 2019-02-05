#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 50000 + 10, maxm = 50000 + 10, maxk = 50000 + 10;

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

int m, n, k, a[maxn];

struct Question
{
	int l, r, pos;
	Question(){}
	Question(int _pos) : pos(_pos), l(read<int>()), r(read<int>()) {}
}Q[maxm];
bool cmp1(Question A, Question B) {return A.l < B.l;}
bool cmp2(Question A, Question B) {return A.r < B.r;}

int Left[maxm], Right[maxm], ans[maxm], block_siz, block_cnt;

void get_belong()
{
	sort(Q + 1, Q + 1 + m, cmp1);
	block_siz = sqrt(n);
	register int l = 1, r = block_siz;
	while (r < m)
		if (Q[r + 1].l - Q[l].l <= block_siz) ++r;
		else
		{
			block_cnt++;
			Left[block_cnt] = l;Right[block_cnt] = r;
			l = ++r;
		}
	if (l <= m)
	{
		block_cnt++;
		Left[block_cnt] = l;Right[block_cnt] = m;
	}
}

int cnt[maxn], res;
void add(int val) {res -= cnt[val] * cnt[val];cnt[val]++;res += cnt[val] * cnt[val];}
void del(int val) {res -= cnt[val] * cnt[val];cnt[val]--;res += cnt[val] * cnt[val];}

int main()
{
#ifdef CraZYali
	freopen("2709.in", "r", stdin);
	freopen("2709.out", "w", stdout);
#endif
	cin >> n >> m >> k;
	REP(i, 1, n) a[i] = read<int>();
	REP(i, 1, m) Q[i] = Question(i);
	get_belong();
	REP(i, 1, block_cnt)
	{
		sort(Q + Left[i], Q + Right[i] + 1, cmp2);
		REP(j, 1, k) cnt[j] = 0;res = 0;
		register int l = Q[Left[i]].l, r = Q[Left[i]].r;
		REP(j, l, r) add(a[j]);
		ans[Q[Left[i]].pos] = res;
		REP(j, Left[i] + 1, Right[i])
		{
			while (l < Q[j].l) del(a[l++]);
			while (l > Q[j].l) add(a[--l]);
			while (r < Q[j].r) add(a[++r]);
			ans[Q[j].pos] = res;
		}
	}
	REP(i, 1, m) printf("%d\n", ans[i]);
	return 0;
}
