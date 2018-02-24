#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1000 + 10, inf = (((1 << 30) - 1) << 1) + 1;

int A[maxn], B[15], Y[15], C[15], Z[15];
int N, N1, N2, M, HP, MP, SP, DHP, DMP, DSP, X, ans = inf, T;
bool flag;

struct node
{
	int hp, mp, sp, rnd;
	bool operator < (node B) const{return rnd < B.rnd;}
};
map <node, int> VIS;

inline void dfs(int hp = HP, int mp = MP, int sp = SP, int rnd = 1, int boss = M)
{
	if (boss <= 0) {chkmin(ans, rnd - 1);flag = 1;return;}
	if (hp <= 0 || rnd - 1 >= ans/* ||VIS[(node){hp, mp, sp, rnd}] && VIS[(node){hp, mp, sp, rnd}] <= boss*/) return;
	if (rnd > N) {flag = 1;return;}
//	VIS[(node){hp, mp, sp, rnd}] = boss;
	dfs(min(HP, hp + DHP) - A[rnd], mp, sp, rnd + 1, boss);
	dfs(hp - A[rnd], min(MP, mp + DMP), sp, rnd + 1, boss);
	dfs(hp - A[rnd], mp, min(SP, DSP + sp), rnd + 1, boss - X);
	REP(i, 1, N1)
		if (mp >= B[i]) dfs(hp - A[rnd], mp - B[i], sp, rnd + 1, boss - Y[i]);
	REP(i, 1, N2)
		if (sp >= C[i]) dfs(hp - A[rnd], mp, sp - C[i], rnd + 1, boss - Z[i]);
}

int main()
{
	freopen("boss.in", "r", stdin);
	freopen("boss.out", "w", stdout);
	cin >> T;
	while (T--)
	{
		ans = inf;flag = 0;
		scanf("%d%d%d%d%d%d%d%d%d", &N, &M, &HP, &MP, &SP, &DHP, &DMP, &DSP, &X);
		VIS.clear();
		REP(i, 1, N) scanf("%d", A + i);
		scanf("%d", &N1);
		REP(i, 1, N1) scanf("%d%d", B + i, Y + i);
		scanf("%d", &N2);
		REP(i, 1, N2) scanf("%d%d", C + i, Z + i);
		dfs();

		if (ans == inf)
			if (flag) printf("Tie\n");
			else printf("No\n");
		else printf("Yes %d\n", ans);
	}

	return 0;
}
