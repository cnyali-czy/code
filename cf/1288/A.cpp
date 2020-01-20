#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
	int T;cin >> T;
	while (T--)
	{
		int n, d;
		cin >> n >> d;
		if (d <= n)
		{
			puts("YES");
			continue;
		}
		bool flag = 0;
		for (int i = 1, j; i <= d; i = j + 1)
		{
			j = d / (d / i);
			if (d / i + (d % i != 0) + i - 1 <= n)
			{
				puts("YES");
				flag = 1;
				break;
			}
		}
		if (!flag) puts("NO");
	}
	return 0;
}
