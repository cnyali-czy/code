program tsoi2_cmdo;
// Hash DP by Erwin
// O(2^S) S:number of enemies
// Expected Marks: 100

const
  LimitN=60;
  limitM=60;
  LimitE=15;
  dx:array[1..4] of shortint=(-1,0,1,0);
  dy:array[1..4] of shortint=(0,1,0,-1);
  fi='cmdo.in';
  fo='cmdo.out';

type
  Tenemy=record
           x,y,d:shortint;
         end;
  Trule=record
          a,b:shortint;
        end;

var
  n,m,enemies   :shortint;
  map           :array[0..LimitN+1,0..LimitM+1] of shortint;
  enemy         :array[1..LimitE] of Tenemy;
  connect       :array[1..LimitE,1..LimitE] of boolean;
  g             :array[0..(1 shl LimitE)-1] of int64;
  ans           :int64;

procedure scan(id:shortint);
var x,y,d:shortint;
begin
  x:=enemy[id].x;
  y:=enemy[id].y;
  d:=enemy[id].d;
  repeat
    inc(x,dx[d]);
    inc(y,dy[d]);
    if (1<=map[x,y]) and (map[x,y]<=enemies) then
      connect[id,map[x,y]]:=true;
  until map[x,y]=-1;
end;

function dir(ch:char):shortint;
begin
  case ch of
    '^':dir:=1;
    '>':dir:=2;
    'v':dir:=3;
    '<':dir:=4;
  end;
end;

procedure update(x,y:shortint;c:char);
begin
  case c of
    '.':map[x,y]:=0;
    '#':map[x,y]:=-1;
    'v','^','<','>':
      begin
        inc(enemies);
        enemy[enemies].x:=x;
        enemy[enemies].y:=y;
        enemy[enemies].d:=dir(c);
        map[x,y]:=enemies;
      end;
  end;
end;

procedure init;
var i,j:shortint;
    ch:char;
begin
  assign(input,fi);
  reset(input);
  fillchar(map,sizeof(map),255);
  fillchar(g,sizeof(g),255);
  enemies:=0;
  ans:=0;
  readln(n,m);
  for i:=1 to n do
    begin
      for j:=1 to m do
        begin
          read(ch);
          update(i,j,ch);
        end;
      readln;
    end;
  for i:=1 to enemies do scan(i);
  g[(1 shl enemies)-1]:=1;
  close(input);
end;

function free(v:shortint;h:longint):boolean;
var i:shortint;
begin
  free:=false;
  for i:=1 to enemies do
    if (v<>i) and ((1 shl (i-1)) and h=0) and (connect[i,v]) then
      exit;
  free:=true;
end;

function f(h:longint):int64;
var i:shortint;
    s:int64;
begin
  if g[h]<>-1 then
    f:=g[h]
  else
    begin
      s:=0;
      for i:=1 to enemies do
        if ((1 shl (i-1)) and h=0) and (free(i,h)) then
          inc(s,f(h or (1 shl (i-1))));
      g[h]:=s;
      f:=s;
    end;
end;

procedure _output;
begin
  assign(output,fo);
  rewrite(output);
  if ans=0 then writeln('Impossible')
           else writeln(ans);
  close(output);
end;

begin
  init;
  ans:=f(0);
  _output;
end.
