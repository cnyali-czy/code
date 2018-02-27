#include<bits/stdc++.h>
using namespace std;
int i,j,n,m,k,ans1=100000000,ans2;
struct stu{
	int kll,shu,jia;
}a[110];
void dfs(int q,int ka,int qian){
	if(qian>100000000)
		return;
	if(q>n)
		return;
	if(ka>ans1||(ka==ans1&&qian>=ans2))
		return;
	if(ka>=k){
		ans1=ka;
		ans2=qian;
		return;
	}
	for(int i=0;i<=a[q].shu;i++)
		dfs(q+1,ka+a[q].kll*i,qian+a[q].jia*i);
}
int cmp(stu a,stu b){
	return a.jia>b.jia;
}
int main(){
	freopen("plan.in","r",stdin);
	freopen("plan.out","w",stdout);
	cin>>n>>k;
	for(i=1;i<=n;i++)
		scanf("%d%d%d",&a[i].jia,&a[i].shu,&a[i].kll);
	sort(a+1,a+1+n,cmp);
	dfs(1,0,0);
	cout<<ans1<<" "<<ans2<<endl;
	return 0;
}
