program language_checker;

var i,j,k:longint;
    f1,f2,f3:text;
    m,n,t1,t2,t:longint;
    s,s1,s2:ansistring;
    words:array[1..100]of string;
    g:array[1..100,1..100]of longint;
procedure endit(s:string);
begin
  assign(output,'check.txt');
  rewrite(output);
  if (s = '10') then writeln('FC:')
  else writeln('NO');
  writeln(s);
  close(output);
  close(f1);close(f2);close(f3);
  halt;
end;
function check(a,b:string):boolean;
var i:longint;
begin
  for i:=1 to length(a) do
    if a[i] in ['A'..'Z'] then a[i]:=chr(ord(a[i])-ord('A')+ord('a'));
  for i:=1 to length(a) do
    if b[i] in ['A'..'Z'] then b[i]:=chr(ord(b[i])-ord('A')+ord('a'));
  if a=b then check:=true
         else check:=false
end;
begin
  assign(f1,'language.in');
  assign(f2,'language.ans');
  assign(f3,'language.out');
  reset(f1);reset(f2);reset(f3);
  readln(f2,i);readln(f3,t);
  if i<>t then endit('0');
  readln(f1,n,m);
  for i:=1 to n do
    readln(f1,words[i]);
  fillchar(g,sizeof(g),0);
  for i:=1 to m do
    begin
      readln(f1,s);
      k:=pos(' ',s);
      s1:=copy(s,1,k-1);
      s2:=copy(s,k+1,length(s)-k);
      for j:=1 to n do
        if check(s1,words[j]) then t1:=j;
      for j:=1 to n do
        if check(s2,words[j]) then t2:=j;
      g[t1,t2]:=-1;
    end;

  readln(f3,s);
  if s<>'' then begin s:=s+' ';m:=1;end
           else m:=0;
  k:=pos(' ',s);
  s1:=copy(s,1,k-1);delete(s,1,k);
  while s<>'' do
    begin
      k:=pos(' ',s);
      s2:=copy(s,1,k-1);delete(s,1,k);
      for j:=1 to n do
        if check(s1,words[j]) then t1:=j;
      for j:=1 to n do
        if check(s2,words[j]) then t2:=j;
      if g[t1,t2]<>-1 then
        begin
          endit('0');
        end;
      s1:=s2;
      inc(m);
    end;
  if m<>t then endit('0');
  endit('10');
end.
