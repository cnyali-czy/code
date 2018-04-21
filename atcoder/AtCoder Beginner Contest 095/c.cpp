#include <bits/stdc++.h>

using namespace std;

int main()
{
#ifdef CraZYali
	freopen("c.in", "r", stdin);
	freopen("c.out", "w", stdout);
#endif
	int A, B, C, X, Y;
	cin >> A >> B >> C >> X >> Y;
	C *= 2;
	if (A + B > C)
		if (X > Y)
			if (A < C) printf("%d", C * Y + (X - Y) * A);
			else printf("%d", C * X);
		else
			if (B < C) printf("%d", C * X + (Y - X) * B);
			else printf("%d", C * Y);
	else printf("%d", A * X + B * Y);
	return 0;
}
