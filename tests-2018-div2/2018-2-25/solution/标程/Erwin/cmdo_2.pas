program tsoi2_cmdo;
// Brute Force by Erwin
// O(S!) S:number of enemies
// Expected Marks: 90

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
  n,m           :shortint;
  enemies,rules :shortint;
  map           :array[0..LimitN+1,0..LimitM+1] of shortint;
  enemy         :array[1..LimitE] of Tenemy;
  rule          :array[1..sqr(LimitE)] of Trule;
  queue         :array[1..LimitE] of shortint;
  locate        :array[1..LimitE] of shortint;
  bool          :array[1..LimitE] of boolean;
  ans           :longint;

procedure make_rules(id:shortint);
var i,x,y,d:shortint;
begin
  x:=enemy[id].x;
  y:=enemy[id].y;
  d:=enemy[id].d;
  repeat
    inc(x,dx[d]);
    inc(y,dy[d]);
    if (1<=map[x,y]) and (map[x,y]<=enemies) then
      begin
        inc(rules);
        rule[rules].a:=id;
        rule[rules].b:=map[x,y];
      end;
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

procedure init;
var i,j:shortint;
    ch:char;
begin
  assign(input,fi);
  reset(input);
  fillchar(map,sizeof(map),255);
  enemies:=0;
  ans:=0;
  readln(n,m);
  for i:=1 to n do
    begin
      for j:=1 to m do
        begin
          read(ch);
          case ch of
            '.':map[i,j]:=0;
            '#':map[i,j]:=-1;
            'v','^','<','>':
              begin
                inc(enemies);
                with enemy[enemies] do
                  begin
                    x:=i; y:=j; d:=dir(ch);
                  end;
                map[i,j]:=enemies;
              end;
          end;
        end;
      readln;
    end;
  rules:=0;
  for i:=1 to enemies do
    make_rules(i);
  close(input);
end;

function check:boolean;
var i:shortint;
begin
  check:=false;
  for i:=1 to rules do
    if locate[rule[i].a]>locate[rule[i].b] then
      exit;
  check:=true;
end;

procedure dfs(d:shortint);
var i:shortint;
begin
  if d=enemies+1 then
    inc(ans,ord(check))
  else
    for i:=1 to enemies do
      if not bool[i] then
        begin
          queue[d]:=i;
          locate[i]:=d;
          bool[i]:=true;
          dfs(d+1);
          bool[i]:=false;
        end;
end;

procedure _output;
begin
  assign(output,fo);
  rewrite(output);
  if ans=0 then
    writeln('Impossible')
  else
    writeln(ans);
  close(output);
end;

begin
  init;
  dfs(1);
  _output;
end.
