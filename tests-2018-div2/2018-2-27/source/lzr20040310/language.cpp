#include<iostream>
#include<string>
#include<list>
#include<map>
#include<utility>
#include<cstdio>
using namespace std;
map<string,list<string> > p;
pair<int,list<string> > dfs(const string&);
int main(){
	int n,m,ans=0;
	list<string> ansl;
	freopen("language.in","r",stdin);
	freopen("language.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		string str;
		cin>>str;
	}
	for(int i=1;i<=m;i++){
		string s1,s2;
		cin>>s1>>s2;
		p[s1].push_back(s2);
	}
	for(map<string,list<string> >::iterator i=p.begin();i!=p.end();i++){
		pair<int,list<string> > k=dfs(i->first);
		if(k.first>ans){
			ans=k.first;
			ansl=k.second;
		}
	}
	printf("%d\n",ans);
	for(list<string>::iterator i=ansl.begin();i!=ansl.end();i++)
		cout<<*i<<' ';
	return 0;
}
pair<int,list<string> > dfs(const string &str){
	list<string> ansl;
	if(p.count(str)){
		int ans=0;
		for(list<string>::iterator i=p[str].begin();i!=p[str].end();i++){
			pair<int,list<string> > k=dfs(*i);
			if(k.first>ans){
				ans=k.first;
				ansl=k.second;
			}
		}
		ansl.push_front(str);
		return pair<int,list<string> >(ans+1,ansl);
	}
	ansl.push_back(str);
	return pair<int,list<string> >(1,ansl);
}
