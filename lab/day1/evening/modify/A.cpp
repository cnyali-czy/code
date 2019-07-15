#define REP(i, s, e)  for(int i = s; i <= e ; i++)
#define DREP(i, s, e) for(int i = s; i >= e ; i--)

#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>
#define int long long

using namespace std;
const int maxn = 100000 + 10;

int n, L[maxn], R[maxn], ans;
int x[maxn], y[maxn];
bool flag[maxn];

struct Line
{
	int k, b;
	int f(int x) {return k * x + b;}
	bool operator < (Line B) const {return k > B.k || k == B.k && b < B.b;}
}f[maxn], Stack[maxn];

int top;
void push_back(Line A)
{
	if (top && A.k == Stack[top].k && A.b > Stack[top].b) return;
	while (top > 1 && (A.b - Stack[top-1].b) * (Stack[top-1].k - Stack[top].k) <= (Stack[top].b - Stack[top-1].b) * (Stack[top-1].k - A.k)) top--;
	Stack[++top] = A;
}
int solve(int l, int r)
{
	if (l == r) return l;
	int mid = l + r >> 1, x1, x2, y1(l), y2(mid + 1);
	x1 = solve(l, mid);
	x2 = solve(mid + 1, r);
	int temp = l;
	REP(i, mid + 1, r)
	{
		while (temp < x1 && f[temp].f(x[i]) > f[temp+1].f(x[i])) temp++;
		flag[i] &= y[i] <= f[temp].f(x[i]);	
	}
	top = 0;
	while (y1 <= x1 || y2 <= x2)
		if (y2 > x2 || y1 <= x1 && f[y1] < f[y2]) push_back(f[y1++]);
		else push_back(f[y2++]);
	REP(i, l, top + l - 1) f[i] = Stack[i-l+1];
	return top + l - 1;
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	cin >> n;
	DREP(i, n, 1) scanf("%d%d", L + i, R + i);
	REP(i, 1, n)
	{
		x[i] = x[i-1] + 2ll * (R[i] - L[i]);
		y[i] = y[i-1] + (L[i] + R[i]) * (R[i] - L[i]);
		flag[i] = 1;
		f[i].b = y[i] - x[i] * (f[i].k = R[i]);
	}
	solve(1, n);
	REP(i, 1, n) f[i].b = ((y[i] = -y[i]) - x[i] * (f[i].k = -L[i]));
	solve(1, n);
	int last(0);
	REP(i, 1, n) if (flag[i]) chkmax(ans, i - last), last = i;
	cout << ans << endl;
	return 0;
}
