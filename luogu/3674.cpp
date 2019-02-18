#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 100000 + 10, maxm = 100000 + 10, maxnum = 100000 + 10, N = 100000;

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

int n, m, a[maxn];

struct Question
{
	int opt, l, r, pos, x;
	Question(){};
	Question(int _pos) : pos(_pos), opt(read<int>()), l(read<int>()), r(read<int>()), x(read<int>()) {}
}Q[maxm];
bool cmp1(Question A, Question B) {return A.l < B.l;}
bool cmp2(Question A, Question B) {return A.r < B.r;}

int Left[maxm], Right[maxm], block_cnt, block_siz;
void get_belong()
{
	sort(Q + 1, Q + 1 + m, cmp1);
	block_siz = sqrt(n);
	int l(1), r(1);
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

int cnt[maxn];
bitset <maxn> in1, in2;
void add(int val) {if (!(cnt[val]++)) in1.set(val), in2.set(N - val);}
void del(int val) {if (!(--cnt[val])) in1.reset(val), in2.reset(N - val);}

bool ans[maxm];
bool getans(int id)
{
	int opt = Q[id].opt, x = Q[id].x;
	if (opt == 1) return (in1 & (in1 << x)).any();
	else if (opt == 2) return (in1 & (in2 >> (N - x))).any();
	else
	{
		for (int i = 1; i * i <= x; i++)
			if (x % i == 0 && in1[i] && in1[x / i]) return 1;
		return 0;
	}
}

int main()
{
#ifdef CraZYali
	freopen("3674.in", "r", stdin);
	freopen("3674.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, n) a[i] = read<int>();
	REP(i, 1, m) Q[i] = Question(i);
	get_belong();
	REP(i, 1, block_cnt)
	{
		sort(Q + Left[i], Q + Right[i] + 1, cmp2);
		int l = Q[Left[i]].l, r = Q[Left[i]].r;
		REP(j, l, r) add(a[j]);
		ans[Q[Left[i]].pos] = getans(Left[i]);
		REP(j, Left[i] + 1, Right[i])
		{
			while (l < Q[j].l) del(a[l++]);
			while (l > Q[j].l) add(a[--l]);
			while (r < Q[j].r) add(a[++r]);
			ans[Q[j].pos] = getans(j);
		}
		REP(j, l, r) del(a[j]);
	}
	REP(i, 1, m) puts(ans[i] ? "hana" : "bi");
	return 0;
}
