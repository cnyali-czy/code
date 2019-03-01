#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 50000 + 10;
const double eps = 1e-9;

int n;
struct line
{
	double A, B;
	int pos;
	line() {}
	void input(int _pos) {pos = _pos;scanf("%lf%lf", &A, &B);}
	bool operator < (line BB) const
	{
		if (fabs(A - BB.A) < eps) return B < BB.B;
		return A < BB.A;
	}
}l[maxn];

double crossx(line A, line B) {return -(A.B - B.B) / (A.A - B.A);}

line S[maxn];
int top;

void insert(line A)
{
	while (top)
	{
		if (fabs(S[top].A - A.A) < eps) top--;
		else if (top > 1 && crossx(A, S[top - 1]) <= crossx(S[top], S[top-1])) top--;
		else break;
	}
	S[++top] = A;
}
bool flag[maxn];

int main()
{
#ifdef CraZYali
	freopen("1007.in", "r", stdin);
	freopen("1007.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n) l[i].input(i);
	sort(l + 1, l + n + 1);
	REP(i, 1, n) insert(l[i]);
	REP(i, 1, top) flag[S[i].pos] = 1;
	REP(i, 1, n) if (flag[i]) printf("%d ", i);
	return 0;
}
