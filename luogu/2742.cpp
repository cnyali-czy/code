#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 10000 + 10;

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

double dis(pair <double, double> A , pair <double, double> B) {return sqrt((A.first - B.first) * (A.first - B.first) + (A.second - B.second) * (A.second - B.second));}
bool judge(pair <double, double> A, pair <double, double> B, pair <double, double> C)
{
	double x1(A.first), y1(A.second), x2(B.first), y2(B.second), x3(C.first), y3(C.second);
	return (y1 - y2) * (x3 - x2) < (y3 - y2) * (x1 - x2);
}
bool cmp(pair <double, double> A, pair <double, double> B) {return A.first < B.first || A.first == B.first && A.second < B.second;}
pair <double, double> P[maxn], S[maxn];
double ans;
int n, top;

void insert(pair <double, double> A)
{
	while (top > 1)
		if (judge(A, S[top-1], S[top])) top--;
		else break;
	S[++top] = A;
}
double calc()
{
	double ret = 0;
	REP(i, 2, top) ret += dis(S[i-1], S[i]);
	return ret;
}

int main()
{
#ifdef CraZYali
	freopen("2742.in", "r", stdin);
	freopen("2742.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n) scanf("%lf%lf", &P[i].first, &P[i].second);
	sort(P + 1, P + 1 + n, cmp);
	REP(i, 1, n) insert(P[i]);
	ans += calc();
	top = 0;
	DREP(i, n, 1) insert(P[i]);
	ans += calc();
	printf("%.2lf", ans);
	return 0;
}
