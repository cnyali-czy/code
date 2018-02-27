#include<bits/stdc++.h>
using namespace std;
int i,j,k,l,n,m,ans=-100000,q,dq;
bool p[110];
struct node{
   char s[21],w[21];
}a[110];
int t[2001],d[2001];
char c[21];
int pd(int k,int sum){
    int i,j;
    for(i=0;i<strlen(a[k].w);i++)
    if(a[k].w[i]!=a[sum].s[j++])return 0;
    return 1;
}
void ss(int k,int sum){
    int i,j;
    if(sum>ans){
	ans=sum;
	for(i=l;i>=l-sum+1;i--)
	d[++q]=t[i];if(q>dq)dq=q;
	q=0;
	}
    if(sum==m){ans=sum;return;}
    for(i=1;i<=m;i++){
    if(strcmp(a[k].w,a[i].s)==0){t[++l]=i;ss(i,sum+1);}
	}
}
int main()
{
	freopen("language.in","r",stdin);
	freopen("language.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)scanf("%s",&c);
	for(i=1;i<=m;i++)scanf("%s%s",&a[i].s,&a[i].w);
	for(i=1;i<=m;i++){
	t[++l]=i;
	ss(i,0);
	}
	int u;
	printf("%d\n",ans*2-1);
	for(i=dq;i>=1;i--){
	u++;
	if(u%2==1)printf("%s",a[d[i]].s);
	else printf("%s %s",a[d[i]].s,a[d[i]].w);
	if(i!=1)printf(" ");
    }
	return 0;
}
