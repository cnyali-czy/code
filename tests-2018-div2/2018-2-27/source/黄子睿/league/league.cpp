#include<bits/stdc++.h>
using namespace std;
int i,j,n,m;
char a;
struct stu{
	int name,fs;
}q[60];
int cmp(stu a,stu b){
	return a.fs>b.fs;
}
int main()
{
	freopen("league.in","r",stdin);
	freopen("league.out","w",stdout);
	cin>>n;
	for(i=1;i<=n;i++)
		q[i].name=i;
	for(i=1;i<=n;i++){
		getchar();
		for(j=1;j<=n;j++){
			scanf("%c",&a);
			switch (a){
				case 'W':{
					q[i].fs+=3;
					break;
				}
				case 'L':{
					q[i].fs++;
					q[j].fs++;
					break;
				}
				case 'w':{
					q[j].fs+=3;
					break;
				}
			}
		}
	}
	sort(q+1,q+1+n,cmp);
	for(i=1;i<=n;i++){
		printf("%d",q[i].name);
		if(q[i].fs!=q[i+1].fs){
			puts("");
			return 0;
		}
		printf(" ");
	}
}
