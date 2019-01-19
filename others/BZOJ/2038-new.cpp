#define REP(i, s, e) for(register int i = s; i <= e ; i ++)

#include <bits/stdc++.h>
#define int long long

using namespace std;
const int maxn = 50000 + 10, maxm = 50000 + 10, maxblock = 240;

int n, m, c[maxn];

struct Question
{
	int pos, l, r;
	Question() {}
	Question(int _pos) : pos(_pos) {scanf("%lld%lld", &l, &r);}
}Q[maxm];

bool cmp1(Question A, Question B) {return A.l < B.l;}
bool cmp2(Question A, Question B) {return A.r < B.r;}
bool cmp3(Question A, Question B) {return A.pos < B.pos;}

int belong[maxm], Left[maxblock], Right[maxblock], divide, block_cnt;
void get_belong()
{
	divide = sqrt(n);
	int lastl = 1, cur = 2;
	while (cur <= m)
	{
		if (Q[cur].l - lastl > divide)
		{
			block_cnt++;
			Left[block_cnt] = lastl;Right[block_cnt] = cur - 1;
			REP(i, lastl, cur - 1) belong[i] = block_cnt;
			lastl = cur;
		}
		cur++;
	}
	if (lastl <= m)
	{
		block_cnt++;
		Left[block_cnt] = lastl;Right[block_cnt] = m;
		REP(i, lastl, m) belong[i] = block_cnt;
	}
}

int ans[maxm];
int gcd(int a, int b) {return !b ? a : gcd(b, a % b);}

int cnt[maxm], res;

signed main()
{
#ifdef CraZYali
	freopen("2038-new.in", "r", stdin);
	freopen("2038-new.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, n) scanf("%lld", c + i);
	REP(i, 1, m) Q[i] = Question(i);
	sort(Q + 1, Q + 1 + m, cmp1);
	get_belong();
	REP(i, 1, block_cnt) sort(Q + Left[i], Q + Right[i] + 1, cmp2);
	REP(i, 1, block_cnt)
	{
		REP(j, 1, n) cnt[j] = 0;res = 0;
		int l = Q[Left[i]].l, r = Q[Left[i]].r;
		REP(j, l, r) res += cnt[c[j]]++;
		ans[Q[Left[i]].pos] = res;
		REP(j, Left[i] + 1, Right[i])
		{
			while (r < Q[j].r) res += cnt[c[++r]]++;
			while (l < Q[j].l) res -= --cnt[c[l++]];
			while (l > Q[j].l) res += cnt[c[--l]]++;
			ans[Q[j].pos] = res;
		}
	}
	
	sort(Q + 1, Q + 1 + m, cmp3);
	REP(i, 1, m)
		if (!ans[i]) printf("0/1\n");
		else
		{
			int len = Q[i].r - Q[i].l + 1;
			len = len * (len - 1) / 2;
			printf("%lld/%lld\n", ans[i] / gcd(ans[i], len), len / gcd(ans[i], len));
		}
	return 0;
}
