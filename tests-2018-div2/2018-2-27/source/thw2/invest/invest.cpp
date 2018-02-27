#include<bits/stdc++.h>
using namespace std;
int a[100010],ans1,ans2,ans3,ans4,max1,max2,max3,max4,i,j,k,tmp,n; char c,s[110];
int main(){
	freopen("invest.in","r",stdin);
	freopen("invest.out","w",stdout);
	cin>>n;
	for (i=1;i<=n;i++) cin>>a[i];
	ans1=1; ans2=2; ans3=3; ans4=4;
	while (c!='E') {
		cin>>c;
		if (c=='R') {
			printf("%d %d\n",ans1,ans2);
			cin>>s;
		}
		else if (c>='0' && c<='9') {
			k=c-'0';
			cin>>tmp;
			if (k==ans1 && tmp-a[k]<max2) {
				max1=max2; max2=max3; max3=max4;
				ans1=ans2; ans2=ans3; ans3=ans4;
			} 
			else if (k==ans2 && tmp-a[k]<max3) {
				max2=max3; max3=max4; 
				ans2=ans3; ans3=ans4;
			}
			else if (k==ans3 && tmp-a[k]<max4) {
				max3=max4;
				ans3=ans4;
			}
			if (tmp-a[k]>max1) {
				ans1=k;
				max4=max3; max3=max2; max2=max1;
				max1=tmp-a[k];
			} 
			else if (tmp-a[k]>max2) {
				ans2=k;
				max4=max3; max3=max2;
				max2=tmp-a[k];
			}
			else if (tmp-a[k]>max3) { 
				ans3=k;
				max4=max3;
				max3=tmp-a[k];
			}
			else if (tmp-a[k]>max4) {
				max4=tmp-a[k];
			}
			a[k]=tmp;
		}
	}
	return 0;
}
