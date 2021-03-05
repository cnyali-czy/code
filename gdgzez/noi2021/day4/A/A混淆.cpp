#define p48 main
#define p21 ::
#define p44 signed
#define p4 struct
#define p29 try
#define p58 break
#define p53 !=
#define p70 inline
#define p67 mutable
#define p12 unsigned
#define p69 if
#define p9 while
#define p54 case
#define p3 new
#define p68 static
#define p26 explicit
#define p71 namespace
#define p66 &lt;&lt;
#define p17 else
#define p28 true
#define p62 friend
#define p37 ++
#define p20 &gt;&gt;
#define p40 &lt;=
#define p39 &gt;=
#define p24 +=
#define p63 throw
#define p32 enum
#define p38 protected
#define p10 union
#define p51 --
#define p65 const
#define p7 continue
#define p15 int 
#define p14 false
#define p23 typeid
#define p57 export
#define p16 [
#define p64 private
#define p52 catch
#define p45 endl
#define p46 int 
#define p42 for
#define p11 default
#define p31 void
#define p55 cin
#define p60 printf
#define p59 sizeof
#define p5 bool
#define p2 using
#define p50 ]
#define p8 float
#define p35 cout
#define p6 asm
#define p18 class
#define p34 {
#define p56 auto
#define p36 goto
#define p41 typedef
#define p0 typename
#define p13 }
#define p30 -=
#define p33 ==
#define p19 do
#define p47 switch
#define p22 ;
#define p49 this
#define p61 return
#define p27 public
#define p43 double
#define p1 short
#define p25 long
/*
Problem:	A.cpp
Time:		2021-03-04 09:13
Author:		CraZYali
E-Mail:		yms-chenziyang@outlook.com
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <unordered_map>
#include <set>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>

 /*e0BFcD*/ p2 /*e0BFcD*/   /*e0BFcD*/ p71 /*e0BFcD*/  std /*e0BFcD*/ p22 /*e0BFcD*/ 
 /*Cc64EA*/ p65 /*Cc64EA*/   /*Cc64EA*/ p15 /*Cc64EA*/ maxn = 3e5 + 10 /*Cc64EA*/ p22 /*Cc64EA*/ 

template < /*BEf215*/ p0 /*BEf215*/  T>
 /*B36F84*/ p70 /*B36F84*/  T read()
 /*7cF6A0*/ p34 /*7cF6A0*/ 
T ans = 0, flag = 1 /*48CE5B*/ p22 /*48CE5B*/ 
char c = getchar() /*3c075D*/ p22 /*3c075D*/ 
 /*93ca02*/ p9 /*93ca02*/  (!isdigit(c))
 /*86Dc3b*/ p34 /*86Dc3b*/ 
 /*A37C6b*/ p69 /*A37C6b*/  (c  /*A37C6b*/ p33 /*A37C6b*/  '-') flag = -1 /*A37C6b*/ p22 /*A37C6b*/ 
c = getchar() /*2ca1f4*/ p22 /*2ca1f4*/ 
 /*De38E2*/ p13 /*De38E2*/ 
 /*71e09B*/ p9 /*71e09B*/  (isdigit(c))
 /*ae2Af0*/ p34 /*ae2Af0*/ 
ans = ans * 10 + (c - 48) /*c0f845*/ p22 /*c0f845*/ 
c = getchar() /*C1cED5*/ p22 /*C1cED5*/ 
 /*bA95Ed*/ p13 /*bA95Ed*/ 
 /*a83e65*/ p61 /*a83e65*/  ans * flag /*a83e65*/ p22 /*a83e65*/ 
 /*C9a7D3*/ p13 /*C9a7D3*/ 

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

 /*bF9B5E*/ p15 /*bF9B5E*/ n, m, u /*bF9B5E*/ p16 /*bF9B5E*/ maxn /*bF9B5E*/ p50 /*bF9B5E*/ , v /*bF9B5E*/ p16 /*bF9B5E*/ maxn /*bF9B5E*/ p50 /*bF9B5E*/  /*bF9B5E*/ p22 /*bF9B5E*/ 
vector <int> G /*25DF0B*/ p16 /*25DF0B*/ maxn /*25DF0B*/ p50 /*25DF0B*/ , T /*25DF0B*/ p16 /*25DF0B*/ maxn /*25DF0B*/ p50 /*25DF0B*/ , U /*25DF0B*/ p16 /*25DF0B*/ maxn /*25DF0B*/ p50 /*25DF0B*/  /*25DF0B*/ p22 /*25DF0B*/ 

 /*a6D07f*/ p15 /*a6D07f*/ dfn /*a6D07f*/ p16 /*a6D07f*/ maxn /*a6D07f*/ p50 /*a6D07f*/ , low /*a6D07f*/ p16 /*a6D07f*/ maxn /*a6D07f*/ p50 /*a6D07f*/ , dfs_clock, siz /*a6D07f*/ p16 /*a6D07f*/ maxn /*a6D07f*/ p50 /*a6D07f*/ , dep /*a6D07f*/ p16 /*a6D07f*/ maxn /*a6D07f*/ p50 /*a6D07f*/ , anc /*a6D07f*/ p16 /*a6D07f*/ 20 /*a6D07f*/ p50 /*a6D07f*/  /*a6D07f*/ p16 /*a6D07f*/ maxn /*a6D07f*/ p50 /*a6D07f*/ , mi /*a6D07f*/ p16 /*a6D07f*/ 20 /*a6D07f*/ p50 /*a6D07f*/  /*a6D07f*/ p16 /*a6D07f*/ maxn /*a6D07f*/ p50 /*a6D07f*/  /*a6D07f*/ p22 /*a6D07f*/ 
 /*e8d1Cc*/ p15 /*e8d1Cc*/ c /*e8d1Cc*/ p16 /*e8d1Cc*/ maxn /*e8d1Cc*/ p50 /*e8d1Cc*/  /*e8d1Cc*/ p22 /*e8d1Cc*/ 
 /*a4B391*/ p31 /*a4B391*/  dfs1( /*a4B391*/ p15 /*a4B391*/ u)
 /*B91a6A*/ p34 /*B91a6A*/ 
dfn /*BF207e*/ p16 /*BF207e*/ u /*BF207e*/ p50 /*BF207e*/  = low /*BF207e*/ p16 /*BF207e*/ u /*BF207e*/ p50 /*BF207e*/  =  /*BF207e*/ p37 /*BF207e*/ dfs_clock /*BF207e*/ p22 /*BF207e*/ 
siz /*1FED39*/ p16 /*1FED39*/ u /*1FED39*/ p50 /*1FED39*/  = 1 /*1FED39*/ p22 /*1FED39*/ 

 /*B1904d*/ p15 /*B1904d*/ cnt = 0, fk = 0 /*B1904d*/ p22 /*B1904d*/ 
 /*d76CEf*/ p42 /*d76CEf*/  ( /*d76CEf*/ p15 /*d76CEf*/ v : G /*d76CEf*/ p16 /*d76CEf*/ u /*d76CEf*/ p50 /*d76CEf*/ )
 /*Cc93aF*/ p69 /*Cc93aF*/  (!dfn /*Cc93aF*/ p16 /*Cc93aF*/ v /*Cc93aF*/ p50 /*Cc93aF*/ )
 /*73F82c*/ p34 /*73F82c*/ 
T /*6FbC7e*/ p16 /*6FbC7e*/ u /*6FbC7e*/ p50 /*6FbC7e*/ .emplace_back(v) /*6FbC7e*/ p22 /*6FbC7e*/ 
dep /*1c893e*/ p16 /*1c893e*/ v /*1c893e*/ p50 /*1c893e*/  = dep /*1c893e*/ p16 /*1c893e*/ anc /*1c893e*/ p16 /*1c893e*/ 0 /*1c893e*/ p50 /*1c893e*/  /*1c893e*/ p16 /*1c893e*/ v /*1c893e*/ p50 /*1c893e*/  = u /*1c893e*/ p50 /*1c893e*/  + 1 /*1c893e*/ p22 /*1c893e*/ 

dfs1(v) /*D91Cad*/ p22 /*D91Cad*/ 
low /*8ed6BD*/ p16 /*8ed6BD*/ u /*8ed6BD*/ p50 /*8ed6BD*/  = min(low /*8ed6BD*/ p16 /*8ed6BD*/ u /*8ed6BD*/ p50 /*8ed6BD*/ , low /*8ed6BD*/ p16 /*8ed6BD*/ v /*8ed6BD*/ p50 /*8ed6BD*/ ) /*8ed6BD*/ p22 /*8ed6BD*/ 
 /*baE1d8*/ p69 /*baE1d8*/  (low /*baE1d8*/ p16 /*baE1d8*/ v /*baE1d8*/ p50 /*baE1d8*/  >= dfn /*baE1d8*/ p16 /*baE1d8*/ u /*baE1d8*/ p50 /*baE1d8*/ ) cnt /*baE1d8*/ p37 /*baE1d8*/ , fk = v /*baE1d8*/ p22 /*baE1d8*/ 
siz /*cbeC9F*/ p16 /*cbeC9F*/ u /*cbeC9F*/ p50 /*cbeC9F*/   /*cbeC9F*/ p24 /*cbeC9F*/  siz /*cbeC9F*/ p16 /*cbeC9F*/ v /*cbeC9F*/ p50 /*cbeC9F*/  /*cbeC9F*/ p22 /*cbeC9F*/ 
 /*194Cbd*/ p13 /*194Cbd*/ 
 /*fFe350*/ p17 /*fFe350*/   /*fFe350*/ p69 /*fFe350*/  (dfn /*fFe350*/ p16 /*fFe350*/ v /*fFe350*/ p50 /*fFe350*/  < dfn /*fFe350*/ p16 /*fFe350*/ u /*fFe350*/ p50 /*fFe350*/ )
 /*1c3b79*/ p34 /*1c3b79*/ 
U /*27C0eb*/ p16 /*27C0eb*/ u /*27C0eb*/ p50 /*27C0eb*/ .emplace_back(v) /*27C0eb*/ p22 /*27C0eb*/ 
low /*513087*/ p16 /*513087*/ u /*513087*/ p50 /*513087*/  = min(low /*513087*/ p16 /*513087*/ u /*513087*/ p50 /*513087*/ , dfn /*513087*/ p16 /*513087*/ v /*513087*/ p50 /*513087*/ ) /*513087*/ p22 /*513087*/ 
 /*cAe7d6*/ p13 /*cAe7d6*/ 
 /*19b028*/ p69 /*19b028*/  (cnt > 1) c /*19b028*/ p16 /*19b028*/ u /*19b028*/ p50 /*19b028*/  = -1 /*19b028*/ p22 /*19b028*/ 
 /*A2d3CD*/ p17 /*A2d3CD*/   /*A2d3CD*/ p69 /*A2d3CD*/  (cnt  /*A2d3CD*/ p33 /*A2d3CD*/  1) c /*A2d3CD*/ p16 /*A2d3CD*/ u /*A2d3CD*/ p50 /*A2d3CD*/  = fk /*A2d3CD*/ p22 /*A2d3CD*/ 
//	 /*c2A67f*/ p35 /*c2A67f*/  << u << ' ' << dfn /*c2A67f*/ p16 /*c2A67f*/ u /*c2A67f*/ p50 /*c2A67f*/  << ' ' << low /*c2A67f*/ p16 /*c2A67f*/ u /*c2A67f*/ p50 /*c2A67f*/  << ' ' << c /*c2A67f*/ p16 /*c2A67f*/ u /*c2A67f*/ p50 /*c2A67f*/  << ' ' << siz /*c2A67f*/ p16 /*c2A67f*/ u /*c2A67f*/ p50 /*c2A67f*/  <<  /*c2A67f*/ p45 /*c2A67f*/  /*c2A67f*/ p22 /*c2A67f*/ 
 /*78beDF*/ p13 /*78beDF*/ 

 /*B5021a*/ p71 /*B5021a*/  SMT
 /*9f354D*/ p34 /*9f354D*/ 
 /*79cBCe*/ p65 /*79cBCe*/   /*79cBCe*/ p15 /*79cBCe*/ maxN = 1e7 /*79cBCe*/ p22 /*79cBCe*/ 
 /*F95b0D*/ p15 /*F95b0D*/ ls /*F95b0D*/ p16 /*F95b0D*/ maxN /*F95b0D*/ p50 /*F95b0D*/ , rs /*F95b0D*/ p16 /*F95b0D*/ maxN /*F95b0D*/ p50 /*F95b0D*/ , cur /*F95b0D*/ p22 /*F95b0D*/ 
#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r
#define mid (l + r >> 1)
 /*815fBa*/ p31 /*815fBa*/  ins( /*815fBa*/ p15 /*815fBa*/ &p,  /*815fBa*/ p15 /*815fBa*/ l,  /*815fBa*/ p15 /*815fBa*/ r,  /*815fBa*/ p15 /*815fBa*/ pos)
 /*10B4b9*/ p34 /*10B4b9*/ 
 /*bf1084*/ p69 /*bf1084*/  (!p) p =  /*bf1084*/ p37 /*bf1084*/ cur /*bf1084*/ p22 /*bf1084*/ 
 /*81beD7*/ p69 /*81beD7*/  (l  /*81beD7*/ p33 /*81beD7*/  r)  /*81beD7*/ p61 /*81beD7*/  /*81beD7*/ p22 /*81beD7*/ 
 /*7b023D*/ p69 /*7b023D*/  (pos <= mid) ins(lson, pos) /*7b023D*/ p22 /*7b023D*/ 
 /*850BAd*/ p17 /*850BAd*/  ins(rson, pos) /*850BAd*/ p22 /*850BAd*/ 
 /*F8f7CB*/ p13 /*F8f7CB*/ 
 /*16D23a*/ p31 /*16D23a*/  merge( /*16D23a*/ p15 /*16D23a*/ &x,  /*16D23a*/ p15 /*16D23a*/ y)
 /*C5aec7*/ p34 /*C5aec7*/ 
 /*5a31d0*/ p69 /*5a31d0*/  (!x || !y)  /*5a31d0*/ p61 /*5a31d0*/   /*5a31d0*/ p31 /*5a31d0*/ (x |= y) /*5a31d0*/ p22 /*5a31d0*/ 
merge(ls /*EF751a*/ p16 /*EF751a*/ x /*EF751a*/ p50 /*EF751a*/ , ls /*EF751a*/ p16 /*EF751a*/ y /*EF751a*/ p50 /*EF751a*/ ) /*EF751a*/ p22 /*EF751a*/ 
merge(rs /*31F6E0*/ p16 /*31F6E0*/ x /*31F6E0*/ p50 /*31F6E0*/ , rs /*31F6E0*/ p16 /*31F6E0*/ y /*31F6E0*/ p50 /*31F6E0*/ ) /*31F6E0*/ p22 /*31F6E0*/ 
 /*dc06AB*/ p13 /*dc06AB*/ 
 /*79b05d*/ p5 /*79b05d*/  query( /*79b05d*/ p15 /*79b05d*/ p,  /*79b05d*/ p15 /*79b05d*/ l,  /*79b05d*/ p15 /*79b05d*/ r,  /*79b05d*/ p15 /*79b05d*/ L,  /*79b05d*/ p15 /*79b05d*/ R)
 /*8D5036*/ p34 /*8D5036*/ 
 /*63E841*/ p69 /*63E841*/  (!p)  /*63E841*/ p61 /*63E841*/  0 /*63E841*/ p22 /*63E841*/ 
 /*3Da1Cc*/ p69 /*3Da1Cc*/  (L <= l && r <= R)  /*3Da1Cc*/ p61 /*3Da1Cc*/  1 /*3Da1Cc*/ p22 /*3Da1Cc*/ 
 /*c70D38*/ p69 /*c70D38*/  (R <= mid)  /*c70D38*/ p61 /*c70D38*/  query(lson, L, R) /*c70D38*/ p22 /*c70D38*/ 
 /*FC3bD9*/ p69 /*FC3bD9*/  (L >  mid)  /*FC3bD9*/ p61 /*FC3bD9*/  query(rson, L, R) /*FC3bD9*/ p22 /*FC3bD9*/ 
 /*cf6EA7*/ p61 /*cf6EA7*/  query(lson, L, R) || query(rson, L, R) /*cf6EA7*/ p22 /*cf6EA7*/ 
 /*3dFa6A*/ p13 /*3dFa6A*/ 
 /*c8C456*/ p13 /*c8C456*/ 
unordered_map <int, int> E /*C6bcaA*/ p16 /*C6bcaA*/ maxn /*C6bcaA*/ p50 /*C6bcaA*/  /*C6bcaA*/ p22 /*C6bcaA*/ 
 /*78DFfA*/ p5 /*78DFfA*/  ans /*78DFfA*/ p16 /*78DFfA*/ maxn /*78DFfA*/ p50 /*78DFfA*/  /*78DFfA*/ p22 /*78DFfA*/ 
#define cs return void(ans[E[u][v]] = 1)
 /*dDCA6a*/ p15 /*dDCA6a*/ rt /*dDCA6a*/ p16 /*dDCA6a*/ maxn /*dDCA6a*/ p50 /*dDCA6a*/  /*dDCA6a*/ p22 /*dDCA6a*/ 

 /*F7df8b*/ p15 /*F7df8b*/ jump( /*F7df8b*/ p15 /*F7df8b*/ u,  /*F7df8b*/ p15 /*F7df8b*/ v)
 /*1Fadf3*/ p34 /*1Fadf3*/ 
 /*Da4cBb*/ p69 /*Da4cBb*/  (anc /*Da4cBb*/ p16 /*Da4cBb*/ 0 /*Da4cBb*/ p50 /*Da4cBb*/  /*Da4cBb*/ p16 /*Da4cBb*/ u /*Da4cBb*/ p50 /*Da4cBb*/   /*Da4cBb*/ p33 /*Da4cBb*/  v)  /*Da4cBb*/ p61 /*Da4cBb*/  0 /*Da4cBb*/ p22 /*Da4cBb*/ 
 /*cbe958*/ p15 /*cbe958*/ res = n /*cbe958*/ p22 /*cbe958*/ 
DEP(i, 18, 0)  /*4985D1*/ p69 /*4985D1*/  (dep /*4985D1*/ p16 /*4985D1*/ anc /*4985D1*/ p16 /*4985D1*/ i /*4985D1*/ p50 /*4985D1*/  /*4985D1*/ p16 /*4985D1*/ u /*4985D1*/ p50 /*4985D1*/  /*4985D1*/ p50 /*4985D1*/  > dep /*4985D1*/ p16 /*4985D1*/ v /*4985D1*/ p50 /*4985D1*/ )
 /*CDdc14*/ p34 /*CDdc14*/ 
res = min(res, mi /*B09AD5*/ p16 /*B09AD5*/ i /*B09AD5*/ p50 /*B09AD5*/  /*B09AD5*/ p16 /*B09AD5*/ u /*B09AD5*/ p50 /*B09AD5*/ ) /*B09AD5*/ p22 /*B09AD5*/ 
u = anc /*69F45e*/ p16 /*69F45e*/ i /*69F45e*/ p50 /*69F45e*/  /*69F45e*/ p16 /*69F45e*/ u /*69F45e*/ p50 /*69F45e*/  /*69F45e*/ p22 /*69F45e*/ 
 /*f31D4C*/ p13 /*f31D4C*/ 
 /*40e26A*/ p61 /*40e26A*/  res /*40e26A*/ p22 /*40e26A*/ 
 /*3cE2e1*/ p13 /*3cE2e1*/ 

 /*2C6E03*/ p31 /*2C6E03*/  check( /*2C6E03*/ p15 /*2C6E03*/ u,  /*2C6E03*/ p15 /*2C6E03*/ v)
 /*d4ebBf*/ p34 /*d4ebBf*/ 
 /*C0ad3E*/ p15 /*C0ad3E*/ w = u /*C0ad3E*/ p22 /*C0ad3E*/ 
DEP(i, 18, 0)  /*a72AE6*/ p69 /*a72AE6*/  (dep /*a72AE6*/ p16 /*a72AE6*/ anc /*a72AE6*/ p16 /*a72AE6*/ i /*a72AE6*/ p50 /*a72AE6*/  /*a72AE6*/ p16 /*a72AE6*/ w /*a72AE6*/ p50 /*a72AE6*/  /*a72AE6*/ p50 /*a72AE6*/  > dep /*a72AE6*/ p16 /*a72AE6*/ v /*a72AE6*/ p50 /*a72AE6*/ ) w = anc /*a72AE6*/ p16 /*a72AE6*/ i /*a72AE6*/ p50 /*a72AE6*/  /*a72AE6*/ p16 /*a72AE6*/ w /*a72AE6*/ p50 /*a72AE6*/  /*a72AE6*/ p22 /*a72AE6*/ 
 /*B7cF4A*/ p69 /*B7cF4A*/  (v  /*B7cF4A*/ p33 /*B7cF4A*/  1)
 /*a89bA6*/ p34 /*a89bA6*/ 
 /*B4DA6c*/ p69 /*B4DA6c*/  (T /*B4DA6c*/ p16 /*B4DA6c*/ v /*B4DA6c*/ p50 /*B4DA6c*/ .size() > 2) cs /*B4DA6c*/ p22 /*B4DA6c*/ 
 /*bdf2Fc*/ p69 /*bdf2Fc*/  (T /*bdf2Fc*/ p16 /*bdf2Fc*/ v /*bdf2Fc*/ p50 /*bdf2Fc*/ .size() > 1)  /*bdf2Fc*/ p69 /*bdf2Fc*/  (siz /*bdf2Fc*/ p16 /*bdf2Fc*/ u /*bdf2Fc*/ p50 /*bdf2Fc*/  > 1 || anc /*bdf2Fc*/ p16 /*bdf2Fc*/ 0 /*bdf2Fc*/ p50 /*bdf2Fc*/  /*bdf2Fc*/ p16 /*bdf2Fc*/ u /*bdf2Fc*/ p50 /*bdf2Fc*/   /*bdf2Fc*/ p53 /*bdf2Fc*/  v) cs /*bdf2Fc*/ p22 /*bdf2Fc*/ 
 /*FBDAE4*/ p69 /*FBDAE4*/  (anc /*FBDAE4*/ p16 /*FBDAE4*/ 0 /*FBDAE4*/ p50 /*FBDAE4*/  /*FBDAE4*/ p16 /*FBDAE4*/ u /*FBDAE4*/ p50 /*FBDAE4*/   /*FBDAE4*/ p33 /*FBDAE4*/  v)
 /*FA7cBa*/ p34 /*FA7cBa*/ 
 /*CbEeA1*/ p69 /*CbEeA1*/  (T /*CbEeA1*/ p16 /*CbEeA1*/ u /*CbEeA1*/ p50 /*CbEeA1*/ .size() > 1) cs /*CbEeA1*/ p22 /*CbEeA1*/ 
 /*78E5c9*/ p61 /*78E5c9*/  /*78E5c9*/ p22 /*78E5c9*/ 
 /*c3a5BD*/ p13 /*c3a5BD*/ 
 /*8204c9*/ p13 /*8204c9*/ 
 /*D6B580*/ p17 /*D6B580*/ 
 /*Ff3e0A*/ p34 /*Ff3e0A*/ 
 /*4bafDE*/ p69 /*4bafDE*/  (c /*4bafDE*/ p16 /*4bafDE*/ v /*4bafDE*/ p50 /*4bafDE*/   /*4bafDE*/ p33 /*4bafDE*/  -1) cs /*4bafDE*/ p22 /*4bafDE*/ 
 /*AB041d*/ p69 /*AB041d*/  (c /*AB041d*/ p16 /*AB041d*/ v /*AB041d*/ p50 /*AB041d*/  && c /*AB041d*/ p16 /*AB041d*/ v /*AB041d*/ p50 /*AB041d*/   /*AB041d*/ p53 /*AB041d*/  w) cs /*AB041d*/ p22 /*AB041d*/ 
 /*21a7Df*/ p13 /*21a7Df*/ 
 /*D29Bd7*/ p5 /*D29Bd7*/  flg = 0 /*D29Bd7*/ p22 /*D29Bd7*/ 
 /*ad0D4A*/ p69 /*ad0D4A*/  (v  /*ad0D4A*/ p33 /*ad0D4A*/  1) flg = 1 /*ad0D4A*/ p22 /*ad0D4A*/ 
 /*30F4c9*/ p17 /*30F4c9*/   /*30F4c9*/ p69 /*30F4c9*/  (jump(u, v) < dfn /*30F4c9*/ p16 /*30F4c9*/ v /*30F4c9*/ p50 /*30F4c9*/ ) flg = 1 /*30F4c9*/ p22 /*30F4c9*/ 
 /*a13E8A*/ p42 /*a13E8A*/  ( /*a13E8A*/ p15 /*a13E8A*/ w : T /*a13E8A*/ p16 /*a13E8A*/ u /*a13E8A*/ p50 /*a13E8A*/ )
 /*cEDC4a*/ p34 /*cEDC4a*/ 
 /*DBd41f*/ p56 /*DBd41f*/  res1 = (1 <= dfn /*DBd41f*/ p16 /*DBd41f*/ v /*DBd41f*/ p50 /*DBd41f*/  - 1 ? SMT  /*DBd41f*/ p21 /*DBd41f*/  query(rt /*DBd41f*/ p16 /*DBd41f*/ w /*DBd41f*/ p50 /*DBd41f*/ , 1, n, 1, dfn /*DBd41f*/ p16 /*DBd41f*/ v /*DBd41f*/ p50 /*DBd41f*/  - 1) : 0) /*DBd41f*/ p22 /*DBd41f*/ 
 /*ade695*/ p56 /*ade695*/  res2 = (dfn /*ade695*/ p16 /*ade695*/ v /*ade695*/ p50 /*ade695*/  + 1 <= dfn /*ade695*/ p16 /*ade695*/ u /*ade695*/ p50 /*ade695*/  - 1 ? SMT  /*ade695*/ p21 /*ade695*/  query(rt /*ade695*/ p16 /*ade695*/ w /*ade695*/ p50 /*ade695*/ , 1, n, dfn /*ade695*/ p16 /*ade695*/ v /*ade695*/ p50 /*ade695*/  + 1, dfn /*ade695*/ p16 /*ade695*/ u /*ade695*/ p50 /*ade695*/  - 1) : 0) /*ade695*/ p22 /*ade695*/ 
 /*EdAbcC*/ p69 /*EdAbcC*/  (res1  /*EdAbcC*/ p33 /*EdAbcC*/  res2)
 /*24fD0a*/ p34 /*24fD0a*/ 
 /*f8a7B5*/ p69 /*f8a7B5*/  (!res1) cs /*f8a7B5*/ p22 /*f8a7B5*/ 
flg = 1 /*9F61b5*/ p22 /*9F61b5*/ 
 /*D14CEf*/ p13 /*D14CEf*/ 
 /*8CA42D*/ p13 /*8CA42D*/ 
 /*Adc931*/ p69 /*Adc931*/  (!flg) cs /*Adc931*/ p22 /*Adc931*/ 
 /*0a8f47*/ p13 /*0a8f47*/ 


 /*5CDF8d*/ p31 /*5CDF8d*/  dfs2( /*5CDF8d*/ p15 /*5CDF8d*/ u)
 /*cE198D*/ p34 /*cE198D*/ 
REP(j, 1, 18) mi /*52FB7D*/ p16 /*52FB7D*/ j /*52FB7D*/ p50 /*52FB7D*/  /*52FB7D*/ p16 /*52FB7D*/ u /*52FB7D*/ p50 /*52FB7D*/  = min(mi /*52FB7D*/ p16 /*52FB7D*/ j - 1 /*52FB7D*/ p50 /*52FB7D*/  /*52FB7D*/ p16 /*52FB7D*/ u /*52FB7D*/ p50 /*52FB7D*/ , mi /*52FB7D*/ p16 /*52FB7D*/ j - 1 /*52FB7D*/ p50 /*52FB7D*/  /*52FB7D*/ p16 /*52FB7D*/ anc /*52FB7D*/ p16 /*52FB7D*/ j - 1 /*52FB7D*/ p50 /*52FB7D*/  /*52FB7D*/ p16 /*52FB7D*/ u /*52FB7D*/ p50 /*52FB7D*/  /*52FB7D*/ p50 /*52FB7D*/ ) /*52FB7D*/ p22 /*52FB7D*/ 
 /*27Ae93*/ p15 /*27Ae93*/ res = n /*27Ae93*/ p22 /*27Ae93*/ 
 /*C983Ab*/ p42 /*C983Ab*/  ( /*C983Ab*/ p15 /*C983Ab*/ f : U /*C983Ab*/ p16 /*C983Ab*/ u /*C983Ab*/ p50 /*C983Ab*/ ) res = min(res, dfn /*C983Ab*/ p16 /*C983Ab*/ f /*C983Ab*/ p50 /*C983Ab*/ ) /*C983Ab*/ p22 /*C983Ab*/ 
multiset <int> ssr /*b9A18c*/ p22 /*b9A18c*/ 
ssr.emplace(res) /*e61ac2*/ p22 /*e61ac2*/ 
 /*C9decD*/ p42 /*C9decD*/  ( /*C9decD*/ p15 /*C9decD*/ v : T /*C9decD*/ p16 /*C9decD*/ u /*C9decD*/ p50 /*C9decD*/ ) ssr.emplace(low /*C9decD*/ p16 /*C9decD*/ v /*C9decD*/ p50 /*C9decD*/ ) /*C9decD*/ p22 /*C9decD*/ 
 /*bd1fa2*/ p56 /*bd1fa2*/  it = ssr.begin() /*bd1fa2*/ p22 /*bd1fa2*/ 
 /*63dBA2*/ p42 /*63dBA2*/  ( /*63dBA2*/ p15 /*63dBA2*/ v : T /*63dBA2*/ p16 /*63dBA2*/ u /*63dBA2*/ p50 /*63dBA2*/ )
 /*C20A1c*/ p34 /*C20A1c*/ 
 /*85E61A*/ p56 /*85E61A*/  ti = it /*85E61A*/ p22 /*85E61A*/ 
 /*51FEe7*/ p69 /*51FEe7*/  (*ti  /*51FEe7*/ p33 /*51FEe7*/  low /*51FEe7*/ p16 /*51FEe7*/ v /*51FEe7*/ p50 /*51FEe7*/ ) ti /*51FEe7*/ p37 /*51FEe7*/  /*51FEe7*/ p22 /*51FEe7*/ 
mi /*B4aE6A*/ p16 /*B4aE6A*/ 0 /*B4aE6A*/ p50 /*B4aE6A*/  /*B4aE6A*/ p16 /*B4aE6A*/ v /*B4aE6A*/ p50 /*B4aE6A*/  = *ti /*B4aE6A*/ p22 /*B4aE6A*/ 
dfs2(v) /*7Bbadc*/ p22 /*7Bbadc*/ 
 /*fAC46D*/ p13 /*fAC46D*/ 
 /*F49BEA*/ p42 /*F49BEA*/  ( /*F49BEA*/ p15 /*F49BEA*/ f : U /*F49BEA*/ p16 /*F49BEA*/ u /*F49BEA*/ p50 /*F49BEA*/ ) check(u, f) /*F49BEA*/ p22 /*F49BEA*/ 
 /*Df9Cc3*/ p42 /*Df9Cc3*/  ( /*Df9Cc3*/ p15 /*Df9Cc3*/ v : T /*Df9Cc3*/ p16 /*Df9Cc3*/ u /*Df9Cc3*/ p50 /*Df9Cc3*/ ) SMT  /*Df9Cc3*/ p21 /*Df9Cc3*/  merge(rt /*Df9Cc3*/ p16 /*Df9Cc3*/ u /*Df9Cc3*/ p50 /*Df9Cc3*/ , rt /*Df9Cc3*/ p16 /*Df9Cc3*/ v /*Df9Cc3*/ p50 /*Df9Cc3*/ ) /*Df9Cc3*/ p22 /*Df9Cc3*/ 
 /*7eBbd0*/ p42 /*7eBbd0*/  ( /*7eBbd0*/ p15 /*7eBbd0*/ v : U /*7eBbd0*/ p16 /*7eBbd0*/ u /*7eBbd0*/ p50 /*7eBbd0*/ ) SMT  /*7eBbd0*/ p21 /*7eBbd0*/  ins(rt /*7eBbd0*/ p16 /*7eBbd0*/ u /*7eBbd0*/ p50 /*7eBbd0*/ , 1, n, dfn /*7eBbd0*/ p16 /*7eBbd0*/ v /*7eBbd0*/ p50 /*7eBbd0*/ ) /*7eBbd0*/ p22 /*7eBbd0*/ 
 /*d6Ae79*/ p13 /*d6Ae79*/ 

 /*8CEDaB*/ p15 /*8CEDaB*/  /*8CEDaB*/ p48 /*8CEDaB*/ ()
 /*2fcD4B*/ p34 /*2fcD4B*/ 
#ifdef CraZYali
file("A") /*B4587C*/ p22 /*B4587C*/ 
#endif
 /*fE9aD0*/ p55 /*fE9aD0*/  >> n >> m /*fE9aD0*/ p22 /*fE9aD0*/ 
REP(i, 1, m)
 /*FBba26*/ p34 /*FBba26*/ 
u /*dF490f*/ p16 /*dF490f*/ i /*dF490f*/ p50 /*dF490f*/  = read<int>() /*dF490f*/ p22 /*dF490f*/ v /*dF490f*/ p16 /*dF490f*/ i /*dF490f*/ p50 /*dF490f*/  = read<int>() /*dF490f*/ p22 /*dF490f*/ 
G /*ACbE0d*/ p16 /*ACbE0d*/ u /*ACbE0d*/ p16 /*ACbE0d*/ i /*ACbE0d*/ p50 /*ACbE0d*/  /*ACbE0d*/ p50 /*ACbE0d*/ .emplace_back(v /*ACbE0d*/ p16 /*ACbE0d*/ i /*ACbE0d*/ p50 /*ACbE0d*/ ) /*ACbE0d*/ p22 /*ACbE0d*/ G /*ACbE0d*/ p16 /*ACbE0d*/ v /*ACbE0d*/ p16 /*ACbE0d*/ i /*ACbE0d*/ p50 /*ACbE0d*/  /*ACbE0d*/ p50 /*ACbE0d*/ .emplace_back(u /*ACbE0d*/ p16 /*ACbE0d*/ i /*ACbE0d*/ p50 /*ACbE0d*/ ) /*ACbE0d*/ p22 /*ACbE0d*/ 
E /*dc719B*/ p16 /*dc719B*/ u /*dc719B*/ p16 /*dc719B*/ i /*dc719B*/ p50 /*dc719B*/  /*dc719B*/ p50 /*dc719B*/  /*dc719B*/ p16 /*dc719B*/ v /*dc719B*/ p16 /*dc719B*/ i /*dc719B*/ p50 /*dc719B*/  /*dc719B*/ p50 /*dc719B*/  = E /*dc719B*/ p16 /*dc719B*/ v /*dc719B*/ p16 /*dc719B*/ i /*dc719B*/ p50 /*dc719B*/  /*dc719B*/ p50 /*dc719B*/  /*dc719B*/ p16 /*dc719B*/ u /*dc719B*/ p16 /*dc719B*/ i /*dc719B*/ p50 /*dc719B*/  /*dc719B*/ p50 /*dc719B*/  = i /*dc719B*/ p22 /*dc719B*/ 
 /*fDda0e*/ p13 /*fDda0e*/ 
dep /*c3efAB*/ p16 /*c3efAB*/ 1 /*c3efAB*/ p50 /*c3efAB*/  = 1 /*c3efAB*/ p22 /*c3efAB*/ dfs1(1) /*c3efAB*/ p22 /*c3efAB*/ 
REP(j, 1, 18) REP(i, 1, n) anc /*a689Bf*/ p16 /*a689Bf*/ j /*a689Bf*/ p50 /*a689Bf*/  /*a689Bf*/ p16 /*a689Bf*/ i /*a689Bf*/ p50 /*a689Bf*/  = anc /*a689Bf*/ p16 /*a689Bf*/ j - 1 /*a689Bf*/ p50 /*a689Bf*/  /*a689Bf*/ p16 /*a689Bf*/ anc /*a689Bf*/ p16 /*a689Bf*/ j - 1 /*a689Bf*/ p50 /*a689Bf*/  /*a689Bf*/ p16 /*a689Bf*/ i /*a689Bf*/ p50 /*a689Bf*/  /*a689Bf*/ p50 /*a689Bf*/  /*a689Bf*/ p22 /*a689Bf*/ 

dfs2(1) /*82CdF9*/ p22 /*82CdF9*/ 
REP(i, 1, m) putchar(ans /*AfCed6*/ p16 /*AfCed6*/ i /*AfCed6*/ p50 /*AfCed6*/  + 48) /*AfCed6*/ p22 /*AfCed6*/ 
 /*E2bC3a*/ p61 /*E2bC3a*/  0 /*E2bC3a*/ p22 /*E2bC3a*/ 
 /*52A907*/ p13 /*52A907*/ 
