#include<bits/stdc++.h>
using namespace std;
int a[100001];
int b[100001];
int n, m;
int main(){
	freopen("invest.in","r",stdin);
	freopen("invest.out","w",stdout);
	int i, j, k;
	char c[20];
	cin >> n;
	for(i = 1; i <= n; i++){
		scanf("%d",&a[i]);
		b[i] = a[i];
	}
	while(1){
		cin >> c;
		int fff = 0;
		if(c[0] >= '0' && c[0] <= '9'){
			for(j = 0; j < strlen(c); j++)if(c[j] >= '0' && c[j] <= '9')fff = fff * 10 + c[j] - '0';
			cin >> k;
			b[fff] = a[fff];
			a[fff] += k;
		}
		else if(c[0] == 'R'){
			int mx1 = 1, mx2 = 0;
			for(j = 2; j <= n; j++){
				if(a[j] - b[j] > a[mx1] - b[mx1]){
					mx2 = mx1;
					mx1 = j;
				}
				else if(a[j] - b[j] > a[mx2] - b[mx2])mx2 = j;
			}
			if(mx1 > mx2)cout << mx2 << " " << mx1 << endl;
			else cout << mx1 << " " << mx2 << endl;
		}
		
		else if(c[0] == 'E')return 0;
	}
	return 0;
}
