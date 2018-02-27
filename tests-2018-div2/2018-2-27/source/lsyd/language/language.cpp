#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<map>
using namespace std;
map<string,int>p;
map<int,string>pf;
int f[1010][1010],fom[1010][1010];
string s1,s,s2;
void dfs(int r,int l){
	if(fom[r][l]){
	    dfs(r,fom[r][l]);
	    cout<<pf[fom[r][l]]<<' ';
	    dfs(fom[r][l],l);
	}
}
int main(){
	int i,j,k,ans=0,m,n,l=1;
	freopen("language.in","r",stdin);
	freopen("language.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++){
		cin>>s;
		p[s]=i;
		pf[i]=s;
	}
	l--;
	for(i=1;i<=n;i++)
	    for(j=1;j<=n;j++)
	       if(i!=j)f[i][j]=1000000010;
	for(i=1;i<=m;i++){
	    cin>>s1;cin>>s2;
	    f[p[s1]][p[s2]]=-1;
    }
    for(k=1;k<=n;k++)
        for(i=1;i<=n;i++)
            for(j=1;j<=n;j++){
            	if(f[i][j]>f[i][k]+f[k][j]){
                    f[i][j]=f[i][k]+f[k][j];
                    fom[i][j]=k;
                }
            }
    int x,y;
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            if(f[i][j]<ans){ans=f[i][j];x=i,y=j;}
    printf("%d\n",0-ans+1);
    cout<<pf[x]<<' ';
    dfs(x,y);
    cout<<pf[y];
    puts("");
	return 0;
}/*
5 4
hh
ak
ioi
zero
czy
hh ak
ak ioi
hh zero
czy zero
*/

