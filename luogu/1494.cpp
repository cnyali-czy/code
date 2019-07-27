#define REP(i, s, e) for (int i = s; i <= e ;i++)

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cmath>
#define int long long

using namespace std;
const int maxn = 50000 + 10, maxm = 50000 + 10, maxblock = 230;

template <typename T> T read()
{
	T ans = 0, flag = 1;
	char c = getchar();
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

int n, m, l, r, a[maxn];

struct Question
{
	int l, r, pos;
	Question(){}
	Question(int _pos) : pos(_pos), l(read<int>()), r(read<int>()) {}
}Q[maxm];

bool cmp1(Question A, Question B) {return A.l < B.l;}
bool cmp2(Question A, Question B) {return A.r < B.r;}
bool cmp3(Question A, Question B) {return A.r > B.r;}

int gcd(int a, int b) {return !b ? a : gcd(b, a % b);}

int Left[maxblock], Right[maxblock], block_siz, block_cnt;
void get_belong()
{
	sort(Q + 1, Q + 1 + m, cmp1);
	block_siz = sqrt(n);
	l = r = 1;
	while (r < m)
		if (Q[r+1].l - Q[l].l <= block_siz) r++;
		else
		{
			block_cnt++;
			Left[block_cnt] = l;Right[block_cnt] = r;
			l = ++r;
		}
	if (l <= m)
	{
		block_cnt++;
		Left[block_cnt] = l;Right[block_cnt] = r;
	}
}

int nowans, cnt[maxn];
pair <int, int> ans[maxm];
void add(int val) {nowans += cnt[val]++;}
void del(int val) {nowans -= --cnt[val];}

signed main()
{
#ifdef CraZYali
	freopen("1494.in", "r", stdin);
	freopen("1494.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, n) a[i] = read<int>();
	REP(i, 1, m) Q[i] = Question(i);
	get_belong();
	l = r = 0;
	REP(i, 1, block_cnt)
	{
		if (i & 1)  sort(Q + Left[i], Q + Right[i] + 1, cmp2);
		else        sort(Q + Left[i], Q + Right[i] + 1, cmp3);
		if (!(l + r))
		{
			l = Q[1].l, r = Q[1].r;
			REP(j, l, r) add(a[j]);
		}
		while (l < Q[Left[i]].l) del(a[l++]);
		while (l > Q[Left[i]].l) add(a[--l]);
		while (r < Q[Left[i]].r) add(a[++r]);
		while (r > Q[Left[i]].r) del(a[r--]);
		ans[Q[Left[i]].pos] = make_pair(nowans, (r - l + 1) * (r - l) / 2);
		REP(j, Left[i] + 1, Right[i])
		{
			while (l < Q[j].l) del(a[l++]);
			while (l > Q[j].l) add(a[--l]);
			while (r < Q[j].r) add(a[++r]);
			while (r > Q[j].r) del(a[r--]);
			ans[Q[j].pos] = make_pair(nowans, (r - l + 1) * (r - l) / 2);
		}
	}
	REP(i, 1, m)
		if (!(ans[i].first * ans[i].second)) printf("0/1\n");
		else
		{
			int g = gcd(ans[i].first, ans[i].second);
			printf("%lld/%lld\n", ans[i].first / g, ans[i].second / g);
		}
	return 0;
}
