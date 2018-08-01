#include<bits/stdc++.h>
#define For(i, l, r) for(int i = (l); i <= (r); ++ i)
using namespace std;

string todig(int num) {
	string str;
	for (; num; num /= 10)
		str += (char)(num % 10 + '0');
	reverse(str.begin(), str.end());
	return str;
}

string pre = "c";
string suf = ".in";

const int N = 100100;
int a[N];

int main() {
	freopen("in","r",stdin);

	int n, cases = 1;
	while (~scanf("%d", &n)) {
		For (i, 1, n) scanf("%d", &a[i]);
		freopen ((pre + todig(cases) + suf).c_str(), "w", stdout);
		printf ("%d\n", n/4);
		For (i, 1, n) {
			printf ("%d ", a[i]);
			if (i%4==0) cout << endl;
		}
		fclose(stdout);
		++ cases;
	}
	
	return 0;
}
