type  gtype=record
      m,w:longint;
      end;
var f:array[0..10000] of longint;
    good:array[1..1500] of gtype;
    n,i,j,ans,num,a,m,w,c:longint;
function max(x,y:longint):longint;
begin
  if x>y then exit(x)
         else exit(y);
end;
begin
  assign(input,'chicken.in');
  assign(output,'chicken.out');
  reset(input);
  rewrite(output);
  readln(n,c);
  num:=0;
  for i:=1 to n do
    begin
      readln(a,m,w);
      for j:=0 to 9 do
        if a>1 shl j then
          begin
            inc(num);
            good[num].m:=m*(1 shl j);
            good[num].w:=w*(1 shl j);
            a:=a-1 shl j;
          end;
      if a>0 then
        begin
          inc(num);
          good[num].m:=m*a;
          good[num].w:=w*a;
        end;
    end;
  fillchar(f,sizeof(f),0);
  for i:=1 to num do
    for j:=c downto good[i].m do
      f[j]:=max(f[j],f[j-good[i].m]+good[i].w);
  ans:=0;
  for i:=1 to c do
    ans:=max(ans,f[i]);
  writeln(ans);
  close(input);
  close(output);
end.
