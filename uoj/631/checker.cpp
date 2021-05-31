#include "testlib.h"
#include<bits/stdc++.h>
using namespace std;
const int M=2e5,N=1e6+5,U=1e9;
struct poi{
	int x,y,d;
	inline friend bool operator<(const poi&a,const poi&b){
		return make_pair(a.x,a.y)<make_pair(b.x,b.y);
	}
	inline friend bool operator==(const poi&a,const poi&b){
		return make_pair(a.x,a.y)==make_pair(b.x,b.y);
	}
};
int main(int argc, char* argv[]){
	int n,m,i,op,x,y;
	vector<poi>ve;
    registerTestlibCmd(argc, argv);
    int limit_n=inf.readInt(0,M,"n"),limit_m=inf.readInt(0,M,"m");
	n=ouf.readInt(0,limit_n,"n");
	for(i=1;i<=n;++i){
		x=ouf.readInt(0,U,"x");
		y=ouf.readInt(0,U,"y");
		ve.push_back(poi{x,y,0});
	}
	auto build=[&](){
		sort(ve.begin(),ve.end());
		if(unique(ve.begin(),ve.end())!=ve.end())quitf(_wa,"Coincident Point");
		map<int,int>mpx,mpy;
		for(auto u:ve)++mpx[u.x],++mpy[u.y];
		int dt=0;
		for(auto&u:ve){
			int newd=mpx[u.x]>mpy[u.y]?0:1;
			if(newd!=u.d)++dt;
			u.d=newd;
		}
		return dt;
	};
	build();
	m=ouf.readInt(0,limit_m,"m");
	int tot=0;
	for(i=1;i<=m;++i){
		op=ouf.readInt(0,1,"opt");
		x=ouf.readInt(0,U,"x");
		y=ouf.readInt(0,U,"y");
		for(auto&u:ve){
			int&v=op==0?u.x:u.y;
			if(v==x)v=y;
		}
		tot+=build();
	}
	int limit=inf.readInt();
	if(tot>=limit)quitf(_ok,"The total step is %d.",tot);
		else quitf(_wa,"The total step is %d.",tot);
	return 0;
}
